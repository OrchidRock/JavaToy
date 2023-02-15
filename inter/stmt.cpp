#include "stmt.h"


Stmt* Stmt::Null = new Stmt();
Stmt* Stmt::Enclosing = Stmt::Null;
Stmt::Stmt() {
}
void Stmt::gen(int b, int a) {}


Seq::Seq(Stmt* s1, Stmt* n) : stmt1(s1), next(n) {}
Seq::~Seq() {
    if(stmt1 && stmt1 != Null) delete stmt1;
    if(next && next != Null) delete next;
}

void Seq::gen(int b, int a) {
    if (stmt1 == Null) next->gen(b, a);
    else if (next == Null) stmt1->gen(b, a);
    else{
        int label = newlabel();
        stmt1->gen(b, label);
        emitlabel(label);
        next->gen(label, a);
    }

}

If::If(Expr* x, Stmt* s): expr(x), stmt(s) {
    if(!(expr->type == Type::Bool)) expr->error("boolean required in if");
}
void If::gen(int b, int a){
    int label = newlabel();
    expr->jumping(0, a);
    emitlabel(label);
    stmt->gen(label, a);
}
