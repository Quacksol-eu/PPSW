#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_NR 2 
#define MAX_KEYWORD_STRING_LTH 10 
#define NULL '\0'
#include "string.h"

enum Result { OK, ERROR };
enum KeywordCode { CLB, GT }; 
enum TokenType { KEYWORD, NUMBER, STRING };
enum WorkType { TOKEN, DELIMITER };

union TokenValue
{
    enum KeywordCode eKeyword;
    unsigned int uiNumber;
    char* pcString;
};  

struct Token
{
    enum TokenType eType;
    union TokenValue uValue;
};   

struct Keyword
{
    enum KeywordCode eCode;  
    char cString[MAX_KEYWORD_STRING_LTH + 1];  
};  

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr; 

struct Keyword asKeywordList[MAX_KEYWORD_NR] =
{
    {CLB, "calib"},
    {GT, "goto" },
};  

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar)
{
    unsigned char ucCounter;
    for(ucCounter = 0; pcString[ucCounter] != '\0'; ucCounter++)
    {
        if(pcString[ucCounter] == cOldChar)
        {
            pcString[ucCounter] = cNewChar;
        }
    }
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue)
{
    unsigned char ucCharCounter;
    unsigned char ucCurrentChar;

    *puiValue = 0;

    if ((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == '\0'))
    {
        return ERROR;
    }

    for (ucCharCounter = 2; ucCharCounter <= 6; ucCharCounter++)
    {
        ucCurrentChar = pcStr[ucCharCounter];

        if (ucCurrentChar == '\0')
        {
            return OK;
        }
        else if (ucCharCounter == 6)
        {
            return ERROR;
        }

        *puiValue = *puiValue << 4;

        if (ucCurrentChar >= '0' && ucCurrentChar <= '9')
        {
            ucCurrentChar = ucCurrentChar - '0';
        }
        else if (ucCurrentChar >= 'A' && ucCurrentChar <= 'F')
        {
            ucCurrentChar = ucCurrentChar - 'A' + 10;
        }
        else
        {
            return ERROR;
        }

        *puiValue |= ucCurrentChar;
    }
    return ERROR;
}

unsigned char ucFindTokensInString(char *pcString)
{  
    enum WorkType eTryb = DELIMITER;
    unsigned char ucLocalTokenNr = 0;
    unsigned char ucArrayIndex;
    unsigned char ucCurrentCharacter;
   
    for(ucArrayIndex = 0;; ucArrayIndex++)
    {          
        ucCurrentCharacter = pcString[ucArrayIndex];
         
        switch(eTryb)
        {
            case TOKEN:  
                if(ucLocalTokenNr == MAX_TOKEN_NR || ucCurrentCharacter == '\0')
                {
                    return ucLocalTokenNr;  
                }  
                else if(ucCurrentCharacter == ' ')
                {  
                    eTryb = DELIMITER;  
                }  
                break;  

            case DELIMITER:  
                if(ucCurrentCharacter == '\0')
                {  
                    return ucLocalTokenNr;  
                }  
                else if(ucCurrentCharacter != ' ')
                {  
                    eTryb = TOKEN;  
                    asToken[ucLocalTokenNr].uValue.pcString = pcString + ucArrayIndex;
                    ucLocalTokenNr++;
                }  
                break;  
        }  
    }  
}  

enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode)
{  
    unsigned char ucArrayIndex;    
 
    for(ucArrayIndex = 0; ucArrayIndex < MAX_KEYWORD_NR; ucArrayIndex++)
    {  
        if(EQUAL == eCompareString(asKeywordList[ucArrayIndex].cString, pcStr))
        {
            *peKeywordCode = asKeywordList[ucArrayIndex].eCode;
            return OK;
        }  
    }  
    return ERROR;  
}  
 
void DecodeTokens(void)
{
    unsigned char ucArrayIndex;
    struct Token *psCurrentToken;
    unsigned int uiTokenValue;
    enum KeywordCode eKodTokena;
 
    for(ucArrayIndex = 0; ucArrayIndex < ucTokenNr; ucArrayIndex++)
    {  
        psCurrentToken = &asToken[ucArrayIndex];
 
        if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue))
        {  
            psCurrentToken->eType = NUMBER;  
            psCurrentToken->uValue.uiNumber = uiTokenValue;  
        }  
        else if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eKodTokena))
        {  
            psCurrentToken->eType = KEYWORD;  
            psCurrentToken->uValue.eKeyword = eKodTokena;  
        }  
        else
        {  
            psCurrentToken->eType = STRING;  
        }  
    }  
}
void DecodeMsg(char *pcString)
{
    ucTokenNr = ucFindTokensInString(pcString);  
    ReplaceCharactersInString(pcString, ' ', NULL);
    DecodeTokens();  
}