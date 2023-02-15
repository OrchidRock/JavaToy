#include "expr.h"
#include <string>


Expr::Expr(Token* tok, Type* p) : op(tok), type(p) {}
Expr::~Expr() {
    if (op) delete op;
    if (type) delete type;
}

Expr* Expr::gen() { return this; }
Expr* Expr::reduce() { return this; }
void Expr::jumping(int t, int f) {
    emitjumps(toString(), t, f);
}
void Expr::emitjumps(std::string test, int t, int f) {
    
}
std::string Expr::toString() { return op->toString(); }

Id::Id(Word* id, Type* p, int b) : Expr(id, p), offset(b) {}

Op::Op(Token* tok, Type* p) : Expr(tok, p){}
Expr* Op::reduce() {
    Expr* x = gen();
    Temp* t = new Temp(type);
    emit(t->toString() + "=" + x->toString());
    return t;
}

int Temp::count = 0;
Temp::Temp(Type* p) : Expr(new Word(Word::temp), p) {
    number = count++; 
}
std::string Temp::toString(){
        return std::string("t") + std::to_string(number);
    }
