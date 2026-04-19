#include <LPC21xx.H>
#define MR0 (1<<0)
#define InteruptOnMR0 (1<<0)
#define CounterEnable (1<<0)
#define CounterReset (1<<1) 
#define ResetOnMR0 (1<<1)

void InitTimer0(void)
{
	T0TCR = CounterEnable;
}

void WaitOnTimer0(unsigned int uiTime)
{ 
  T0TCR |= CounterReset; 
	T0TCR &= (~CounterReset);
	while (T0TC < (15000 * uiTime)) {}
}

void InitTimer0Match0(unsigned int iDelayTime)
{      
		T0MR0 = (15000 * iDelayTime);
		T0TCR |= CounterReset;
		T0TCR &= (~CounterReset);
		T0MCR |= (InteruptOnMR0 | ResetOnMR0);
		T0TCR |= CounterEnable;
}

void WaitOnTimer0Match()
{
	while((T0IR&MR0) == 0) {}
	T0IR = MR0;
}