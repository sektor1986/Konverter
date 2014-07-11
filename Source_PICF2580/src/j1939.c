#include "j1939.h"

#include "canRegs.h"

#define BUFFER_SIZE 8

#define J1939_OK 0
#define BUFFER_FULL 1
#define BUFFER_EMPTY 2

//75%, 250Kbps @8MHz
#define CAN_SPEED 		0x01, 0x90, 0x02
//75%, 250Kbps @32MHz
//#define CAN_SPEED 		0x07, 0x90, 0x02
//75%, 250Kbps @40MHz
//#define CAN_SPEED 		0x09, 0x90, 0x02
//75%, 250Kbps @10MHz
//#define CAN_SPEED 		0x01, 0xA0, 0x02

#define J1939_CLAIM_ADDRESS_TX 0										// Отправка заявки на использование адреса
#define J1939_CLAIM_ADDRESS_RX 1										// Получена заявка на адрес
	
#define J1939_ContentionTimeOut 250000l									// TimeOut

// CAN help functions
void canInit(unsigned char r1, unsigned char r2, unsigned char r3);		// Инициализация CAN шины
void canMode(unsigned char mode);										// Режим работы CAN

// J1939 help functions
void J1939_MesToRegs(struct J1939_message *msg, unsigned char *ptr);	// Заполниние регистров CAN
void J1939_RegsToMes(struct J1939_message *msg, unsigned char *ptr);	// Заполнение полей сообщения из регистров CAN
void J1939_CopyName(void);												// Копирование имени ECU в поле данных сообщения
unsigned char J1939_RecalculateAddress(void);							// Пересчет адреса
char J1939_CompareName(unsigned char *data);							// Сравнение имени: -1 меньше, 0 равно, 1 больше
void J1939_SetAddressFilter(unsigned char addr);						// Установка приемного фильтра на конкретный адрес
void J1939_memcpy(unsigned char *dst, const unsigned char *src, unsigned char size);

void J1939_ClaimAddress(unsigned char mode);							// Процедура инициализации адреса
void J1939_RequestForAddressClaimHandling(void);						// Получен запрос адреса
unsigned char J1939_SendOneMessage(struct J1939_message *msg);			// Посылка одного сообщения
void J1939_ReceiveMessages(void);										// Получить сообщения
void J1939_TransmitMessages(void);										// Передача сообщений из очереди
void J1939_PutInReceiveQueue(void);										// Поместить сообщение в очередь приемника

// Variables
struct J1939_message OneMessage;										// Пересылаемое/полученное сообщение
union  J1939_name Name;													// Имя ECU
unsigned char J1939_Address;											// Текущий адрес
unsigned char ComandedAddress;

// Флаги состояния ECU
struct
{
	unsigned int CannotClaimAddress:1;									// Невозможно получить адрес
	unsigned int WaitingForAddressClaimContention:1;					// Ожидание адреса
	unsigned int ReceivedMessagesDropped:1;								// Полученное сообщение утеряно

	unsigned int AddressRequest:1;
} J1939_Flags;
unsigned long int ContentionWaitTime = 0l;

struct J1939_message TXbuffer[BUFFER_SIZE];								// Передающий буффер
struct J1939_message RXbuffer[BUFFER_SIZE];								// Приемный буффер
unsigned char TXstart,TXend,RXstart,RXend;
unsigned char TXsize,RXsize;											// Количество сообщений в буфферах

void J1939_init(unsigned char startAddress, unsigned char *name)
{
	unsigned char i=0;

	TXstart=TXend=RXstart=RXend=0;
	TXsize=RXsize=0;

	canInit(CAN_SPEED);		// 250 Kbit/s

	ComandedAddress = startAddress;
	J1939_Address = startAddress;
	for (i;i<8;i++) Name.name[i] = name[i];

	// Set up mask 0 to receive broadcast messages.  Set up mask 1 to 
	// receive messages sent to the global address (or eventually us).
	RXM0SIDH = 0x00;
	RXM0SIDL = 0x00;
	RXM0EIDH = 0x00;
	RXM0EIDL = 0x00;
	RXM1SIDH = 0x00;
	RXM1SIDL = 0x00;
	RXM1EIDH = 0x00;
	RXM1EIDL = 0x00;

	// Set up filter 0 to accept only broadcast messages (PF = 240-255).
	// Set up filter 2 and 3 to accept only the global address.  Once we
	// get an address for the CA, we'll change filter 3 to accept that
	// address.
	RXF0SIDH = 0x07;
	RXF0SIDL = 0x88; //0x88
	RXF2SIDL = 0x08;
	RXF2EIDH = J1939_GLOBAL_ADDRESS;
	RXF3SIDL = 0x08;
	RXF3EIDH = J1939_GLOBAL_ADDRESS;

	canMode(0);

	J1939_Flags.CannotClaimAddress = 0;
	J1939_Flags.WaitingForAddressClaimContention = 0;
	J1939_Flags.ReceivedMessagesDropped = 0;

	J1939_Flags.AddressRequest = 0;

	J1939_ClaimAddress(J1939_CLAIM_ADDRESS_TX);

	while (J1939_Flags.WaitingForAddressClaimContention)
		J1939_poll(5);
	return;
}

void canInit(unsigned char r1, unsigned char r2, unsigned char r3)
{
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB2 = 0;

	canMode(1);
	RXB0CON = 0x40;
	RXB1CON = 0x40;

	BRGCON1 = r1;
    BRGCON2 = r2;
	BRGCON3 = r3;

	CIOCONbits.ENDRHI = 1;
	CIOCONbits.CANCAP = 0;

	return;
}

void canMode(unsigned char m)
{
	unsigned char mode = 0;
	switch (m)
	{
		case 0: CANCON &= 0b00011111; break;						//normal
		case 1: CANCON = 0b10000000 | (CANCON&0b00011111); mode = 0b10000000; break;	//initialize
		case 2: CANCON = 0b01000000 | (CANCON&0b00011111); mode = 0b01000000; break;   //loopback
	}
	while ((CANSTAT&0b11100000)!=mode);
}

void J1939_MesToRegs(struct J1939_message *msg, unsigned char *ptr)
{
	unsigned char i = 0;
	*ptr = 0;
	*ptr |= (msg->priority<<5);
	*ptr |= (msg->PDUformat>>5);
	*ptr |= (msg->dp<<3);
	ptr++;
	*ptr = 0x08;
	*ptr |= ((msg->PDUformat<<3)&0b11100000);
	*ptr |= (msg->PDUformat&0b00000011);
	ptr++;
	*ptr = msg->PDUspecific;
	ptr++;
	*ptr = msg->sourceAddr;
	ptr++;
	*ptr = msg->dataLen;
	ptr++;
	for (i; i<msg->dataLen; i++)
	{
		*ptr = msg->data[i];
		ptr++;
	}

	return;
}	

void J1939_RegsToMes(struct J1939_message *msg, unsigned char *ptr)
{
	unsigned char i = 0;
	msg->priority = *ptr>>5;
	msg->dp = ((*ptr & 0b00001000)>>3);
	msg->PDUformat = 0;
	msg->PDUformat |= *ptr<<5;
	ptr++;
	msg->PDUformat |= ((*ptr>>3)&0b00011100);
	msg->PDUformat |= (*ptr &0b00000011);
	ptr++;
	msg->PDUspecific = *ptr;
	ptr++;
	msg->sourceAddr = *ptr;
	ptr++;
	if (msg->dataLen>8)
		msg->dataLen = 8;
	msg->dataLen = *ptr;
	ptr++;
	for (i; i<msg->dataLen; i++)	
	{
		msg->data[i] = *ptr;
		ptr++;
	}

	return;
}

void J1939_CopyName(void)
{
	unsigned char i = 0;
	for (i; i<8; i++)
		OneMessage.data[i] = Name.name[i];

	return;
}

void J1939_ClaimAddress(unsigned char mode)
{
	OneMessage.priority = J1939_CONTROL_PRIORITY;
	OneMessage.PDUspecific = J1939_GLOBAL_ADDRESS;
	OneMessage.PDUformat = J1939_PF_ADDRESS_CLAIMED;
	OneMessage.dataLen = 8;
	OneMessage.r = 0;
	OneMessage.dp = 0;

	if (mode == J1939_CLAIM_ADDRESS_RX)
	{
		if (OneMessage.sourceAddr != J1939_Address 
			|| OneMessage.sourceAddr == J1939_NULL_ADDRESS) return;

		if (J1939_CompareName(OneMessage.data)!=-1)
		{
			if (!J1939_RecalculateAddress())
			{
				J1939_CopyName();
				J1939_Address = J1939_NULL_ADDRESS;
				OneMessage.sourceAddr = J1939_NULL_ADDRESS;
				J1939_SendOneMessage(&OneMessage);					
				J1939_SetAddressFilter( J1939_GLOBAL_ADDRESS );
				J1939_Flags.CannotClaimAddress = 1;
				J1939_Flags.WaitingForAddressClaimContention = 0;
				return;
			}
		}
	}
	
	J1939_CopyName();
	OneMessage.sourceAddr = ComandedAddress;	
	J1939_SendOneMessage(&OneMessage);

	if (((ComandedAddress & 0x80) == 0) ||			// Addresses 0-127
		((ComandedAddress & 0xF8) == 0xF8))			// Addresses 248-253 (254,255 illegal)
	{
		J1939_Flags.CannotClaimAddress = 0;
		J1939_Address = ComandedAddress;
		// Set up filter to receive messages sent to this address
		J1939_SetAddressFilter( J1939_Address );
	}
	else
	{
		// We don't have a proprietary address, so we need to wait.
 		J1939_Flags.WaitingForAddressClaimContention = 1;
		ContentionWaitTime = 0;
	}

	return;
}

void J1939_SetAddressFilter(unsigned char addr)
{
	canMode(1);
	
	RXF3EIDH = addr;
	
	canMode(0);

	return;
}

unsigned char J1939_RecalculateAddress(void)
{
	if (J1939_Address<128 || (!J1939_Flags.WaitingForAddressClaimContention && J1939_Address>128))
		J1939_Address = 128;
	else
		J1939_Address++;

	ComandedAddress = J1939_Address;

	if (J1939_Address == 248)
	{
		J1939_Address = J1939_NULL_ADDRESS;
		return 0;
	}

	return 1;
}

char J1939_CompareName(unsigned char *data)
{
	unsigned char	i;

	for (i = 0; (i<8) && (data[i] == Name.name[i]); i++);

	if (i == 8)
		return 0;
	else if (Name.name[i] < data[i] )
		return -1;
	else
		return 1;

	return 0;
}

unsigned char J1939_SendOneMessage(struct J1939_message *msg)
{
	unsigned char i = 0;
	unsigned char *ptr, *pCON;
	while (i<2)
	{
		switch (i)
		{
			case 0: ptr = &TXB0CON; break;
			case 1: ptr = &TXB1CON; break;
			case 2: ptr = &TXB2CON; break;
		}

		pCON = ptr;
		ptr++;

		if (!(*pCON & 0x08))
		{
			J1939_MesToRegs(msg, ptr);
			*pCON |= 0x08;
			return 1;
		}
		
		i++;
	}	
	return 0;
}

void J1939_poll(unsigned char time)
{
	ContentionWaitTime+=time;	

	J1939_ReceiveMessages();
	J1939_TransmitMessages();

	if (J1939_Flags.WaitingForAddressClaimContention &&
		(ContentionWaitTime >= J1939_ContentionTimeOut))
	{
		J1939_Flags.CannotClaimAddress = 0;
		J1939_Flags.WaitingForAddressClaimContention = 0;
		
		J1939_Address = ComandedAddress;
		J1939_SetAddressFilter(J1939_Address);
	}
}

void J1939_ReceiveMessages(void)
{
	unsigned char i=0;
	unsigned char *ptr,*pCON;

	while (i<2)
	{
		switch (i)
		{
			case 0: ptr = &RXB0CON; break;
			case 1: ptr = &RXB1CON; break;
		}
		pCON = ptr;
		ptr++;
		if (*pCON & 0x80)
		{
			J1939_RegsToMes(&OneMessage,ptr);

			switch (OneMessage.PDUformat)
			{
				case J1939_PF_ADDRESS_CLAIMED:
					if (!J1939_Flags.AddressRequest)
						J1939_ClaimAddress( J1939_CLAIM_ADDRESS_RX );
					break;
				case J1939_PF_REQUEST:
					{
						if ((OneMessage.data[0] == J1939_PGN0_REQ_ADDRESS_CLAIM) &&
							(OneMessage.data[1] == J1939_PGN1_REQ_ADDRESS_CLAIM) &&
							(OneMessage.data[2] == J1939_PGN2_REQ_ADDRESS_CLAIM))
							J1939_RequestForAddressClaimHandling();
						else
							J1939_PutInReceiveQueue();
					}
					break;
				default:
				{
					J1939_PutInReceiveQueue();
				}
			}
			*pCON &= 0x7F;
		}
		i++;		
	}
	return;	
}

void J1939_RequestForAddressClaimHandling(void)
{
	if (J1939_Flags.CannotClaimAddress)
		OneMessage.sourceAddr = J1939_NULL_ADDRESS;	// Send Cannot Claim Address message
	else
		OneMessage.sourceAddr = J1939_Address;		// Send Address Claim for current address

	OneMessage.priority = J1939_CONTROL_PRIORITY;
	OneMessage.PDUformat = J1939_PF_ADDRESS_CLAIMED;	// Same as J1939_PF_CANNOT_CLAIM_ADDRESS
	OneMessage.PDUspecific = J1939_GLOBAL_ADDRESS;
	OneMessage.dataLen = 8;
	J1939_CopyName();
	J1939_SendOneMessage(&OneMessage);
	
	return;
}

void J1939_PutInReceiveQueue(void)
{
	if (RXsize<BUFFER_SIZE)
	{
		J1939_memcpy((unsigned char*)&RXbuffer[RXend],(const unsigned char*)&OneMessage,sizeof(struct J1939_message));
		RXend++;
		RXsize++;
		if (RXend == BUFFER_SIZE) RXend=0;
	}
	else
		J1939_Flags.ReceivedMessagesDropped = 1;	

	return;
}

void J1939_TransmitMessages(void)
{
	unsigned char buf = 0;
	while (TXsize && buf<3)
	{
		if (J1939_SendOneMessage(&TXbuffer[TXstart]))
		{
			TXsize--;
			TXstart++;
			if (TXstart == BUFFER_SIZE) TXstart=0;
		}
	}
	return;
}

unsigned char J1939_Send(struct J1939_message *msg)
{
	if (TXsize == BUFFER_SIZE) return BUFFER_FULL;
	J1939_memcpy((unsigned char*)&TXbuffer[TXend],(const unsigned char*)msg,sizeof(struct J1939_message));
	TXbuffer[TXend].sourceAddr = 0x00;//J1939_Address;
	TXsize++;
	TXend++;
	if (TXend == BUFFER_SIZE) TXend=0;
	return J1939_OK;
}

unsigned char J1939_Receive(struct J1939_message *msg)
{
	if (RXsize == 0) return BUFFER_EMPTY;
	J1939_memcpy((unsigned char*)msg,(const unsigned char*)&RXbuffer[RXstart], sizeof(struct J1939_message));
	RXsize--;
	RXstart++;
	if (RXstart==BUFFER_SIZE) RXstart=0;
	return J1939_OK;
}

unsigned char J1939_RXsize(void)
{
	return RXsize;
}

unsigned char J1939_TXsize(void)
{
	return TXsize;
}

void J1939_memcpy(unsigned char *dst, const unsigned char *src, unsigned char size)
{
	unsigned char i=0;
	for (i; i<size; i++)
		dst[i] = src[i];
	return;
}

void ECAN_Transmit(void)
{
    TXB1EIDH = 0x00;
    TXB1EIDL = 0x00;
    
    //0x35E    0110 1011 110
    TXB1SIDH = 0x6B;
   // TXB0SIDL = 0xC0;
	TXB1SIDL = 0xCB;

    TXB1DLC = 0x08;
    TXB1D0 = 0xAA;
    TXB1D1 = 0xCC;
    TXB1D2 = 0x55;
    TXB1D3 = 0x00;
    TXB1D4 = 0x00;
    TXB1D5 = 0x00;	
    TXB1D6 = 0x00;
    TXB1D7 = 0x00;
    
    TXB1CONbits.TXREQ = 1; //Set the buffer to transmit

    
}