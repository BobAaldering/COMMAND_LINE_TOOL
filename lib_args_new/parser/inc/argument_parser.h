#ifndef COMMAND_LINE_TOOL_ARGUMENT_PARSER_H
#define COMMAND_LINE_TOOL_ARGUMENT_PARSER_H

#include <memory> // Add the 'memory' header.

#include <argument_base.h> // Add the 'argument_base' header.

namespace parser_arguments {
    // This is the class 'argument_parser'. Used as a complete abstract class for parsing arguments.
    class argument_parser {
    public:
        [[nodiscard]] virtual std::unique_ptr<arguments::argument_base> parse(const std::string& flag_identification, const std::string& argument_value) const = 0; // The abstract parse method for parsing specific types of arguments.
        virtual ~argument_parser() = default; // Virtual destructor.
    };
}

#endif