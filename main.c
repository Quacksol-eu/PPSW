#include <LPC21xx.H>
#include "LED.h"
#include "timer_interrupts.h"
#include "KEYBOARD.h" 

#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002

#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

#define VIC_TIMER0_CHANNEL_NR 4

#define mIRQ_SLOT_ENABLE 0x00000020
void Automat() 
{
	static unsigned char ucBlinkCounter = 0;
	enum StepState {RIGHT,LEFT,STOP,BLINK};
	static enum StepState eStepState = STOP;
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
			break;
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
}
int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(200000,&Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}



