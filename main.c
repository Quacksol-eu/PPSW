#include "uart.h"
#include "string.h"
#include "timer_interrupts.h"
#include "decode.h"
extern struct RecieverBuffer sRecieverBuffer;
extern struct TransmiterBuffer sTransmiterBuffer;
extern struct Watch sWatch;
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
	char cMsgBuffer[20];
	Timer0Interrupts_Init((1000000),&WatchUpdate);
	UART_InitWithInt(9600);
	while(1)
	{
		if (eReciever_GetStatus() == READY)
		{
			Reciever_GetStringCopy(cBufferRecieved);
			DecodeMsg(cBufferRecieved);
		}
		
		////////////////////////////////
	
		if (sTransmiterBuffer.eStatus == FREE)
		{
			if ((asToken[0].eType == KEYWORD) && (asToken[0].uValue.eKeyword == CLC) && (asToken[1].eType == NUMBER))
			{               
				CopyString("calc ", cMsgBuffer);
				AppendUIntToString((asToken[1].uValue.uiNumber * 2), cMsgBuffer);
				AppendString("\r\n", cMsgBuffer);
				
				Transmiter_SendString(cMsgBuffer);
				
				asToken[0].eType = STRING;
			}
			else if (sWatch.fMinutesValueChanged == 1)
			{
				sWatch.fMinutesValueChanged = 0;
				CopyString("min ", cMsgBuffer);
				AppendUIntToString(sWatch.ucMinutes, cMsgBuffer);
				AppendString("\r\n", cMsgBuffer);
				
				Transmiter_SendString(cMsgBuffer);
			}
			else if (sWatch.fSecondsValueChanged == 1)
			{
				sWatch.fSecondsValueChanged = 0;

				CopyString("sec ", cMsgBuffer);
				AppendUIntToString(sWatch.ucSeconds, cMsgBuffer);
				AppendString("\r\n", cMsgBuffer);
				
				Transmiter_SendString(cMsgBuffer);
			}
		}
   }
}
