#ifndef COMMAND_LINE_TOOL_I_OPTION_PARSER_H
#define COMMAND_LINE_TOOL_I_OPTION_PARSER_H

#include <i_parsed_collection.h> // Add the 'i_parsed_collection' header.
#include <i_arguments_collection.h> // Add the 'i_arguments_collection' header.

namespace parser {
    // This is the abstract class 'i_option_collection'. It has only abstract methods, so you can see this also as an interface.
    class i_option_parser {
    public:
        [[nodiscard]] virtual std::unique_ptr<collections::i_parsed_collection> parse(const collections::i_arguments_collection& arguments_collection) = 0; // This is the abstract 'parse' method. It is used to parse all the argument given to the main function into specific options, and eventually positional arguments.
        virtual ~i_option_parser() = default; // Virtual destructor.
    };
}

#endif