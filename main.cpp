#include <iostream>
#include "lexanalizer.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Lexem lexem;
    LexemAnalyser* lex = new LexemAnalyser("test.pas");

    while(lexem != END_OF_FILE){
        lexem = lex->next();
        if(lexem != END_OF_LINE && lexem != SPACE)
        cout << lex->value() << endl;
    }
    return 0;
}