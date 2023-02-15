#ifndef __PARSER_H__
#define __PARSER_H__

#include "../lexer/lexer.h"
#include "../lexer/token.h"
#include "../symbols/env.h"
#include "../inter/stmt.h"
#include "../inter/expr.h"

class Parser {
private:
    Lexer& lex;
    Token* look;

public:
    Env* top = NULL;
    int used = 0;

    Parser(Lexer& l);
    ~Parser();

    void move();
    void error(std::string s);
    void match(int t);
    void program();
    Stmt* block();
    void decls();
    Type* type();
    Type* dims(Type* p);
    Stmt* stmts();
    Stmt* stmt();
    Stmt* assign();
    Expr* boolean();
    Expr* join();
    Expr* equality();
    Expr* rel();
    Expr* expr();
    Expr* term();
    Expr* unary();
    Expr* factor();
    //Access offset(Id a);
        
};


#endif
