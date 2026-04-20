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
	unsigned char ucBlinkCounter = 0;
	enum StepState {RIGHT,LEFT,STOP,BLINK};
	enum StepState eStepState = STOP;
	LedInit();
	KeyboardInit();
	while (1) 
	{
		switch(eStepState)
		{
			case(STOP):
			{
				if (eKeyboardRead() == BUTTON_0)
				{
					eStepState = LEFT;
				}
				else if (eKeyboardRead() == BUTTON_2)
				{
					eStepState = RIGHT;
				}
				continue;
			}
			case(LEFT): 
			{
				if (eKeyboardRead() == BUTTON_1)
				{
					eStepState = STOP;
				}
				else if (eKeyboardRead() == BUTTON_3)
				{
					eStepState = BLINK;
				}
				else
				{
					LedStepLeft();
				}
				break;
			}
			case(RIGHT):
			{
				if (eKeyboardRead() == BUTTON_1)
				{
					eStepState = STOP;
				}
				else
				{
					LedStepRight();
				}
				break;
			}
			case(BLINK):
			{
				if (ucBlinkCounter <= 5)
				{
					if ((ucBlinkCounter%2) == 0)
					{
						LedOn(4);
					}
					else
					{
						LedOn(0);
					}
					ucBlinkCounter++;
				}
				else 
				{
					eStepState = RIGHT;
					ucBlinkCounter = 0;
				}
				break;
			}
		}
		Delay(100);
	}
}