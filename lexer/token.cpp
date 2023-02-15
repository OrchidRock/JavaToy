#include "token.h"
#include <string>

Token::Token(int t) : tag(t) {}
Token::Token(Token* other) : tag(other->tag) {}
std::string Token::toString() {
    return std::to_string((char)tag);
}

Num::Num(int v) : Token(Tag::NUM), value(v) {}
std::string Num::toString() {
    return std::to_string(value);
}

Word* Word::And = new Word(" ",1);
Word* Word::Or  = new Word("||", Tag::OR);
Word* Word::eq  = new Word("==", Tag::EQ);
Word* Word::ne  = new Word("!=", Tag::NE);
Word* Word::le  = new Word("<=", Tag::LE);
Word* Word::ge  = new Word(">=", Tag::GE);
Word* Word::minus = new Word("minus", Tag::MINUS);
Word* Word::True = new Word("true", Tag::TRUE);
Word* Word::False = new Word("false", Tag::FALSE);
Word* Word::temp = new Word("t", Tag::TEMP);

Word::Word(std::string s, int tag) : Token(tag), lexeme(s) {
}
Word::Word(Word* other) : Token(other->tag), lexeme(other->lexeme) {}
std::string Word::toString() {
    return lexeme;
}


Real::Real(float v) : Token(Tag::REAL), value(v) {}
std::string Real::toString() {
    return std::to_string(value);
}


