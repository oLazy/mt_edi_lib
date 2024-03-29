//
// Created by eric on 15/04/2021.
//

#include "Tokenizer.h"
#include <iostream>

namespace MTparser{
    using namespace std;
    vector<Token> Tokenizer::parse(const string &inString) {
        vector<Token> tokens;
        Token currentToken;
        currentToken.lineNumber=1;

        for (char currCh : inString){
            switch (currCh) {
                case  '>':
                    if(currentToken.type == WHITESPACE){
                        currentToken.type = SPECIAL;
                        currentToken.text.append(1,currCh);
                    } else {
                        currentToken.text.append(1,currCh);
                    }
                    break;
                case '!':
                    if(currentToken.type == SPECIAL){
                        currentToken.type = COMMENT;
                        currentToken.text.append(1,currCh);
                    } else {
                        currentToken.text.append(1,currCh);
                    }
                    break;
                case '0' ... '9':
                    if (currentToken.type == WHITESPACE){
                        currentToken.type = UNSIGNED_INT;
                        currentToken.text.append(1,currCh);
                    } else if(currentToken.type == SIGN) {
                        currentToken.type = INT;
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == POTENTIAL_REAL) {
                            currentToken.type = REAL;
                            currentToken.text.append(1,currCh);
                    } else if (currentToken.type == DATE){
                        currentToken.text.append(1,currCh);
                    } else {
                        currentToken.text.append(1, currCh);
                    }
                    break;
                case '"':
                    if (currentToken.type == WHITESPACE) {
                        currentToken.type = Q_STRING;
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == Q_STRING){
                        currentToken.text.append(1,currCh);
                        endToken(currentToken, tokens);
                    }
                    break;
                case '.':
                    if (currentToken.type == WHITESPACE){
                        currentToken.type = POTENTIAL_REAL;
                        currentToken.text.append(1,currCh);
                    }else if (currentToken.type == INT || currentToken.type == UNSIGNED_INT){
                        currentToken.type = REAL;
                        currentToken.text.append(1, currCh);
                    } else if(currentToken.type == STRING || currentToken.type == Q_STRING){
                        currentToken.text.append(1,currCh);
                    } else if(currentToken.type == KEYWORD) {
                        currentToken.text.append(1, currCh);
                    }
//                    } else {
//                        endToken(currentToken,tokens);
//                    }
                    break;
                case '=':
                    if(currentToken.type == SPECIAL){
                        currentToken.type = KEYWORD;
                        currentToken.text.append(1, currCh);
                    } else {
                        endToken(currentToken,tokens);
                        currentToken.type = OPERATOR;
                        currentToken.text.append(1, currCh);
                        endToken(currentToken,tokens);
                    }
                    break;
                case ':':
                    if(currentToken.type == INT){
                        currentToken.type = POT_LAT_LONG;
                        currentToken.text.append(1, currCh);
                    } else if (currentToken.type == POT_LAT_LONG) {
                        currentToken.type = LAT_LONG;
                        currentToken.text.append(1, currCh);
                    } else {
                        currentToken.text.append(1, currCh);
                    }
                    break;
                case 'a' ... 'd':
                case 'A' ... 'D':
                case 'f' ... 'z':
                case 'F' ... 'Z':
                    if(currentToken.type == WHITESPACE){
                        currentToken.type = STRING;
                    } else if(currentToken.type == SPECIAL){
                        currentToken.type = KEYWORD;
                    }
                    currentToken.text.append(1,currCh);
                    break;
                case 'E':
                case 'e':
                    if (currentToken.type == STRING || currentToken.type == WHITESPACE){
                        currentToken.type = STRING;
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == REAL){
                        currentToken.type = EXP;
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == SPECIAL || currentToken.type == KEYWORD) {
                        currentToken.text.append(1,currCh);
                    } else{
                        currentToken.text.append(1,currCh);
                    }
                    break;
                case '+':
                case '-':
                    if(currentToken.type==WHITESPACE){
                        currentToken.type = SIGN;
                        currentToken.text.append(1,currCh);
                    } else {
                        currentToken.text.append(1, currCh);
                    }
                    break;

                case '/':
                    if (currentToken.type==INT || currentToken.type == DATE || currentToken.type==UNSIGNED_INT){
                        currentToken.type = DATE;
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == WHITESPACE){
                        currentToken.type = POT_DATA_GUARDIAN;
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == POT_DATA_GUARDIAN){
                        currentToken.type = DATA_GUARDIAN;
                        currentToken.text.append(1,currCh);
                        endToken(currentToken,tokens);
                    } else {
                        currentToken.text.append(1,currCh);
                    }
                    break;
                case ' ':
                case '\t':
                    if (currentToken.type == COMMENT){
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == Q_STRING){
                        currentToken.text.append(1,currCh);
                    } else if (currentToken.type == SIGN){
                        currentToken.type = STRING;
                        endToken(currentToken,tokens);
                    } else {
                        endToken(currentToken,tokens);
                    }
                    break;
                case '\r':
                case '\n':
                    endToken(currentToken, tokens);
                    ++currentToken.lineNumber;
                    break;
                default:
                    if(currentToken.type == WHITESPACE || currentToken.type == INT || currentToken.type == REAL){
                        endToken(currentToken,tokens);
                    } else if (currentToken.type == SIGN){
                        currentToken.type = STRING;
                        endToken(currentToken,tokens);
                    }
                    break;
            }
        }
        endToken(currentToken, tokens);
        return tokens;
    }

    void Tokenizer::endToken(Token &t, vector<Token> &ts) {
        if(t.type == COMMENT){
            cout << "Ignoring comment: " << t.text << endl;
        } else if(t.type != WHITESPACE){
            ts.push_back(t);
        }
        t.type = WHITESPACE;
        t.text.erase();
    }

    void Token::debugPrint() const {

    }
}
