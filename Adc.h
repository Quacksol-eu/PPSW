void ReadAdc(void);
void AdcInit();
enum AdcStatus {READ,UPDATE};
struct AdcData
{
	volatile unsigned int uiAdcValue;
	volatile enum AdcStatus eAdcStatus;
};
