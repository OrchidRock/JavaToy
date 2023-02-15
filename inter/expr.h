#ifndef __EXPR_H__
#define __EXPR_H__

#include "node.h"

class Expr: public Node {
public:
    Token* op = NULL;
    Type* type = NULL;
    Expr(Token* tok, Type* p);    
    ~Expr();
     
    Expr* gen();
    Expr* reduce();
    void jumping(int t, int f);
    void emitjumps(std::string test, int t , int f);
    std::string toString();
};

class Id: public Expr {
public:
    int offset;
    Id(Word* id, Type* p, int b);
};

class Temp: public Expr {
public:
    static int count;
    int number = 0;
    Temp(Type* p);
    std::string toString();
};

class Op: public Expr {
public:
    Op(Token* tok, Type* p);
    Expr* reduce();
};

class Arith : public Op {
public:
    Expr expr1, expr2;
    Arith(Token tok, Expr x1, Expr x2);
    Expr gen();
    std::string toString();
};

class Unary : public Op {};

#endif
