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
	unsigned char ucStepCounter = 0;
	enum StepState {MOVE, STOP};
	enum StepState eStepState = STOP;
	LedInit();
	KeyboardInit();
	while (1) 
	{
		switch(eStepState)
		{
			case(MOVE):
			{
				if (ucStepCounter <= 2)
				{
					LedStepRight();
					ucStepCounter++;
				}
				else
				{
					eStepState = STOP;
				}
				break;
			}
			case(STOP):
			{
				if (eKeyboardRead() == BUTTON_0)
				{
					eStepState = MOVE;
					ucStepCounter = 0;
				}
				continue;
			}
		}
		Delay(500);
	}
}