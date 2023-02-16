#include "expr.h"
#include <string>
#include <iostream>

Expr::Expr(Token* tok, Type* p) : op(tok), type(p) {}
Expr::~Expr() {
    std::cout << "expr delete" << std::endl;
    if(op) delete op;
    if(type) delete type;
}

Expr* Expr::gen() { return this; }
Expr* Expr::reduce() { return this; }
void Expr::jumping(int t, int f) {
    emitjumps(toString(), t, f);
}
void Expr::emitjumps(std::string test, int t, int f) {
    if(t != 0 && f != 0) {
        emit(std::string("if ") + test + " goto L" + std::to_string(t));
        emit(std::string("goto L") + std::to_string(f));
    }
    else if (t != 0) emit(std::string("if ") + test + " goto L" + std::to_string(t));
    else if (f != 0) emit(std::string("iffalse ") + test + " goto L" + std::to_string(f));
    else ;
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

Arith::Arith(Token* tok, Expr*  x1, Expr* x2) : 
            Op(tok, NULL), expr1(x1), expr2(x2) {
    type = new Type(Type::max(expr1->type, expr2->type));
    if(type == NULL) error("type error");
}
Arith::~Arith() {
    if (expr1)  delete expr1;    
    if (expr2)  delete expr2;    
}
Expr* Arith::gen() {
    return new Arith(op, expr1->reduce(), expr2->reduce());
}
std::string Arith::toString() {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}


Unary::Unary(Token* tok, Expr* x) : Op(tok, NULL), expr(x) {
    type = new Type(Type::max(Type::Int, expr->type));
    if (type == NULL) error("type error");
}
Unary::~Unary() {
    if (expr) delete expr;
}
Expr* Unary::gen() {
    return new Unary(op, expr->reduce());
}
std::string Unary::toString() {
    return op->toString() + " " + expr->toString();
}

Constant* Constant::True = new Constant(new Word(Word::True), new Type(Type::Bool));
Constant* Constant::False = new Constant(new Word(Word::False), new Type(Type::Bool));
void Constant::jumping(int t, int f){
    if(this == True && t != 0) emit(std::string("goto L") + std::to_string(t)); 
    else if(this == False && f != 0) emit(std::string("goto L") + std::to_string(f));
}


Logical::Logical(Token* tok, Expr* x1, Expr* x2) :
          Expr(tok, NULL), expr1(x1), expr2(x2){
    type = check(expr1->type, expr2->type);
    if(type == NULL) error("type error");
}
Logical::~Logical(){
    if (expr1)  delete expr1;    
    if (expr2)  delete expr2;    
}
Type* Logical::check(Type* p1, Type* p2) {
    if (p1 == Type::Bool && p2 == Type::Bool) return new Type(Type::Bool);
    else return NULL;
}
Expr* Logical::gen() {
    int f = newlabel();
    int a = newlabel();
    Temp* tmp = new Temp(new Type(type));
    this->jumping(0, f);
    emit(tmp->toString()+" = true");
    emit(std::string("goto L")+std::to_string(a));
    emitlabel(f);
    emit(tmp->toString() + " = false");
    emitlabel(a);
    return tmp;
}

std::string Logical::toString() {
    return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}

void Or::jumping(int t, int f) {
    int label = t != 0 ? t : newlabel();
    expr1->jumping(label, 0);
    expr2->jumping(t, f);
    if (t == 0) emitlabel(label);
}
void And::jumping(int t, int f) {
    int label = f != 0 ? f : newlabel();
    expr1->jumping(0,label);
    expr2->jumping(t, f);
    if (f == 0) emitlabel(label);
}
void Not::jumping(int t, int f) {
    expr2->jumping(f, t);
}
std::string Not::toString() {
    return op->toString() + " " + expr2->toString();
}
