#ifndef __EXPR_H__
#define __EXPR_H__

#include "node.h"
#include <string>

class Expr: public Node {
public:
    Token* op = NULL;
    Type* type = NULL;
    Expr(Token* tok, Type* p);    
    Expr(Expr* other);
    ~Expr();
     
    Expr* gen();
    Expr* reduce();
    virtual void jumping(int t, int f);
    void emitjumps(std::string test, int t , int f);
    virtual std::string toString();
};

class Id: public Expr {
public:
    int offset;
    Id(Word* id, Type* p, int b);
    ~Id() {}
};

class Temp: public Expr {
public:
    static int count;
    int number = 0;
    Temp(Type* p);
    ~Temp() {}
    std::string toString();
};

class Op: public Expr {
public:
    Op(Token* tok, Type* p);
    ~Op() {}
    Expr* reduce();
};

class Arith : public Op {
public:
    Expr* expr1;
    Expr* expr2;
    Arith(Token* tok, Expr* x1, Expr* x2);
    ~Arith();
    Expr* gen();
    std::string toString();
};

class Unary : public Op {
public:
    Expr* expr;
    Unary(Token* tok, Expr* x);
    ~Unary();
    Expr* gen();
    std::string toString();

};

class Constant : public Expr {
public:
    Constant(Token* tok, Type* p) : Expr(tok, p) {}
    Constant(int i) : Expr(new Num(i), new Type(Type::Int)) {}
    ~Constant() {}

    void jumping(int t, int f);
    static Constant* True;
    static Constant* False;

    bool operator==(Constant* other) {
        if(this->op == other->op && this->type == other->type)
            return true;
        else
            return false;
    }
};

class  Logical : public Expr {
public:
    Expr* expr1;
    Expr* expr2;
    Logical(Token* tok, Expr* x1, Expr* x2);
    ~Logical();
    Type* check(Type* p1, Type* p2);
    Expr* gen();
    std::string toString();
};

class Or : public Logical {
public:
    Or(Token* tok, Expr* x1, Expr* x2) : Logical(tok,x1,x2) {}
    ~Or() {}
    void jumping(int t, int f);  
};

class And : public Logical {
public:
    And(Token* tok, Expr* x1, Expr* x2) : Logical(tok,x1,x2) {}
    ~And() {}
    void jumping(int t, int f);  
};

class Not : public Logical {
public:
    Not(Token* tok, Expr* x2) : Logical(tok,NULL,x2) {}
    ~Not() {}
    void jumping(int t, int f);  
    std::string toString();
};

class Rel : public Logical {
public:
    Rel(Token* tok, Expr* x1, Expr* x2) : Logical(tok,x1,x2) {}
    Type* check(Type* p1, Type* p2);
    void jumping(int t, int f);
     
};

#endif
