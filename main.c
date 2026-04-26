#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "KEYBOARD.h" 
#include "servo.h"

int main ()
{
	KeyboardInit();
	ServoInit(200);
	while(1){
	 	if (eKeyboardRead() == BUTTON_0)
		{
			ServoCalib();
		}
		if (eKeyboardRead() == BUTTON_1)
		{
			ServoGoTo(12);
		}
		if (eKeyboardRead() == BUTTON_2)
		{
			ServoGoTo(24);
		}
		if (eKeyboardRead() == BUTTON_3)
		{
			ServoGoTo(36);
		}
	}
}

