#ifndef COMMAND_LINE_TOOL_PROGRAM_H
#define COMMAND_LINE_TOOL_PROGRAM_H

#include <iostream> // Add the 'iostream' header.

#include <int_argument.h> // Add the 'int_argument' header.
#include <dbl_argument.h> // Add the 'dbl_argument' header.
#include <text_argument.h> // Add the 'text_argument' header.
#include <flag_argument.h> // Add the 'flag_argument' header.
#include <invalid_argument.h> // Add the 'invalid_argument' header.
#include <i_parsed_collection.h> // Add the 'i_parsed_collection' header.

// This is the 'program' class.
class program {
public:
    explicit program(std::unique_ptr<collections::i_parsed_collection> collection_of_arguments); // The constructor, the collection of parsed objects in passed to it.
    void run(); // The 'run' method. It is used to run the program.

private:
    std::unique_ptr<collections::i_parsed_collection> m_collection; // An owning pointer, to a parsed collection.
};

#endif