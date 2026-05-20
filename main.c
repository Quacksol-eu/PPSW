#include "uart.h"
#include "string.h"
#include "decode.h"
#include "Adc.h"
#include "servo.h"
extern struct RecieverBuffer sRecieverBuffer;
extern struct TransmiterBuffer sTransmiterBuffer;
extern volatile struct AdcData sAdc0;
char cAdcBase[20] = "Value ";

int main()
{
	unsigned int uiServoPos;
	unsigned int uiCopyOfAdcValue;
	ServoInit(100);
	AdcInit();
	while(1)
	{
		if (sAdc0.eAdcStatus == READ)
		{
			uiCopyOfAdcValue = sAdc0.uiAdcValue;
			sAdc0.eAdcStatus = UPDATE;
			uiServoPos = (uiCopyOfAdcValue * 47) / 1023;
			ServoGoTo(uiServoPos);
		}
	}
}