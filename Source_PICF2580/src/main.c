#define USE_OR_MASKS
#include <p18cxxx.h>
#include "j1939.h"
#include "adc.h"
#include "timers.h"

#pragma config XINST = OFF
#pragma config OSC=HS, WDT=ON, LVP=OFF, MCLRE = OFF, PBADEN = ON //, PWRT = ON //OSC=IRCIO7
#define Rop              210.0
#define Vop              5.11

unsigned char name[8] = {0};

unsigned int ADCResult=0;
float voltage=0;

void adc_init(void);
void mcu_init(void);
void timer_init(void);
void User_Timer(void);

float valueR(unsigned char channel);
float valueV(unsigned char channel);
void SendAirTemperatur(unsigned int value);
void SendAdaptiveCruise(unsigned char value);
void SendAEBS(unsigned char value);
void SendFuelLevel(unsigned char value);
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
//		WriteTimer1(0xE0C0);
		WriteTimer1(0xD8F0);  // Reload 1 ms 10MHz
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
	TRISC = 0;		//порт C на выход RC0-RC7

	mcu_init();
	adc_init();

	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	J1939_init(0x21,name);

	timer_init();

	while (1)
	{
    	ClrWdt();
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

//	WriteTimer1(0xE0C0);  // Reload 1 ms 8MHz
	WriteTimer1(0xD8F0);  // Reload 1 ms 10MHz

}

void User_Timer(void)
{
    static unsigned int TimerValue = 0;
    static unsigned int TimerValue_2 = 120;
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
	
	
	if (TimerValue == 235) //Таймаут 1 с
	{
		SendAirTemperatur(CalcAirTemperatur_For_J1939());
        TimerValue = 0;
	}
	
    if (TimerValue_2 == 235) //Таймаут 1 с
	{
		SendFuelLevel(CalcFuelLevel_For_J1939());
        TimerValue_2 = 0;
	}
	
	/*
	if (TimerButtonUpdate == 60) //Таймаут 250 мс
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
				
	if (TimerValue_2 == 60) //Таймаут 250 мс
	{
		SendAdaptiveCruise(valueCruiseControl);		
		TimerValue_2 = 0;
	}
	
	if (TimerValue_3 == 12) //Таймаут 50 мс
	{
		SendAEBS(valueAEBS);	
		TimerValue_3 = 0;	    
	}
	*/
	ReceiveMessage();
}

float valueR(unsigned char channel)
{              
//               
//             _____       _____                        Uизм = (Rизм/(Rop+Rизм)) * Uref
//     |------|_____|--*--|_____|------- + Uref         Rизм = (Rop * Uизм)/(Uref - Uизм)
//              Rизм   |    Rop                         Rизм = (Rop * ADCизм)/(ADCref - ADCизм))
//                     |
//                     |----> Uизм
	
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

float valueV(unsigned char channel)
{
    unsigned char i;
	float ADCism = 0.0;
	float ADCResult=0.0;
	
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
    ADCResult = ADCism * Vop / 1024; 
    
    return ADCResult;
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

//SPN 96 PGN 0xFEFC
void SendFuelLevel(unsigned char value)
{
    struct J1939_message msg;

	msg.PDUformat = 0xFE;
	msg.PDUspecific = 0xFC;
	msg.priority = J1939_INFO_PRIORITY;
	msg.sourceAddr = 0x21;
	msg.dataLen = 8;
	msg.r = 0;
	msg.dp = 0;
	
	msg.data[0] = 0xFF;
	msg.data[1] = value;
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
	float C = 0.0;
		
	// C = 2,5641*R - 256,24
	// Температура 	| Сопротивление
	// 		-40		|	84.3
	//		0		|	100.0
	//		40		|	115.5
	C = valueR(1);
	if (C < 500)
	{
	    C = 2.5641*C - 256.24;
	    return ( unsigned int)((C + 273.0)*32);
	}
	else
	    return 0xFFFF;
	
}

unsigned char CalcFuelLevel_For_J1939(void)
{
    unsigned char result = 0;
    float V = 0.0;
    
    V = valueV(3);          // Получаем значение напряжения
    if (V < 0.5)            
        return 0xFF;        // Датчик не подключен
    else if (V < 1)
        return 0x00;        // Минимальный уровень
    else if (V <= 3.7)
    {
        return (unsigned char)(92.593*V - 92.593);  // Рабочий диапазон
    }
    else
        return 0xFA;        // Максимальный уровень
}

void ReceiveMessage(void)
{
    struct J1939_message msg;
    static unsigned int time_msg1 = 0;
    static unsigned int time_msg2 = 0;
    unsigned char temp_light = 0;
    
    time_msg1++;
    time_msg2++;
    
    J1939_poll(5);
    
    time_msg1++;
    time_msg2++;
    while (J1939_RXsize())
    {
        J1939_Receive(&msg);
        if ( (msg.PDUformat == 0xFD) && (msg.PDUspecific == 0xC4) ) 
        {
            if (((msg.data[3]>>2) & 0x03) != 0x03)
            {
                if (((msg.data[3]>>2) & 0x03) == 0x01)
                {
                    LATC |= 0xC0;
                    time_msg1 = 0;
                }
            } 
        }
        
        else if ( (msg.PDUformat == 0xFE) && (msg.PDUspecific == 0x4F) )
        {
            if (((msg.data[0]>>4) & 0x03) != 0x03)
            {
                if (((msg.data[0]>>4) & 0x03) == 0x01)
                {
                    LATC |= 0xC0;
                    time_msg2 = 0;
                }
            }            
        } 
        
    }
    
    if ( (time_msg1 > 1000) && (time_msg2 > 1000) )
    {
       LATC &= ~0xC0; 
       time_msg1 = 1000;
       time_msg2 = 1000; 
    }
    /*
    else
    {
        if (time_msg1 > 200)
            time_msg1 = 200;
        else
            time_msg1++;
            
        if (time_msg2 > 200)
            time_msg2 = 200;
        else
            time_msg2++;
    }
    */
    
}
