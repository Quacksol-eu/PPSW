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
	enum StepState {MOVE, STOP};
	enum StepState eStepState = MOVE;
	LedInit();
	KeyboardInit();
	while (1) 
	{
		switch(eStepState)
		{
			case(MOVE):
			{
				if (eKeyboardRead() == BUTTON_0)
				{
					eStepState = STOP;
				}
				else
				{
					LedStepRight();
				}
				break;
			}
			case(STOP):
			{
				if (eKeyboardRead() == BUTTON_2)
				{
					eStepState = MOVE;
				}
				break;
			}
		}
		Delay(250);
	}
}