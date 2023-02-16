#include "parser.h"
#include <string>

Parser::Parser(Lexer& l) : lex(l), look(NULL) { move(); }
Parser::~Parser() { 
    if (Stmt::Null) delete Stmt::Null;
    if (Constant::True) delete Constant::True;
    if (Constant::False) delete Constant::False;
}

void Parser::move() { look = lex.scan(); }

void Parser::error(std::string s) {
    throw std::string("Error near line " + std::to_string(lex.line) + ": " + s);
}

void Parser::match(int t) {
    if (look->tag == t) move();
    else error("syntax error");    
}

void Parser::program() {
    Stmt* s = block();
    int begin = s->newlabel();
    int after = s->newlabel();
    s->emitlabel(begin);
    s->gen(begin, after);
    s->emitlabel(after);

    delete s;
}

Stmt* Parser::block() {
    match('{');
    Env* savedEnv = top;
    top = new Env(top);
    //top->prev = savedEnv;
    decls();
    Stmt* s = stmts();
    match('}');
    
    delete top;
    top = savedEnv;

    return s;
}

void Parser::decls() {
    while( look->tag == Tag::BASIC) {
        Type* p = type();
        Word* tok = new Word(((Word*)look)->lexeme, look->tag);
        
        match(Tag::ID);
        match(';');
        
        Id* id = new Id(tok, p, used);
        top->put((Token*)p, id);
        used +=  p->width; 
    }

}

Type* Parser::type() {
    Type* p = new Type((Type*)look);
    match(Tag::BASIC);
    if (look->tag != '[') return p;
    else return dims(p);
}

Type* Parser::dims(Type* p) {
    match('[');
    int num = ((Num*)look)->value;
    match(Tag::NUM);
    match(']');
    
    if (look->tag == '[') p = dims(p);
    
    return new Array(num, p); 
}

Stmt* Parser::stmts() {
    if (look->tag == '}') return new Stmt();
    else return new Seq(stmt(), stmts());
}

Stmt* Parser::stmt() {
    Expr* x;
    Stmt* s;
    Stmt* s1;
    Stmt* s2;
    Stmt* savedStmt; // for break;
    
    switch(look->tag) {
    case ';' :
        move();
        return Stmt::Null;
    case Tag::IF:
        match(Tag::IF); match('('); x = boolean(); match(')');
        s1 = stmt();
        if(look->tag != Tag::ELSE) return new If(x, s1);
        match(Tag::ELSE);
        s2 = stmt();
        //return new Else(x, s1, s2);
        return NULL;
    }

    return NULL;
}

Expr* Parser::boolean() {
    return NULL;
}
