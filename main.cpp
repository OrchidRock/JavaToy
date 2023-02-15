
#include<iostream>

#include "parser/parser.h"
#include "lexer/lexer.h"

class Main {
public: 
    static void main(int argc, char* argv[]) {
        Lexer lex = Lexer();
        Parser parse = Parser(lex);
        parse.program();
        std::cout << '\n';
    }
};


int main(int argc, char* argv[]){
    
    Main::main(argc, argv); 
    return 0;
}
