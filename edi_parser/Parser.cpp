//
// Created by eric on 16/04/2021.
//

#include "Parser.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <cmath>

namespace MTparser {
    void Parser::parse(vector<Token> &t){
        for(auto ti = t.begin(); ti != t.end();ti++){
            data_block(ti);
        }
    }

    void Parser::data_block(vector<Token>::iterator &it) {
        string keyword;
        Option_list ol;
        Data_set ds;
        if(it->type == KEYWORD){
            if(it->text==">END")return;
            keyword = it->text;
            if(next(it)->type==KEYWORD) {
                fileContents[keyword] = make_tuple(ol,ds);
                return;
            }
        }

        while(next(it)->type != KEYWORD) {
            it++;
//            cerr << "data_block(): current token: " << it->text << "\n\n";
            switch (it->type) {
                case DATA_GUARDIAN:
//                    cerr << "data guardian!\n";
                    ds = data_set(it);
                    break;
                case STRING:
                case SIGN:
                    if (next(it)->type == OPERATOR) {
                        ol = option_list(it);
                    } else {
                        while (next(it)->type!=KEYWORD)it++; // skip any free text
                    }
                    break;
                default:
                    throw runtime_error("Data_block does not contain option list, free text or dataset after the keyword.");
            }
        }
        fileContents[keyword] = make_tuple(ol,ds);
    }

    Option_list Parser::option_list(vector<Token>::iterator &it) {
        Option_list res;
        while (it->type==STRING && next(it)->type==OPERATOR && next(it,2)->type != KEYWORD){
            string option_name = it->text;
            it++;
            if(it->type==OPERATOR){
                it++;
                res[option_name]=it->text;
//                cerr << "option name: " << option_name << endl;
//                cerr << "option value: " << it->text << endl;
                it++;
            } else {
                throw runtime_error("Malformed option list, error about line " + to_string(it->lineNumber) + '\n');
            }
        }
        it--;
//        cerr << "current token: " << it->text << "\n\n";
        return res;
    }

    Data_set Parser::data_set(vector<Token>::iterator &it) {
        if (it->type == DATA_GUARDIAN){
//            cerr << "right on time!\n";
            Data_set res;
            it++;
            int to_read = stoi(it->text);
            for(int i=0; i<to_read;i++){
                it++;
                res.push_back(it->text);
            }
//            cerr << "data_set(): current token: " << it->text << sTokenTypeStrings[it->type] << endl;
            return res;
        } else {
            throw logic_error("I should not be in this branch");
        }
    }

    Option_list Parser::get_option_list_for(const string &key) const {
        return std::get<0>(fileContents.at(key));
    }

    Data_set Parser::get_data_set_for(const string &key) const {
        return std::get<1>(fileContents.at(key));
    }



    Data_block Parser::get() const {
        auto res = fileContents;
        return res;
    }

    void Parser::parse(const string &fileContents) {
        vector<Token> tokens = tokenizer.parse(fileContents);
        parse(tokens);
    }


    vector<double> dataset2double(const Data_set &ds, string const skip) {
        vector<double> res;
        for (auto d : ds){
            if (d!=skip){
                res.push_back(stod(d));}
            else {
                res.push_back(nan(""));
            }
        }
        return res;
    }
}