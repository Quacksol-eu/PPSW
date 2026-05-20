#define NULL '\0'
#include "uart.h"
extern struct RecieverBuffer sRecieverBuffer;

void CopyString(char pcSource[], char pcDestination[]){ 

 unsigned char ucCharacterCounter;
 for (ucCharacterCounter=0; pcSource[ucCharacterCounter] != NULL; ucCharacterCounter++ )
	{
   pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter]; 
  } 
	pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter]; 
}

void AppendString(char pcSourceStr[], char pcDestinationStr[])
{
	unsigned char ucCharacterCounter;
	for (ucCharacterCounter = 0; pcDestinationStr[ucCharacterCounter] != NULL; ucCharacterCounter++)
	{
	}
	CopyString(pcSourceStr, pcDestinationStr + ucCharacterCounter);
}

void UIntToHexStr(unsigned int uiValue, char pcStr[])
{
    unsigned int uiNibbleCounter;
    unsigned int uiCurrentNibble;

    pcStr[0] = '0';
    pcStr[1] = 'x';

    for (uiNibbleCounter = 0; uiNibbleCounter < 4; uiNibbleCounter++)
    {
        uiCurrentNibble = ((uiValue >> (uiNibbleCounter * 4)) & 0x000F);

        if (uiCurrentNibble < 10)
        {
            pcStr[5 - uiNibbleCounter] = '0' + uiCurrentNibble;
        }
        else
        {
            pcStr[5 - uiNibbleCounter] = 'A' + (uiCurrentNibble - 10);
        }
    }

    pcStr[6] = NULL;
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[])
{
    unsigned char ucCharacterCounter;

    for (ucCharacterCounter = 0; pcDestinationStr[ucCharacterCounter] != NULL; ucCharacterCounter++)
    {
    }

    UIntToHexStr(uiValue, &pcDestinationStr[ucCharacterCounter]);
}

enum CompResult {DIFFERENT, EQUAL};

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; (pcStr1[ucCharacterCounter] != '\0') || (pcStr2[ucCharacterCounter] != '\0'); ucCharacterCounter++)
    {
        if(pcStr1[ucCharacterCounter] != pcStr2[ucCharacterCounter])
        {
            return DIFFERENT;
        }
    }

    return EQUAL;
}

enum eRecieverStatus eReciever_GetStatus(void)
{
	switch(sRecieverBuffer.eStatus)
	{
		case(EMPTY):
		{
			return EMPTY;
			break;
		}
		case(READY):
		{
			return READY;
			break;
		}
		case(OVERFLOW):
		{
			return OVERFLOW;
			break;
		}
	}
}

void Reciever_GetStringCopy(char *ucDestination)
{
	unsigned char i;
	while(eReciever_GetStatus() != READY);
	CopyString(sRecieverBuffer.cData, ucDestination);
	for (i = 0; i < RECIEVER_SIZE; i++) 
	{
      sRecieverBuffer.cData[i] = 0;
  }
	sRecieverBuffer.eStatus = EMPTY;
}