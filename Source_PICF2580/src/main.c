#define USE_OR_MASKS
#include <p18cxxx.h>
#include "j1939.h"
#include "adc.h"
#include "timers.h"

#pragma config XINST = OFF
#pragma config OSC=IRCIO7, WDT=OFF, LVP=OFF, MCLRE = OFF, PBADEN = ON //, PWRT = ON //OSC=HS
#define Rop              210.0

unsigned char name[8] = {0};

unsigned int ADCResult=0;
float voltage=0;

void adc_init(void);
void mcu_init(void);
void timer_init(void);
void User_Timer(void);

float valueR(unsigned char channel);
void SendAirTemperatur(unsigned int value);
void SendAdaptiveCruise(unsigned char value);
void SendAEBS(unsigned char value);
unsigned int CalcAirTemperatur_For_J1939(void);
unsigned char CalcFuelLevel_For_J1939(void);
void ReceiveMessage(void);

void InterruptHandlerHigh (void);


#pragma code InterruptVectorHigh  = 0x08     
void InterruptVectorHigh (void) 
{
	_asm
		goto InterruptHandlerHigh  //jump to interrupt routine
	_endasm
}

#pragma interrupt InterruptHandlerHigh      
void InterruptHandlerHigh () 
{
	if (PIR1bits.TMR1IF)
	{		
		PIR1bits.TMR1IF = 0; 
		WriteTimer1(0xE0C0);
//		WriteTimer1(0xD8F0);  // Reload 1 ms 10MHz
		User_Timer();
	}	
}

void main(void)
{
	unsigned long int time = 0l;
	unsigned long int address;
	unsigned char status=0;
	unsigned char count = 0,i;

    LATC = 0x3F;
	TRISC = 0;		//���� C �� ����� RC0-RC7

	mcu_init();
	adc_init();

	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	J1939_init(0x21,name);

	timer_init();

	while (1)
	{
/*		while(!PIR1bits.TMR1IF); 
		User_Timer();
        PIR1bits.TMR1IF = 0;*/
	}

	return;
}

void adc_init(void)
{
    unsigned char channel=0x00,config1=0x00,config2=0x00,config3=0x00,portconfig=0x00,i=0;

	//-- clear adc interrupt and turn off adc if in case was on prerviously---
    CloseADC();
	//--initialize adc---
	/**** ADC configured for:
    * FOSC/2 as conversion clock
    * Result is right justified
    * Aquisition time of 2 AD
    * Channel 1 for sampling
    * ADC interrupt on
    * ADC reference voltage from VDD & VSS
*/
    config1 = ADC_FOSC_4 | ADC_RIGHT_JUST | ADC_16_TAD ;
    config2 = ADC_CH0 | ADC_CH1 | ADC_CH2 | ADC_CH3 | ADC_CH4 | ADC_CH8 | ADC_CH9 | ADC_CH10 | ADC_INT_ON | ADC_REF_VDD_VSS;
	portconfig = ADC_10ANA ;

    OpenADC(config1,config2,portconfig);

//---initialize the adc interrupt and enable them---
    ADC_INT_ENABLE();	
}

void mcu_init(void) 
{ 
    // Set the internal clock to 16mHz 

	OSCCONbits.IRCF0 = 1; 
	OSCCONbits.IRCF1 = 1; 
	OSCCONbits.IRCF2 = 1; 

	OSCTUNEbits.PLLEN = 0; //Frequency Multiplier PLL for INTOSC Enable bit

} 

void timer_init(void)
{
	WriteTimer1(0);
	OpenTimer1(T1_16BIT_RW | T1_SOURCE_INT | T1_PS_1_1 | T1_OSC1EN_OFF | T1_SYNC_EXT_OFF | TIMER_INT_ON); 

	WriteTimer1(0xE0C0);  // Reload 1 ms 8MHz
//	WriteTimer1(0xD8F0);  // Reload 1 ms 10MHz

}

void User_Timer(void)
{
    static unsigned int TimerValue = 0;
    static unsigned int TimerValue_2 = 0;
    static unsigned int TimerValue_3 = 0;
    static unsigned int valueAEBS = 1;
    static unsigned int valueCruiseControl = 1;
    static unsigned int TimerButtonUpdate = 0;
    static unsigned int state_button_0 = 1;
    static unsigned int state_button_1 = 1;
    unsigned int ADC_value = 0;
    
	TimerValue++;
	TimerValue_2++;
	TimerValue_3++;
	TimerButtonUpdate++;
	
	
	if (TimerValue == 240) //������� 1 �
	{
		SendAirTemperatur(CalcAirTemperatur_For_J1939());
        TimerValue = 0;
	}
	
	
	if (TimerButtonUpdate == 60) //������� 250 ��
	{
    	SetChanADC(ADC_CH1);
    	ConvertADC();
    	while(BusyADC());
    	ADC_value = (float) ReadADC();
        if (ADC_value < 100)
        {
            if (state_button_0)
            {
                if (valueCruiseControl)
                    valueCruiseControl = 0;
                else
                    valueCruiseControl = 1;
                TimerButtonUpdate = 0;
                state_button_0 = 0;
            } 
        }
        else
            state_button_0 = 1;
        SetChanADC(ADC_CH0);
    	ConvertADC();
    	while(BusyADC());
    	ADC_value = (float) ReadADC();
        if (ADC_value < 100)
        {
            if (state_button_1)
            {
                if (valueAEBS)
                    valueAEBS = 0;
                else
                    valueAEBS = 1;
		        TimerButtonUpdate = 0; 
		        state_button_1 = 0; 
		    }
		}
	    else
		       state_button_1 = 1; 
	    TimerButtonUpdate = 0;   
	}
				
	if (TimerValue_2 == 60) //������� 250 ��
	{
		SendAdaptiveCruise(valueCruiseControl);		
		TimerValue_2 = 0;
	}
	
	if (TimerValue_3 == 12) //������� 50 ��
	{
		SendAEBS(valueAEBS);	
		TimerValue_3 = 0;	    
	}
	
	ReceiveMessage();
}

float valueR(unsigned char channel)
{              
//               
//             _____       _____
//     |------|_____|--*--|_____|------- + Uref         R��� = (Rop * U���)/(Uref - U���)
//              R���   |    Rop                         R��� = (Rop * ADC���)/(ADCref - ADC���))
//                     |
//                     |----> U���
	
	unsigned char i;
	float ADCism = 0.0;
	float ADCref = 0.0;
	float ADCResult=0.0;

	float resist = 0.0;

	switch (channel)
	{
		case 0: SetChanADC(ADC_CH3); break;
		case 1: SetChanADC(ADC_CH2); break;
		case 2: SetChanADC(ADC_CH1); break;
		case 3:	SetChanADC(ADC_CH0); break;
	}
    for(i=0;i<50;i++)
    {
    	ConvertADC();
    	while(BusyADC());
    	ADCism += (float) ReadADC();
    }
    ADCism /= 50.0;

	switch (channel)
	{
		case 0: SetChanADC(ADC_CH10); break;
		case 1: SetChanADC(ADC_CH8); break;
		case 2: SetChanADC(ADC_CH9); break;
		case 3:	SetChanADC(ADC_CH4); break;
	}
    for(i=0;i<50;i++)
    {
    	ConvertADC();
    	while(BusyADC());
    	ADCref += (float) ReadADC();
    }
    ADCref /= 50.0;
	if (ADCism < ADCref)	
		resist = (Rop * ADCism)/(ADCref - ADCism);
	else
		resist = 1000.0;
	return resist;
}

void SendAirTemperatur(unsigned int value)  // PGN 65269 Ambient Conditions - AMB, SPN 171 Ambient Air Temperature (Byte 4-5) 
{
	struct J1939_message msg;

	msg.PDUformat = 0xFE;
	msg.PDUspecific = 0xF5;
	msg.priority = J1939_INFO_PRIORITY;
	msg.sourceAddr = 0x21;
	msg.dataLen = 8;
	msg.r = 0;
	msg.dp = 0;
	msg.data[0] = 0xFF;
	msg.data[1] = 0xFF;
	msg.data[2] = 0xFF;
	msg.data[3] = value & 0xFF;
	msg.data[4] = (value>>8) & 0xFF;
	msg.data[5] = 0xFF;
	msg.data[6] = 0xFF;
	msg.data[7] = 0xFF;

	J1939_Send(&msg);
	J1939_poll(5);
}

void SendAdaptiveCruise(unsigned char value)  // PGN 65105 Adaptive Cruise Control ACC2, Operator Input - DD , SPN 5023 ACC usage demand 
{
	struct J1939_message msg;

	msg.PDUformat = 0xFE;
	msg.PDUspecific = 0x51;
	msg.priority = J1939_INFO_PRIORITY;
	msg.sourceAddr = 0x00;
	msg.dataLen = 8;
	msg.r = 0;
	msg.dp = 0;

	if (value)
	    msg.data[0] = 0xFD;
	else
	    msg.data[0] = 0xFC;

	msg.data[1] = 0xFF;
	msg.data[2] = 0xFF;
	msg.data[3] = 0xFF;
	msg.data[4] = 0xFF;
	msg.data[5] = 0xFF;
	msg.data[6] = 0xFF;
	msg.data[7] = 0xFF;

	J1939_Send(&msg);
	J1939_poll(5);
}

//SPN 5681 PGN x0B00
void SendAEBS(unsigned char value)
{
	struct J1939_message msg;

	msg.PDUformat = 0x0B;
	msg.PDUspecific = 0x00;
	msg.priority = J1939_CONTROL_PRIORITY;
	msg.sourceAddr = 0x00;
	msg.dataLen = 8;
	msg.r = 0;
	msg.dp = 0;
	
	if (value)
	    msg.data[0] = 0xFD;
	else
	    msg.data[0] = 0xFC;

	msg.data[1] = 0xFF;
	msg.data[2] = 0xFF;
	msg.data[3] = 0xFF;
	msg.data[4] = 0xFF;
	msg.data[5] = 0xFF;
	msg.data[6] = 0xFF;
	msg.data[7] = 0xFF;

	J1939_Send(&msg);
	J1939_poll(5);    
}

unsigned int CalcAirTemperatur_For_J1939(void)
{
	unsigned int result = 0;
	float C = 0.0;
		
	// C = 2,5641*R - 256,24
	// ����������� 	| �������������
	// 		-40		|	84.3
	//		0		|	100.0
	//		40		|	115.5
	C = 2.5641*valueR(1)-256.24;
	result =( unsigned int)((C + 273.0)*32);
	
	return result;
}

void ReceiveMessage(void)
{
    struct J1939_message msg;
    static time = 0;
    
    time++;
    
    while (J1939_RXsize())
    {
        J1939_Receive(&msg);
        if ( (msg.PDUformat == 0xFD) && (msg.PDUspecific == 0xC4) ) 
        {
            if (((msg.data[3]>>2) & 0x03) == 0x01)
                LATC |= 0xC0;
            else
                LATC &= ~0xC0;
            time = 0; 
        }
    }
    
    if (time > 100)
       LATC &= ~0xC0;    
    else
        time++;
    
}
