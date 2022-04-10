#ifndef COMMAND_LINE_TOOL_ARGUMENT_DECORATOR_H
#define COMMAND_LINE_TOOL_ARGUMENT_DECORATOR_H

#include <argument_parser.h> // Add the 'argument_parser' header.

namespace decorator {
    // This is the class 'argument_decorator'. It inherits from an 'argument_parser'.
    // This is a decorator used to add extra functionality to a parser associated with a certain type of argument. For example, as extra functionality, range-based checking for certain types of arguments can be considered.
    class argument_decorator : public parser_arguments::argument_parser {
    public:
        explicit argument_decorator(std::unique_ptr<parser_arguments::argument_parser> inner_value); // This is the constructor. It will have ownership about the 'inner value', what an argument parser is.

        [[nodiscard]] std::unique_ptr<arguments::argument_base> parse(const std::string &flag_identification, const std::string &argument_value) const override; // The 'parser' method. It will parse an option with its argument.

    private:
        std::unique_ptr<parser_arguments::argument_parser> m_inner_value; // The 'inner value' of this decorator. It is an 'argument_parser'.
    };
}

#endif