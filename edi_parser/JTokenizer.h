//
// Created by eric on 15/04/2021.
//

#ifndef MTPARSER_TOKENIZER_H
#define MTPARSER_TOKENIZER_H
#include <string>
#include <vector>
namespace MTparser {
    using namespace std;
    enum TokenType {
        WHITESPACE,
        LETTER,
        LEGAL_CHAR,
        UNSIGNED_INT,
        UNSIGNED_REAL,
        SIGN,
        INT,
        REAL,
        POTENTIAL_REAL,
        EXP,
        STRING,
        Q_STRING,
        NUMBER,
        DATE,
        LAT_LONG,
        POT_LAT_LONG,
        COMMENT,
        SPECIAL,
        KEYWORD,
        OPERATOR,
        POT_DATA_GUARDIAN,
        DATA_GUARDIAN
    };

    static const char *sTokenTypeStrings[] = {
            "WHITESPACE",
            "LETTER",
            "LEGAL_CHAR",
            "UNSIGNED_INT",
            "UNSIGNED_REAL",
            "SIGN",
            "INT",
            "REAL",
            "POTENTIAL_REAL",
            "EXP",
            "STRING",
            "Q_STRING",
            "NUMBER",
            "DATE",
            "LAT_LONG",
            "POT_LAT_LONG",
            "COMMENT",
            "SPECIAL",
            "KEYWORD",
            "OPERATOR",
            "POT_DATA_GUARDIAN",
            "DATA_GUARDIAN"
    };

    class Token {
    public:
        enum TokenType type{WHITESPACE};
        string text;
        size_t lineNumber{0};

        void debugPrint() const;
    };

    class Tokenizer {
    public:
        vector<Token> parse(const string &inString);

    private:
        void endToken(Token &t, vector<Token> &ts);
    };
}

#endif //MTPARSER_TOKENIZER_H
