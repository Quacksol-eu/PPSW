#include "uart.h"
#include "string.h"
#include "timer_interrupts.h"
#include "decode.h"
#include "Adc.h"
#include "LED.h"
#include "servo.h"
extern struct RecieverBuffer sRecieverBuffer;
extern struct TransmiterBuffer sTransmiterBuffer;
extern volatile struct AdcData sAdc0;
char cAdcBase[15] = "Value ";

int main()
{
	unsigned int uiServoPos;
	ServoInit(100);
	ServoGoTo(12);
	AdcInit();
	Timer1Interrupts_Init((1000000/20),&StartAdcConversion);
	UART_InitWithInt(9600);
	while(1)
	{
		if ((1) && (sAdc0.eAdcStatus == READ))
		{
			AppendUIntToString(sAdc0.uiAdcValue , cAdcBase);
			Transmiter_SendString(cAdcBase);
			CopyString("Value ", cAdcBase);
			sAdc0.eAdcStatus = UPDATE;
			uiServoPos = (sAdc0.uiAdcValue * 47) / 1023;
      ServoGoTo(uiServoPos);
		}
	}
}