#define USE_OR_MASKS
#include <p18cxxx.h>
#include "j1939.h"
#include "adc.h"
#include "timers.h"

#pragma config XINST = OFF
#pragma config OSC=IRCIO7, WDT=OFF, LVP=OFF, MCLRE = OFF, PBADEN = ON //, PWRT = ON //OSC=HS
#define Rop              210.0

unsigned char name[8] = {0};
unsigned int TimerValue = 0;

unsigned int ADCResult=0;
float voltage=0;

void adc_init(void);
void mcu_init(void);
void timer_init(void);
void User_Timer(void);

float valueR(unsigned char channel);
void SendAirTemperatur(unsigned int value);
void SendFuelLevel(unsigned char value);
unsigned int CalcAirTemperatur_For_J1939(void);
unsigned char CalcFuelLevel_For_J1939(void);

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

    LATC = 0xFF;
	TRISC = 0;		//порт C на выход RC0-RC7

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
	TimerValue++;
	if (TimerValue == 120)
	{
		SendAirTemperatur(CalcAirTemperatur_For_J1939());

	}
			
	if (TimerValue == 240)
	{			
		SendFuelLevel(CalcFuelLevel_For_J1939());		
		TimerValue = 0;
	}

}

float valueR(unsigned char channel)
{              
//               
//             _____       _____
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

void SendFuelLevel(unsigned char value)  // PGN 65276 Dash Display - DD , SPN 96 Fuel Level (Byte 2)  
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
	unsigned int result = 0;
	float C = 0.0;
		
	// C = 2,5641*R - 256,24
	// Температура 	| Сопротивление
	// 		-40		|	84.3
	//		0		|	100.0
	//		40		|	115.5
	C = 2.5641*valueR(1)-256.24;
	result =( unsigned int)((C + 273.0)*32);
	
	return result;
}

unsigned char CalcFuelLevel_For_J1939(void)
{
	unsigned char result = 0;
	float L = 0.0;  //Level %
    float R = 0.0;

	//% = 0,00020957*I31*I31-0,3759869*I31+164,76
	//  Уровень %  	|  Сопротивление
	//    	0		|	761.0
	//		50		|	390.0
	//		100		|	193.5
  	R = valueR(0);
	if (R > 761.0)
		L = 0.0;
	else if (R < 193.5)
		L = 100.0;
	else
		L = 0.00020957*R*R - 0.3759869*R + 164.76;
	result = (unsigned char)(L * 2.5);	
	
	return result;
}