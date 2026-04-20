#include "LED.h" 
#include "KEYBOARD.h" 

void Delay(iDelay)
{
	int iTimeCount;
	iDelay = iDelay*12000;
	for (iTimeCount=0; iTimeCount < iDelay; iTimeCount++){}
}

int main() 
{
	enum LedState{LED_LEFT, LED_RIGHT};
	enum LedState eLedState = LED_LEFT;
	LedInit();
	KeyboardInit();
	while (1) 
	{
		switch(eLedState)
		{
			case LED_LEFT:
				LedStepLeft();
				eLedState = LED_RIGHT;
				break;
			case LED_RIGHT:
				LedStepRight();
				eLedState = LED_LEFT;
				break;
		
		}
		Delay(100);
	}
}