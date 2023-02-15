#ifndef __STMT_H__
#define __STMT_H__

#include "node.h"
#include "expr.h"

class Stmt: public Node {
public:
    Stmt();
    
    int after = 0;
    void gen(int b, int a);

    static Stmt* Null;
    static Stmt* Enclosing;
};


class Seq : public Stmt {
public:
    Stmt* stmt1 = NULL;
    Stmt* next = NULL;

    Seq(Stmt* stmt1, Stmt* next);
    ~Seq();

    void gen(int b, int a);

};

class If: public Stmt {
public:
    Expr* expr;
    Stmt* stmt;
    If(Expr* x, Stmt* s);
    void gen(int b, int a);
};

class Else: public Stmt {
        
};

#endif
