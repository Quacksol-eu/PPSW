#include <LPC21xx.H>
#include "Led.h"
enum AdcStatus {READ,UPDATE,WAITING};

struct AdcData 
{
	volatile unsigned int uiAdcValue;
	volatile enum AdcStatus eAdcStatus;
};

volatile struct AdcData sAdc0;

//////////TRYB BURST - ZMIANA JEDYNIE W STANIE UPDATE - ODCZYT STALE ///////////////

__irq void ReadAdcBurst(void)
{
    unsigned int uiVal;
    
    uiVal = ADDR;
		sAdc0.uiAdcValue = (uiVal >> 6) & 0x3FF;
		sAdc0.eAdcStatus = READ;
    VICVectAddr = 0x00; 
}

void AdcInitBurst()
{
    PINSEL1 &= ~(3 << 24); 
    PINSEL1 |=  (1 << 24); 
    
    ADCR = (1 << 1) | (4 << 8) | (1 << 16) | (1 << 21);
    
    VICVectAddr3 = (unsigned long)ReadAdcBurst;
    VICVectCntl3 = 0x20 | 18;             
    VICIntEnable |= (1 << 18);    
	
    sAdc0.eAdcStatus = UPDATE;
}

/////////////WYWOLANIE KONWERSJI FUNKCJA StartAdcConversions()///////////

__irq void ReadAdcOnlyOnStart(void)
{
    unsigned int uiVal;
    uiVal = ADDR;
		sAdc0.uiAdcValue = (uiVal >> 6) & 0x3FF;
		sAdc0.eAdcStatus = READ;
    VICVectAddr = 0x00; 
}

void AdcInitOnlyOnStart()
{
    PINSEL1 &= ~(3 << 24); 
    PINSEL1 |=  (1 << 24); 
    
    ADCR = (1 << 1) | (4 << 8) | (1 << 21);
    
    VICVectAddr3 = (unsigned long)ReadAdcOnlyOnStart;
    VICVectCntl3 = 0x20 | 18;             
    VICIntEnable |= (1 << 18);    
	
    sAdc0.eAdcStatus = UPDATE;
}

void StartAdcConversion()
{
	ADCR &= ~(7 << 24);
	ADCR |= (1 << 24); 
}

