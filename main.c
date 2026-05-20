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

int main()
{
	unsigned int uiServoPos;
	ServoInit(100);
	AdcInit();
	Timer1Interrupts_Init((1000000/20),&StartAdcConversion);
	while(1)
	{
		if (sAdc0.eAdcStatus == READ)
		{
			sAdc0.eAdcStatus = UPDATE;
			uiServoPos = (sAdc0.uiAdcValue * 47) / 1023;
			ServoGoTo(uiServoPos);
		}
	}
}