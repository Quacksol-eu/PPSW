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
	enum StepState {STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
	enum StepState eStepState = STATE0;
	LedInit();
	KeyboardInit();
	while (1) 
	{
		switch(eStepState)
		{
			case STATE0:
				LedStepLeft();
				eStepState = STATE1;
				break;
			case STATE1:
				LedStepLeft();
				eStepState = STATE2;
				break;
			case STATE2:
				LedStepLeft();
				eStepState = STATE3;
				break;
			case STATE3:
				LedStepRight();
				eStepState = STATE4;
				break;
			case STATE4:
				LedStepRight();
				eStepState = STATE5;
				break;
			case STATE5:
				LedStepRight();
				eStepState = STATE0;
				break;
		}
		Delay(500);
	}
}