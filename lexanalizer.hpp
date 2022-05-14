#ifndef LEXANALIZER_HPP
#define LEXANALIZER_HPP

#include <string>
#include <map>
#include <fstream>
#include "lexem.hpp"

using namespace std;

class LexemAnalyser{
#pragma region ENUM
    private:
        typedef enum _state{
            S0,
            S1,
            S2,
            S3,
            S4,
            S5,
            S6,
            S7,
            S8,
            S9,
            S10,
            S11,
            S12,
            S13,
            S14,
            S15,
            S16,
            S17,
            S18,
            S19,
            S20,
            S21,
            S22,
            S23,
            S_SPACE,
            S_END_OF_LINE
        } State;

        typedef enum _token{
            END_OF_LINE = '\n',
            SPACE = ' ',
            PLUS = '+',
            MINUS = '-',
            DIV = '/',
            MUL = '*',
            LOWER = '<',
            GREATER = '>',
            EQUAL = '=',
            DOT = '.',
            COMMA = ',',
            DOUBLE_DOT = ':',
            DOT_COMMA = ';',
            LEFT_C_BRACKET = '(',
            RIGHT_C_BRACKET = ')',
            LEFT_S_BRACKET = '[',
            RIGHT_S_BRACKET = ']',
            WORD = 1000,
            NUMBER = 1001,
        } Token;
#pragma endregion
    private:
        State _prevState;
        State _currState;
        char _currChar;
        string _sLexemValue;
        map<string, Lexem>* _keyWords;
        map<State, map<Token, State>>* _translationTable;
        map<State, Lexem>* _resultLexem;

        fstream _file;
        

    private:
        void initKeywords();
        void insertPair(State state, Token token, State result);
        void initTransTable();
        void initResLexem();
        bool isKeyword(string id);
        void returnToken(char c);
        void popToken();
        Token topToken();
    
    public:
        LexemAnalyser(string fileName);
        ~LexemAnalyser();
        Lexem next();
        string value();
};

#endif