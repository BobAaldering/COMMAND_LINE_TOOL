#ifndef COMMAND_LINE_TOOL_I_PARSER_BUILDER_H
#define COMMAND_LINE_TOOL_I_PARSER_BUILDER_H

#include <string> // Add the 'string' header.
#include <memory> // Add the 'memory' header.

#include <i_option_parser.h> // Add the 'i_option_parser' header.
#include <i_option_collection.h> // Add the 'i_option_collection' header.

namespace builder {
    // This is the interface 'i_parser_builder'.
    class i_parser_builder {
    public:
        [[maybe_unused]] virtual i_parser_builder& with_help_configuration(std::ostream& help_out_stream) = 0; // Abstract method used for a default 'help' flag.
        [[maybe_unused]] virtual i_parser_builder& with_help_configuration(char help_short_flag, const std::string &help_long_flag, std::ostream& help_out_stream) = 0; // Abstract method used for a customizable 'help' flag.

        [[maybe_unused]] virtual i_parser_builder& with_option(char short_flag, const std::string& long_flag, const std::string& description, bool default_value) = 0; // Abstract method for a flag.

        [[maybe_unused]] virtual i_parser_builder& with_int_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, int default_value) = 0; // Abstract method for an option with an integer argument.
        [[maybe_unused]] virtual i_parser_builder& with_int_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, const std::pair<int, int>& range_values, int default_value) = 0; // Abstract method for an option with an integer argument. It has range-based checking support for arguments.

        [[maybe_unused]] virtual i_parser_builder& with_dbl_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, double default_value) = 0; // Abstract method for an option with a double argument.
        [[maybe_unused]] virtual i_parser_builder& with_dbl_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, const std::pair<int, int>& range_values, double default_value) = 0; // Abstract method for an option with a double argument. It has range-based checking support for arguments.

        [[maybe_unused]] virtual i_parser_builder& with_text_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, const std::string& default_value) = 0; // Abstract method for an option with a text argument.

        [[maybe_unused]] virtual i_parser_builder& with_text_positional(const std::string& positional_identification, const std::string& description, const std::string& default_value) = 0; // Abstract method for a text positional argument.
        [[maybe_unused]] virtual i_parser_builder& with_int_positional(const std::string& positional_identification, const std::string& description, int default_value) = 0; // Abstract method for an integer positional argument.
        [[maybe_unused]] virtual i_parser_builder& with_dbl_positional(const std::string& positional_identification, const std::string& description, double default_value) = 0; // Abstract method for a double positional argument.

        [[maybe_unused]] virtual std::unique_ptr<parser::i_option_parser> make() = 0; // Abstract method to create an option parser.

        virtual ~i_parser_builder() = default;
    };
}

#endif