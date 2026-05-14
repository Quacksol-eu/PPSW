#include "uart.h"
#include "string.h"
#include "timer_interrupts.h"
#include "decode.h"
extern struct RecieverBuffer sRecieverBuffer;
extern struct TransmiterBuffer sTransmiterBuffer;
extern struct Watch sWatch;
char cTimerSecondsBase[15] = "sec ";
char cTimerMinutesBase[15] = "min ";
char cCalcBase[15] = "calc ";
char cBufferRecieved[20];

void WatchUpdate()
{
    sWatch.ucSeconds++;
    if (sWatch.ucSeconds == 60)
    {
        sWatch.ucSeconds = 0;
        sWatch.ucMinutes++;
        sWatch.fMinutesValueChanged = 1;
    }
		sWatch.fSecondsValueChanged = 1;
}

int main()
{
	Timer0Interrupts_Init((1000000),&WatchUpdate);
	UART_InitWithInt(9600);
	while(1)
	{
		if (eReciever_GetStatus() == READY)
		{
			Reciever_GetStringCopy(cBufferRecieved);
			DecodeMsg(cBufferRecieved);
		}
		if ((sTransmiterBuffer.eStatus == FREE) && ((asToken[0].eType == KEYWORD) && (asToken[0].uValue.eKeyword == CLC)))
		{
			if(asToken[1].eType == NUMBER)
      {				
				AppendUIntToString((asToken[1].uValue.uiNumber * 2) , cCalcBase);
				Transmiter_SendString(cCalcBase);
				CopyString("calc ", cCalcBase);
				asToken[1].uValue.uiNumber = 0;
        asToken[1].uValue.uiNumber = 0;				
				asToken[0].eType = STRING;
				asToken[1].eType = STRING;
		  }
		}
		if ((sTransmiterBuffer.eStatus == FREE) && (sWatch.fMinutesValueChanged == 1))
		{
			sWatch.fMinutesValueChanged = 0;
			AppendUIntToString(sWatch.ucMinutes, cTimerMinutesBase);
			Transmiter_SendString(cTimerMinutesBase);
			CopyString("min ", cTimerMinutesBase);
		}
		else if ((sTransmiterBuffer.eStatus == FREE) && (sWatch.fSecondsValueChanged == 1))
		{
			sWatch.fSecondsValueChanged = 0;
			AppendUIntToString(sWatch.ucSeconds, cTimerSecondsBase);
			Transmiter_SendString(cTimerSecondsBase);
			CopyString("sec ", cTimerSecondsBase);
		}
		
	}
}