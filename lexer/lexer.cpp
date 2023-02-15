#include "lexer.h"
#include <iostream>
#include <cctype>

#include "../symbols/type.h"

void Lexer::reserve(Word* w) {
    words.insert(lexerHashTable::value_type(w->lexeme, w));
}

int Lexer::line = 1;
Lexer::Lexer() : curr_tok(NULL) {
    reserve(new Word("if", Tag::IF));
    reserve(new Word("else", Tag::ELSE));
    reserve(new Word("while", Tag::WHILE));
    reserve(new Word("do", Tag::DO));
    reserve(new Word("break", Tag::BREAK));
    reserve(Word::True); reserve(Word::False);
    reserve(Type::Int); reserve(Type::Char);
    reserve(Type::Bool); reserve(Type::Float);
}

Lexer::~Lexer() {
    //delete Word::True; delete Word::False;
    delete Word::minus; 
    delete Word::eq; delete Word::ge;
    delete Word::le; delete Word::ne;
    delete Word::And; delete Word::Or; 
    delete Word::temp;
    
    for(auto iter = words.begin(); iter != words.end(); iter++) {
        if(iter->second) delete iter->second;
        iter->second = NULL;
    } 
}

void Lexer::readch() { peek = std::cin.get(); }
bool Lexer::readch(char c) {
    readch();
    if (peek != c) return false;
    peek = ' ';
    return true;
}

Token* Lexer::scan() {
    if(curr_tok) delete curr_tok;
    curr_tok = NULL;

    for (;; readch()) {
        if (peek == ' ' || peek == '\t') continue;
        else if (peek == '\n') line += 1;
        else break;
    }
    
    switch(peek) {
        case '&':
            if (readch('&')) return Word::And; else return curr_tok = new Token('&');
        case '|': 
            if (readch('|')) return Word::Or; else return curr_tok = new Token('|');
        case '=':
            if (readch('=')) return Word::eq; else return curr_tok = new Token('=');
        case '!':
            if (readch('=')) return Word::ne; else return curr_tok = new Token('!');
        case '<':
            if (readch('=')) return Word::le; else return curr_tok = new Token('<');
        case '>':
            if (readch('=')) return Word::ge; else return curr_tok = new Token('>');
        default:
            break;
    }
    
    if(isdigit(peek)) {
        int v = 0;
        do {
            v = 10 * v + (peek - '0');
            readch();    
        } while (isdigit(peek));
        
        if( peek != '.') return curr_tok = new Num(v);
        float x = v;
        float d = 10;
        for(;;) {
            readch();
            if(! isdigit(peek)) break;
            x = x + (peek - '0') / d; d = d * 10;
        }

        return curr_tok = new Real(x); 
    }
    
    if(isalpha(peek)) {
        std::string b;
        do {
            b.push_back(peek);
            readch();
        } while (isalnum(peek));
        
        Word* w =(Word*) words[b];
        if(w != NULL) return w;

        w = new Word(b, Tag::ID);
        words.insert(lexerHashTable::value_type(b, w));

        return w;
    }

    curr_tok = new Token(peek);
    peek = ' ';
    return curr_tok;
}
