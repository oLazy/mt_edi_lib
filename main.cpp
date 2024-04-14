//driver for my EDI MT libs
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
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <iostream>
#include "edi_parser/Parser.h"
#include "edi_parser/JParser.h"
#include <boost/filesystem.hpp>

enum class FileType{EDI, J, OTHER};

int main(int argc, char* argv[]){
    if (argc < 2) throw std::runtime_error("at least one .edi file must be provided.");
    std::string filename(argv[1]);
    std::string ext{boost::filesystem::extension(filename)};
    FileType ft;
    if(ext == ".edi") {ft = FileType::EDI;}
    else if(ext == ".j") {ft = FileType::J;}
    else {ft = FileType::OTHER;}
    switch (ft) {
        case FileType::EDI: {

        }

    }
};
