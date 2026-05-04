#include <LPC21xx.H>
#include "LED.h"
#include "uart.h"
#include "servo.h"

extern volatile char cOdebranyZnak;

int main()
{
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(50);
	while (1)
	{
		switch(cOdebranyZnak)
		{
		case('1'):
		{
			ServoGoTo(sServo.uiDesiredPosition + 12);
			cOdebranyZnak = 0;
			break;
		}
		case('c'):
		{
			ServoCalib();
			cOdebranyZnak = 0;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}