#include "lexanalizer.hpp"

void LexemAnalyser::initKeywords(){
    _keyWords->insert(make_pair("program", PROGRAM));
    _keyWords->insert(make_pair("type", TYPE));
    _keyWords->insert(make_pair("record", RECORD));
    _keyWords->insert(make_pair("var", VAR));
    _keyWords->insert(make_pair("function", FUNCTION));
    _keyWords->insert(make_pair("begin", BEGIN));
    _keyWords->insert(make_pair("end", END));
    _keyWords->insert(make_pair("of", OF));
    _keyWords->insert(make_pair("if", IF));
    _keyWords->insert(make_pair("else", ELSE));
    _keyWords->insert(make_pair("for", FOR));
    _keyWords->insert(make_pair("do", DO));
    _keyWords->insert(make_pair("then", THEN));
    _keyWords->insert(make_pair("to", TO));
    _keyWords->insert(make_pair("downto", DOWNTO));
    _keyWords->insert(make_pair("read", READ));
    _keyWords->insert(make_pair("readln", READLN));
    _keyWords->insert(make_pair("write", WRITE));
    _keyWords->insert(make_pair("writeln", WRITELN));
    _keyWords->insert(make_pair("and", AND));
    _keyWords->insert(make_pair("or", OR));
    _keyWords->insert(make_pair("not", NOT));
    _keyWords->insert(make_pair("xor", XOR));
    _keyWords->insert(make_pair("div", A_INT_DIV));
    _keyWords->insert(make_pair("mod", A_MOD));
    _keyWords->insert(make_pair("integer", BASETYPE));
    _keyWords->insert(make_pair("real", BASETYPE));
    _keyWords->insert(make_pair("boolean", BASETYPE));
}

void LexemAnalyser::insertPair(State state, Token token, State result){
    _translationTable->at(state).insert(make_pair(token, result));
}

void LexemAnalyser::initTransTable(){
    for(State s = S0; s <= S_END_OF_LINE; s = (State)(s + 1)){
        _translationTable->insert(make_pair(s, map<Token, State>()));
    }

    //S0

    insertPair(S0, WORD, S1);
    insertPair(S0, NUMBER, S2);
    insertPair(S0, PLUS, S5);
    insertPair(S0, MINUS, S6);
    insertPair(S0, MUL, S7);
    insertPair(S0, DIV, S8);
    insertPair(S0, EQUAL, S9);
    insertPair(S0, LOWER, S10);
    insertPair(S0, GREATER, S13);
    insertPair(S0, DOUBLE_DOT, S15);
    insertPair(S0, LEFT_C_BRACKET, S17);
    insertPair(S0, RIGHT_C_BRACKET, S18);
    insertPair(S0, LEFT_S_BRACKET, S19);
    insertPair(S0, RIGHT_S_BRACKET, S20);
    insertPair(S0, DOT_COMMA, S21);
    insertPair(S0, DOT, S22);
    insertPair(S0, COMMA, S23);
    insertPair(S0, SPACE, S_SPACE);
    insertPair(S0, END_OF_LINE, S_END_OF_LINE);

    //S1

    insertPair(S1, NUMBER, S1);
    insertPair(S1, WORD, S1);

    //S2

    insertPair(S2, NUMBER, S2);
    insertPair(S2, DOT, S3);

    //S3

    insertPair(S3, NUMBER, S4);

    //S4

    insertPair(S4, NUMBER, S4);

    //S10

    insertPair(S10, GREATER, S11);
    insertPair(S10, EQUAL, S12);

    //S13

    insertPair(S13, EQUAL, S14);

    //S15

    insertPair(S15, EQUAL, S16);
}

void LexemAnalyser::initResLexem(){
    _resultLexem->insert(make_pair(S1, ID));
    _resultLexem->insert(make_pair(S2, Lexem::NUMBER));
    _resultLexem->insert(make_pair(S4, Lexem::NUMBER));
    _resultLexem->insert(make_pair(S5, A_PLUS));
    _resultLexem->insert(make_pair(S6, A_MINUS));
    _resultLexem->insert(make_pair(S7, A_MUL));
    _resultLexem->insert(make_pair(S8, A_DIV));
    _resultLexem->insert(make_pair(S9, L_EQUAL));
    _resultLexem->insert(make_pair(S10, L_LOWER));
    _resultLexem->insert(make_pair(S11, L_NOT_EQUAL));
    _resultLexem->insert(make_pair(S12, L_LOWER_N_EQUAL));
    _resultLexem->insert(make_pair(S13, L_GREATER));
    _resultLexem->insert(make_pair(S14, L_GREATER_N_EQUAL));
    _resultLexem->insert(make_pair(S15, Lexem::DOUBLE_DOT));
    _resultLexem->insert(make_pair(S16, ASSIGN));
    _resultLexem->insert(make_pair(S17, Lexem::LEFT_C_BRACKET));
    _resultLexem->insert(make_pair(S18, Lexem::RIGTH_C_BRACKET));
    _resultLexem->insert(make_pair(S19, Lexem::LEFT_S_BRACKET));
    _resultLexem->insert(make_pair(S20, Lexem::RIGHT_S_BRACKET));
    _resultLexem->insert(make_pair(S21, Lexem::DOT_N_COMMA));
    _resultLexem->insert(make_pair(S22, Lexem::DOT));
    _resultLexem->insert(make_pair(S23, Lexem::COMMA));
    _resultLexem->insert(make_pair(S_SPACE, Lexem::SPACE));
    _resultLexem->insert(make_pair(S_END_OF_LINE, Lexem::END_OF_LINE));
}

bool LexemAnalyser::isKeyword(string id){
    return _keyWords->find(id) != _keyWords->end();
}

void LexemAnalyser::returnToken(char c){
    _file << c;
}

void LexemAnalyser::popToken(){
    _file.get();
}

LexemAnalyser::Token LexemAnalyser::topToken(){
    char c;
    c = _file.peek();
    _currChar = c;
    if(c >= '0' && c <= '9')
        return NUMBER;
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return WORD;
    return (Token)c;
}

LexemAnalyser::LexemAnalyser(string fileName){
    _currState = S0;
    _prevState = S0;
    _currChar = '\0';
    _sLexemValue = "";
    _keyWords = new map<string, Lexem>();
    _translationTable = new map<State, map<Token, State>>();
    _resultLexem = new map<State, Lexem>();

    _file.open(fileName, ios::in | ios::out);

    initKeywords();
    initTransTable();
    initResLexem();
}

LexemAnalyser::~LexemAnalyser(){

}

Lexem LexemAnalyser::next(){

    Token token;
    _sLexemValue = "";

    while(!_file.eof()){
        token = topToken();

        map<State, map<Token, State>>::iterator eit;
        map<Token, State>::iterator iit;

        if((eit = _translationTable->find(_currState)) != _translationTable->end()){
            _prevState = _currState;
            if((iit = _translationTable->at(_currState).find(token)) != _translationTable->at(_currState).end()){
                _currState = iit->second;
            }else{
                _currState = S0;
            }
        }else{
            return ERROR;
        }

        if(_currState == S0 && _currState != _prevState){
            Lexem result = _resultLexem->at(_prevState);
            if(result == ID){
                if(_keyWords->find(_sLexemValue) != _keyWords->end()){
                    result = _keyWords->at(_sLexemValue);
                }
            }
            return result;
        }else{
            _sLexemValue += _currChar;
        }

    popToken();
    }

    return Lexem::END_OF_FILE;
}

string LexemAnalyser::value(){
    return _sLexemValue;
}