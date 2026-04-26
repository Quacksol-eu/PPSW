#include <LPC21xx.H>

#define NULL '\0'

#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000

#define S0_bm 0x10 
#define S1_bm 0x40 
#define S2_bm 0x20 
#define S3_bm 0x80 

void Delay(iDelay)
{
	int iTimeCount;
	iDelay = iDelay*12000;
	for (iTimeCount=0; iTimeCount < iDelay; iTimeCount++){}
}

void LedInit()
{
	IO1DIR = IO1DIR | (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1SET = LED0_bm;
}

void LedOn(ucLedIndeks)
{
	IO1CLR = (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	switch (ucLedIndeks)
	{
		case (0):
		{
			IO1SET = LED0_bm;
			break;
		}
		case (1):
		{
			IO1SET = LED1_bm;
			break;
		}
		case (2):
		{
			IO1SET = LED2_bm;
			break;
		}
		case (3):
		{
			IO1SET = LED3_bm;
			break;
		}
	}
}

void KeyboardInit()
{
	IO0DIR = IO0DIR & ~(S0_bm|S1_bm|S2_bm|S3_bm);
}

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum KeyboardState eKeyboardRead()
{
	if ((IO0PIN & S0_bm) == 0)
	{
		return BUTTON_0;
	}
	else if ((IO0PIN & S1_bm) == 0)
	{
		return BUTTON_1;
	}
	else if ((IO0PIN & S2_bm) == 0)
	{
		return BUTTON_2;
	}
	else if ((IO0PIN & S3_bm) == 0)
	{
		return BUTTON_3;
	}
	else
	{
		return RELEASED;
	}
}

enum eStep {LEFT, RIGHT};
void LedStep(eStep)
{
	static unsigned int uiCurrentStep = 0;
	switch (eStep)
	{
		case(LEFT):
		{
			uiCurrentStep++;
			break;
		}
		case(RIGHT):
		{
			uiCurrentStep--;
			break;
		}
	}
	LedOn((uiCurrentStep)%4);
}

void LedStepLeft()
{
	LedStep(LEFT);
}
void LedStepRight()
{
	LedStep(RIGHT);
}
int main(void) 
{
	KeyboardInit();
	LedInit();
	while(1) 
	{
		switch (eKeyboardRead())
		{
			case (BUTTON_2):
			{
				LedStepRight();
				break;
			}
			case (BUTTON_1):
			{
				LedStepLeft();
				break;
			}
			default:
			{
				break;
			}
		}
		Delay(100);
	}
}