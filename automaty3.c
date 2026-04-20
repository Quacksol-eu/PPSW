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
	enum StepState {LEFT, RIGHT};
	enum StepState eStepState = LEFT;
	LedInit();
	KeyboardInit();
	while (1) 
	{
		switch(eStepState)
		{
			case(LEFT):
			{
				if (ucStepCounter <= 2)
				{
					LedStepLeft();
					ucStepCounter++;
				}
				else
				{
					eStepState = RIGHT;
					continue;
				}
				break;
			}
			case(RIGHT):
			{
				if (ucStepCounter <= 5)
				{
					LedStepRight();
					ucStepCounter++;
				}
				else
				{
					eStepState = LEFT;
					ucStepCounter = 0;
					continue;
				}
				break;
			}
		}
		Delay(500);
	}
}