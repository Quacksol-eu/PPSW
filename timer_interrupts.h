void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void));
void Timer1Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void));
struct Watch 
{ 
	unsigned char ucMinutes;
	unsigned char ucSeconds; 
  unsigned char fSecondsValueChanged;
  unsigned char fMinutesValueChanged;
};
