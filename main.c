#include "uart.h"
#include "servo.h"
#include "string.h"
#include "decode.h"
extern struct RecieverBuffer sRecieverBuffer;
extern volatile char cOdebranyZnak;

int main()
{
	 char cTempRecieved[RECIEVER_SIZE];
	 UART_InitWithInt(9600);
	 ServoInit(100);
	 while(1)
	 {
		if (eReciever_GetStatus() == READY)
		{
			Reciever_GetStringCopy(cTempRecieved);
			DecodeMsg(cTempRecieved);
		  if(ucTokenNr != 0)
			{
				if (asToken[0].eType == KEYWORD)
				{
					if (asToken[0].uValue.eKeyword == CLB)
					{
						ServoCalib();
					}
					if (asToken[0].uValue.eKeyword == GT)
					{
						ServoGoTo(asToken[1].uValue.uiNumber);
					}
				}
			}
		}
   }
}