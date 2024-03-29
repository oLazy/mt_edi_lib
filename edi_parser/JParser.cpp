//
// Created by eric on 16/04/2021.
//

#include "JParser.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
namespace MTparser {
    void Parser::parse(const string &fileContents) {
        vector<Token> tokens = tokenizer.parse(fileContents);
        parse(tokens);
    }

//! This function parses a string of token from a j-file.
//! As j-format is used but never completely defined, this function is currently written to support EM needs.
//! Particularly, here the sole kind of MT data considered is the impedance tensor Z.
//! \param t string of tokens to parse
    void Parser::parse(vector<Token> &t) {
        for (auto ti = t.begin(); ti != t.end(); ti++) {
            if (ti->type == MTparser::KEYWORD) {// I am parsing the info block
                auto keyword = ti->text;
                ti++;
                if (ti->type != MTparser::OPERATOR) throw std::runtime_error("Bad j-file.");
                ti++;
                informationBlock[keyword] = stod(ti->text);
            }else if (ti->type == MTparser::STRING) {
                auto nextType = std::next(ti)->type;
                switch (nextType) {
                    case MTparser::STRING:
                        std::cout << "Station Name:" << ti->text << "\n";
                        break;
                    case MTparser::UNSIGNED_INT:
                        auto datasetName = ti->text;
//                        std::cout << "Dataset:" << datasetName << "\n";
                        bool isAppRho{false};
                        if(ti->text[0]=='R'||ti->text[0]=='r') isAppRho = true;
                        int entries = (isAppRho)? 9: 5;
                        ti++;
                        auto ndata = stoi(ti->text);
                        if(nfreq==0)nfreq=ndata;
//                        std::cout << ti->text +" data present.\n";
                        ti++;
                        for (int i=0; i<ndata;i++){
                            for (int j =0; j<entries;j++){
//                                std::cout << ti->text << "; ";
                                if (datasetName[0]=='z'||datasetName[0]=='Z') {
                                    dataBlock[datasetName][j].push_back(stod(ti->text));
                                }
                                else if (datasetName[0]=='r'||datasetName[0]=='R'){
                                    dataBlock[datasetName][j].push_back(stod(ti->text));
                                }
                                ti++;
                            }
//                            std::cout << "\n";
                        }
                        ti--;
//                        std::cout << "\n";
                        break;
//                    default:
//                        std::string lineno;
//                        std::stringstream sslineno;
//                        sslineno << ti->lineNumber;
//                        sslineno >> lineno;
//                        throw std::runtime_error("Unknown token after string. Error in J-file line "+ lineno);
                }
            }
        }
    }

    void Parser::printInfoBlock() {
        for (auto t:informationBlock){
            std::cout << t.first << "=" << t.second << "\n";
        }
    }

    Data_Table Parser::getDataFor(const string& e) {
        return dataBlock[e];
    }

    unsigned Parser::getNfreq() const {
        return nfreq;
    }

}