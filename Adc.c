#include <LPC21xx.H>
#include "Led.h"
enum AdcStatus {READ,UPDATE};

struct AdcData 
{
	volatile unsigned int uiAdcValue;
	volatile enum AdcStatus eAdcStatus;
};

volatile struct AdcData sAdc0;

__irq void ReadAdc(void)
{
    unsigned int uiVal;
    
    uiVal = ADDR; 
    uiVal = (uiVal >> 6) & 0x3FF; 
    
    sAdc0.uiAdcValue = uiVal;
    sAdc0.eAdcStatus = READ;
	
    VICVectAddr = 0x00; 
}

void AdcInit()
{
	PINSEL1 &= ~(3 << 24); 
	PINSEL1 |=  (1 << 24); 
	ADCR = ((1 << 1) | (3 << 8) | (1 << 21));
	VICVectAddr3 = (unsigned long)ReadAdc;
  VICVectCntl3 = (0x20 | 18);              
  VICIntEnable |= (1 << 18);             
  sAdc0.eAdcStatus = UPDATE;
}

void StartAdcConversion() 
{
    ADCR |= (1 << 24); 
}
