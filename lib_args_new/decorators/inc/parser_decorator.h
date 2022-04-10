#ifndef COMMAND_LINE_TOOL_PARSER_DECORATOR_H
#define COMMAND_LINE_TOOL_PARSER_DECORATOR_H

#include <i_option_parser.h> // Add the 'i_option_parser' header.

namespace decorator {
    // This is the class 'parser_decorator'. It inherits from an 'i_option_parser'.
    // This decorator adds an extra functionality to an 'option_parser', ie the actual class that will parse all arguments.
    class parser_decorator : public parser::i_option_parser {
    public:
        explicit parser_decorator(std::unique_ptr<parser::i_option_parser> inner_value); // This is the constructor. It will have ownership about the 'inner value', what a option parser is.

        [[nodiscard]] std::unique_ptr<collections::i_parsed_collection> parse(const collections::i_arguments_collection& arguments_collection) override; // The 'parser' method. It will parse all the arguments.

    private:
        std::unique_ptr<parser::i_option_parser> m_inner_value; // The 'inner value' of this decorator. It is an 'i_option_parser'.
    };
}

#endif