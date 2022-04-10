#ifndef COMMAND_LINE_TOOL_TEXT_ARGUMENT_PARSER_H
#define COMMAND_LINE_TOOL_TEXT_ARGUMENT_PARSER_H

#include <text_argument.h> // Add the 'text_argument' header.
#include <argument_parser.h> // Add the 'argument_parser' header.

namespace parser_arguments {
    // This is the 'text_argument_parser'. It inherits from 'argument_parser'.
    // This class is used to parse an argument to its respective string value.
    // Initially, a parser component was associated with a specific option, for example a 'text_option'. But to better separate the responsibilities, a separate class has been created for this.
    class text_argument_parser : public argument_parser {
    public:
        [[nodiscard]] std::unique_ptr<arguments::argument_base> parse(const std::string& flag_identification, const std::string& argument_value) const override; // The parse method for your textual argument.
    };
}

#endif