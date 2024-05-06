find_package(Boost REQUIRED serialization iostreams system filesystem timer program_options)
if (Boost_FOUND)
    message("BOOST FOUND")
    message("VERSION: ${Boost_VERSION}")
endif()

add_library(EMP
        MTParser.cpp MTParser.h # class definition
        Tokenizer.h Tokenizer.cpp Parser.h Parser.cpp # EDI components
        JTokenizer.h JTokenizer.cpp JParser.h JParser.cpp # J components)
        )

target_include_directories(EMP PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(EMP PUBLIC
        Boost_iostreams
        Boost_system
        Boost_serialization
        Boost_filesystem
        Boost_timer
        Boost_chrono
        Boost_program_options)
#add_library(myMtParser Tokenizer.h Tokenizer.cpp Parser.h Parser.cpp)
#add_library(myMtJParser JTokenizer.h JTokenizer.cpp JParser.h JParser.cpp MTParser.cpp MTParser.h)