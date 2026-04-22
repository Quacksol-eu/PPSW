#include <LPC21xx.H>
//Test
#define NULL '\0'

#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000

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
		default:
		{
		}
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