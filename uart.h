#define RECIEVER_SIZE 20
#define TRANSMITER_SIZE 20
#include <LPC21XX.H>
void UART_InitWithInt(unsigned int uiBaudRate);
extern volatile char cOdebranyZnak;
enum eRecieverStatus {EMPTY, READY, OVERFLOW};
struct RecieverBuffer
{ 
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};
enum eTransmiterStatus {FREE, BUSY};
struct TransmiterBuffer
{
	char cData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char cCharCtr;
};
char cTransmiter_GetCharacterFromBuffer();
enum eTransmiterStatus Transmiter_GetStatus(void);
void Transmiter_SendString(char cString[]);