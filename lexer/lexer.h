#ifndef __LEXER_H__
#define __LEXER_H__

#include <map>
#include "token.h"

typedef std::map<std::string, Word*> lexerHashTable;

class Lexer {
private:
    Token * curr_tok = NULL;
public:
    static int line;
    char peek = ' ';
    

    lexerHashTable words;

    void reserve(Word* w);
    Lexer();
    ~Lexer();    

    void readch();
    bool readch(char c);

    Token* scan();
};

#endif
