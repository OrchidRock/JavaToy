#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include "../lexer/token.h"
#include "../symbols/type.h"

class Node {
public:
    int lexline = 0;
    Node();
    void error(std::string s);

    static int labels;
    
    int newlabel();
    void emitlabel(int i);
    void emit(std::string s);
};




#endif
