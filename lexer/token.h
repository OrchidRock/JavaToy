#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include "tag.h"

class Token {
public:
    int tag;
    Token(int t);
    Token(Token* other);
    std::string toString();
};

class Num : public Token {
public:
    int value;
    Num(int v);
    std::string toString();
};


class Word : public Token {
public:
    std::string lexeme = "";
    Word(std::string s, int tag);
    Word(Word* other);
    std::string toString();
    static Word* And;
    static Word* Or;
    static Word* eq;
    static Word* ne;
    static Word* le;
    static Word* ge;
    static Word* minus;
    static Word* True;
    static Word* False;
    static Word* temp;
    
};

class Real : public Token {
public:
    float value;
    Real(float v);
    std::string toString();
};

#endif
