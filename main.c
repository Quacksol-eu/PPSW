#include "Adc.h"
#include "servo.h"
extern volatile struct AdcData sAdc0;
extern struct TransmiterBuffer sTransmiterBuffer;

char cAdcBase[25] = "Value ";

int main()
{
	unsigned int uiAdcSavedValue;
	ServoInit(200);
	AdcInitOnlyOnStart();
	while(1)
	{
		switch(sAdc0.eAdcStatus)
		{
			case(READ):
			{
				uiAdcSavedValue = sAdc0.uiAdcValue;
				ServoGoTo((uiAdcSavedValue * 47) >> 10);
				sAdc0.eAdcStatus = UPDATE;	
				break;
			}
			case(UPDATE):
			{
				sAdc0.eAdcStatus = WAITING;
				StartAdcConversion();
				break;
			}
			case(WAITING):
			{
				break;
			}
		}
	}
}