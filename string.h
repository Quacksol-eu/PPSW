void Reciever_PutCharacterToBuffer(char cCharacter);
void Reciever_GetStringCopy(char *ucDestination);
enum eRecieverStatus eReciever_GetStatus(void);
enum CompResult {DIFFERENT, EQUAL};
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void CopyString(char pcSource[], char pcDestination[]);
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);