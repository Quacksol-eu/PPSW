#define RECIEVER_SIZE 20
void UART_InitWithInt(unsigned int uiBaudRate);
extern volatile char cOdebranyZnak;
enum eRecieverStatus {EMPTY, READY, OVERFLOW};
struct RecieverBuffer
{ 
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};

