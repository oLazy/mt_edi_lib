//
// Created by eric on 16/04/2021.
//

#ifndef MTPARSER_PARSER_H
#define MTPARSER_PARSER_H
#include "Tokenizer.h"
#include <map>
#include <tuple>

namespace MTparser {
    using namespace std;
    typedef vector<string> Data_set;
    typedef map<string ,string > Option_list;
    typedef map<string,tuple<Option_list , Data_set>> Data_block;

    /**
     * @param dataset [in]: the Data_set (std::vector<std::string>) to convert into a std::vector<double>
     * @param skip [in, optional]: if a datum matches this value, it is converted into a nan
     * @return std::vector<double> containing the data values.
     */
    vector<double> dataset2double(Data_set const& , string const skip = "");

    class Parser {
    public:
        void parse(string const&);
        /**
         *
         * @param key [in] the keyword related to the data block of interest.
         * @return the option list related to the data block key.
         *
         * Usage:
         * @code
         * auto ol = my_parser.get_option_list_for(">HEAD");
         * @endcode
         */
        Option_list get_option_list_for(string const& key) const;
        Data_set get_data_set_for(string const& key) const;
        Data_block get() const;
    private:
        void parse(vector<Token> &);
        Tokenizer tokenizer;
        void data_block(vector<Token>::iterator &it);
        Option_list option_list(vector<Token>::iterator &it);
        Data_set data_set(vector<Token>::iterator &it);
        string spare_free_text; // to not waste info section
        Data_block fileContents;
    };
}

#endif //MTPARSER_PARSER_H
