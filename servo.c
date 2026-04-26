#include <LPC21xx.H>
#include "LED.h"
#include "timer_interrupts.h"
#define DETECTOR_PIN (1<<10)

void DetectorInit()
{
	IO0DIR &= (~DETECTOR_PIN);
}

enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector()
{ 
	if((IO0PIN&DETECTOR_PIN)==0)
	{ 
		return ACTIVE; 
	} 
	else
	{ 
		return INACTIVE; 
	} 
}

enum ServoState {CALIB, IDLE, IN_PROGRESS};

struct Servo
{
enum ServoState eState; 
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
}; 

struct Servo sServo;

void Automat() 
{
	unsigned int uiCur = sServo.uiCurrentPosition;
	unsigned int uiDes = sServo.uiDesiredPosition;
	switch(sServo.eState)
	{
		case(CALIB):
		{
			if (eReadDetector() == INACTIVE)
			{
				LedStepRight();
			}
			else 
			{
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
				sServo.eState = IDLE;
			}
			break;
		}
		case(IN_PROGRESS):
		{
			if (uiCur < uiDes)
			{
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else if (uiCur > uiDes)
			{
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		}
		case(IDLE):
		{
			if (uiDes != uiCur)
			{
				sServo.eState = IN_PROGRESS;
			}
			break;
		}
	}	
}

void ServoInit(unsigned int uiServoFrequency)
{ 
 sServo.eState = CALIB;  
 LedInit();
 Timer0Interrupts_Init((1000000/uiServoFrequency),&Automat);
} 

void ServoCalib(void)
{ 
 sServo.eState = CALIB;  
} 

void ServoGoTo(unsigned int uiPosition)
{ 
 sServo.uiDesiredPosition = uiPosition; 
}
