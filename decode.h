#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_NR 3
#define MAX_KEYWORD_STRING_LTH 10 

enum Result { OK, ERROR };
enum KeywordCode { CLC,CLB, GT }; 
enum TokenType { KEYWORD, NUMBER, STRING };

union TokenValue {
    enum KeywordCode eKeyword;
    unsigned int uiNumber;
    char* pcString;
};  

struct Token {
    enum TokenType eType;
    union TokenValue uValue;
};   

struct Keyword {
    enum KeywordCode eCode;  
    char cString[MAX_KEYWORD_STRING_LTH + 1];  
};  

extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr; 

void DecodeMsg(char *pcString);