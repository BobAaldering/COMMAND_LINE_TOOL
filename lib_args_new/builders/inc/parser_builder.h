#ifndef COMMAND_LINE_TOOL_PARSER_BUILDER_H
#define COMMAND_LINE_TOOL_PARSER_BUILDER_H

#include <int_argument_parser.h> // Add the 'int_argument_parser' header.
#include <dbl_argument_parser.h> // Add the 'dbl_argument_parser' header.
#include <text_argument_parser.h> // Add the 'text_argument_parser' header.
#include <flag_argument_parser.h> // Add the 'flag_argument_parser' header.

#include <option_parser.h> // Add the 'option_parser' header.

#include <parsed_collection.h> // Add the 'parsed_collection' header.
#include <option_collection.h> // Add the 'option_collection' header.
#include <positional_collection.h> // Add the 'positional_collection' header.

#include <help_decorator.h> // Add the 'help_decorator' header.

#include <int_argument_decorator.h> // Add the 'int_argument_decorator' header.
#include <dbl_argument_decorator.h> // Add the 'dbl_argument_decorator' header.

#include <i_parser_builder.h> // Add the 'i_parser_builder' header.

namespace builder {
    // This is the class 'parser_builder'. It inherits from 'i_parser_builder'.
    class parser_builder : public i_parser_builder {
    public:
        parser_builder(); // The constructor.

        [[maybe_unused]] i_parser_builder& with_help_configuration(std::ostream& help_out_stream) override; // Method used for a default 'help' flag.
        [[maybe_unused]] i_parser_builder& with_help_configuration(char help_short_flag, const std::string &help_long_flag, std::ostream& help_out_stream) override; // Method used for a customizable 'help' flag.

        [[maybe_unused]] i_parser_builder& with_option(char short_flag, const std::string& long_flag, const std::string& description, bool default_value) override; // Method for a flag.

        [[maybe_unused]] i_parser_builder& with_int_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, int default_value) override; // Method for an option with an integer argument.
        [[maybe_unused]] i_parser_builder& with_int_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, const std::pair<int, int>& range_values, int default_value) override; // Method for an option with an integer argument. It has range-based checking support for arguments.

        [[maybe_unused]] i_parser_builder& with_dbl_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, double default_value) override; // Method for an option with a double argument.
        [[maybe_unused]] i_parser_builder& with_dbl_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, const std::pair<int, int>& range_values, double default_value) override; // Method for an option with a double argument. It has range-based checking support for arguments.

        [[maybe_unused]] i_parser_builder& with_text_option(char short_flag, const std::string& long_flag, const std::string& description, int arguments_count, const std::string& default_value) override; // Method for an option with a text argument.

        [[maybe_unused]] i_parser_builder& with_text_positional(const std::string &positional_identification, const std::string& description, const std::string& default_value) override; // Method for a text positional argument.
        [[maybe_unused]] i_parser_builder & with_int_positional(const std::string &positional_identification, const std::string &description, int default_value) override; // Method for an integer positional argument.
        [[maybe_unused]] i_parser_builder & with_dbl_positional(const std::string &positional_identification, const std::string &description, double default_value) override; // Method for a double positional argument.

        [[maybe_unused]] std::unique_ptr<parser::i_option_parser> make() override; // Method to create an option parser.

    private:
        collections::positional_collection* m_positional_collection; // A raw, non-owning, pointer to a collection of positional arguments.
        collections::option_collection* m_option_collection; // A raw, non-owning, pointer to a collection of options.
        collections::parsed_collection* m_parsed_collection; // A raw, non-owning, pointer to a collection of parsed arguments.

        std::unique_ptr<parser::i_option_parser> m_parser; // An owning pointer to an option parser.

        bool m_is_decorated; // Boolean to indicate if you have already specified a decorator for your help flag.
    };

    parser_builder default_builder(); // Free function, just used for a fancy experience when creating a builder.
}

#endif