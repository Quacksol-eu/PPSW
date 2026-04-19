#include <LPC21xx.H>
#include "timer.h"
#define NULL '\0'
#define LED0_bm 0x10000
#define LED3_bm 0x80000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED0123_bm 0xF0000
#define S0_bm 0x0000000010 
#define S1_bm 0x0000000040 
#define S2_bm 0x0000000020 
#define S3_bm 0x0000000080 
#define S0123_bm 0x00000000F0 
unsigned int uiCurrentStep = 0;
void Delay(iDelay)
{
	int iTimeCount;
	iDelay = iDelay*12000;
	for (iTimeCount=0; iTimeCount < iDelay; iTimeCount++){}
}
void LedInit()
{
	IO1DIR = IO1DIR | LED0123_bm;
	IO1SET = LED0_bm;
}
void LedOn(ucLedIndeks)
{
	switch (ucLedIndeks)
	{
		case (0):
		{
			IO1CLR = LED0123_bm & ~(LED0_bm);
			IO1SET = LED0_bm;
			break;
		}
		case (1):
		{
			IO1CLR = LED0123_bm & ~(LED1_bm);
			IO1SET = LED1_bm;
			break;
		}
		case (2):
		{
			IO1CLR = LED0123_bm & ~(LED2_bm);
			IO1SET = LED2_bm;
			break;
		}
		case (3):
		{
			IO1CLR = LED0123_bm & ~(LED3_bm);
			IO1SET = LED3_bm;
			break;
		}
	}
}
enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum KeyboardState eKeyboardInit()
{
	IO0DIR = IO0DIR & ~(S0123_bm);
	if ((IO0PIN & (S0_bm)) == 0)
	{
		return BUTTON_0;
	}
	else if ((IO0PIN & (S1_bm)) == 0)
	{
		return BUTTON_1;
	}
	else if ((IO0PIN & (S2_bm)) == 0)
	{
		return BUTTON_2;
	}
	else if ((IO0PIN & (S3_bm)) == 0)
	{
		return BUTTON_3;
	}
	else
	{
		return RELEASED;
	}
}

void StepLeft()
{
	uiCurrentStep++;
	LedOn((uiCurrentStep)%4);
}

int main(void) 
{
	LedInit();
	InitTimer0Match0(200);
	while(1) 
	{
		StepLeft();
		WaitOnTimer0Match();
		StepLeft();
		WaitOnTimer0Match();
		StepLeft();
		WaitOnTimer0Match();
		StepLeft();
		WaitOnTimer0Match();
	}
}