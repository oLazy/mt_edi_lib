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

#include "MTParser.h"

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.#include "MTParser.h"

#include <boost/system/error_code.hpp>
#include <strstream>
#include <utility>

namespace {

    /**
     * @brief Utility function ot read in file contents
     * @param f input sile stream
     * @return file contents
     */
    std::string getContentsFromFile(std::ifstream &f) {
        std::ostrstream sstr;
        sstr << f.rdbuf();
        return sstr.str();
    }

    /**
     * @brief Check the path is valid, open the file and read the file contents for file at path.
     * @param path boost::filesystem::path path to input file
     * @return std::string of file contents.
     */
    std::string getContentsFromFilePath(boost::filesystem::path const& path){
        if(!boost::filesystem::is_regular_file(path)){
            throw boost::filesystem::filesystem_error("Path provided in not a regular file", path,
                                                      boost::system::errc::make_error_code(
                                                              boost::system::errc::no_such_file_or_directory
                                                      ));
        }
        boost::filesystem::ifstream f(path);
        if (!f.is_open()){
            throw std::runtime_error("Error: unable to open file: " + path.string() + "\n");
        }
         std::string fc{::getContentsFromFile(f)};
        return fc;
    }
}
MTParser::MTParser(boost::filesystem::path  path):
inputPath(std::move(path)),
fileContent(::getContentsFromFilePath(path)){}

std::string MTParser::getInputFileExtension() {
    return boost::filesystem::extension(this->inputPath);
}
