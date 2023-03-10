#include "type.h"
#include <string>

Type* Type::Int = new Type("int", Tag::BASIC, 4);
Type* Type::Float = new Type("float", Tag::BASIC, 8);
Type* Type::Char = new Type("char", Tag::BASIC, 1);
Type* Type::Bool = new Type("bool", Tag::BASIC, 1);

Type::Type(std::string s, int tag, int w) : Word(s, tag), width(w) {
}
Type::Type(Type* other) : Word(other->lexeme, other->tag), width(other->width) {}

Type* Type::max(Type* p1, Type* p2) {
    if (! numeric(p1) || ! numeric(p2)) return NULL;
    else if (p1 == Type::Float || p2 == Type::Float) return Type::Float;
    else if (p1 == Type::Int || p2 == Type::Int) return Type::Int;
    else return Type::Char;
}
bool Type::numeric(Type* p) {
    if (p == Type::Char || p == Type::Int ||
                            p == Type::Float)
        return true;
    else return false;
}


Array::Array(int sz, Type* p) : 
                Type("[]", 
                Tag::INDEX, sz*p->width), 
                size(sz), of(p) {
}
Array::~Array() { delete of; }

std::string Array::toString() {
    return std::string("[") + std::to_string(size) + "]" + of->toString();
}
