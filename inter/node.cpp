#include "node.h"
#include "../lexer/lexer.h"
#include <string>
#include <iostream>

int Node::labels = 0;

Node::Node() { lexline = Lexer::line; }

void Node::error(std::string s) {
    throw std::string("Error: near line ") + std::to_string(lexline) + ":" + s;
}

int Node::newlabel() { return ++labels; }
void Node::emitlabel(int i) { std::cout << "L" << i << ":" ; }
void Node::emit(std::string s) { std::cout << '\t' << s << '\n'; }
