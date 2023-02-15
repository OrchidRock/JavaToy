#ifndef __TYPE_H__
#define __TYPE_H__

#include <string>
#include "../lexer/token.h"
class Type : public Word {
public:
    int width = 0;
    Type(std::string s, int tag, int w);
    Type(Type* other);

    static bool numeric(Type& p);
    static Type* max(Type& p1, Type& p2);
    
    static Type* Int;
    static Type* Float;
    static Type* Char;
    static Type* Bool;

    bool operator== (const Type*& other) {
        if(lexeme == other->lexeme && tag == other->tag && 
                        width == other->width) 
            return true;
        else
            return false;        
    } 
};

class Array : public Type {
public:
    Type* of;
    int size = 1;
    Array(int sz, Type* p);
    ~Array();
    std::string toString();
};

#endif
