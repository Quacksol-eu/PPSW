
#define TOKEN_H

#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_NR 2 
#define MAX_KEYWORD_STRING_LTH 10 

// Definicje typów wyliczeniowych
enum Result { OK, ERROR };
enum KeywordCode { CLB, GT }; 
enum TokenType { KEYWORD, NUMBER, STRING };

// Definicje struktur i unii
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