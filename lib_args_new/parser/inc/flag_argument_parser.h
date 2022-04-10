#ifndef COMMAND_LINE_TOOL_FLAG_ARGUMENT_PARSER_H
#define COMMAND_LINE_TOOL_FLAG_ARGUMENT_PARSER_H

#include <argument_parser.h> // Add the 'argument_parser' header.
#include <flag_argument.h> // Add the 'flag_argument' header.

namespace parser_arguments {
    // This is the 'flag_argument_parser'. It inherits from 'argument_parser'.
    // This class is used to parse an argument to its respective flag (boolean) value.
    // Initially, a parser component was associated with a specific option, for example a 'flag_option'. But to better separate the responsibilities, a separate class has been created for this.

    class flag_argument_parser : public argument_parser {
    public:
        [[nodiscard]] std::unique_ptr<arguments::argument_base> parse(const std::string& flag_identification, const std::string& argument_value) const override; // The parse method for your flag argument.
    };
}

#endif