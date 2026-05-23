enum AdcStatus {READ,UPDATE,WAITING};
struct AdcData
{
	volatile unsigned int uiAdcValue;
	volatile enum AdcStatus eAdcStatus;
};

void AdcInitBurst();
void AdcInitOnlyOnStart();
void StartAdcConversion();
