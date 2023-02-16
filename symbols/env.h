#ifndef __ENV_H__
#define __ENV_H__

#include "../lexer/token.h"
#include "../inter/expr.h"
#include <map>

typedef std::map<Token*, Id*> envHashTable;

class Env {
private:
    envHashTable table;
protected:
    Env* prev;
public:
    Env(Env* n);
    ~Env();
    
    void put(Token* w, Id* i);//{table.insert(envHashTable::value_type(w, i));}
    Id* get(Token* w);
    
};


#endif
