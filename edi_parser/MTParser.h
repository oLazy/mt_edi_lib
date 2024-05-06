//one line to give the program's name and an idea of what it does.
//Copyright (C) 2024,  Eric Mandolesi

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.#ifndef MT_EDI_LIB_MTPARSER_H
#ifndef MT_EDI_LIB_MTPARSER_H
#define MT_EDI_LIB_MTPARSER_H

#include <string>
#include <boost/filesystem.hpp>
class MTParser {
public:
    /**
     * @brief Constructor for MTParser.
     * @param path The boost::filesystem::path to the MT data file (in either edi or j format) to parse.
     */
    explicit MTParser(boost::filesystem::path );

    /**
     * @brief check the file extension for the input file, ".j" for j-format, ".edi" for edi-format
     * @return std::string containing the file extension
     */
    std::string getInputFileExtension();
    virtual void parse(std::string const&) = 0;
    virtual void printInfoBlock() = 0;
protected:
    const boost::filesystem::path inputPath;
    const std::string fileContent;
};


#endif //MT_EDI_LIB_MTPARSER_H
