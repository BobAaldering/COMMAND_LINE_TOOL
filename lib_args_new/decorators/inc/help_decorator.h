#ifndef COMMAND_LINE_TOOL_HELP_DECORATOR_H
#define COMMAND_LINE_TOOL_HELP_DECORATOR_H

#include <ostream> // Add the 'ostream' header.

#include <i_option_collection.h> // Add the 'i_option_collection' header.
#include <i_positional_collection.h> // Add the 'i_positional_collection' header.
#include <parser_decorator.h> // Add the 'parser_decorator' header.

namespace decorator {
    // This is the class 'help_decorator'. It inherits form a 'parser_decorator'.
    // This class adds an extra functionality to a parser, namely showing a help. It has been decided that you also have access to configurable help within the program.
    class help_decorator : public parser_decorator {
    public:
        help_decorator(char short_flag, std::string help_flag, std::ostream& out_stream, const collections::i_option_collection* options_collection, const collections::i_positional_collection* positional_collection, std::unique_ptr<parser::i_option_parser> inner_value); // This is the constructor. It has constant pointers to various collections.

        [[nodiscard]] std::unique_ptr<collections::i_parsed_collection> parse(const collections::i_arguments_collection& arguments_collection) override; // This is the 'parse' method. It will parse the arguments given to the program.

    private:
        void print_help_positional() const; // Private method to print the 'help' diagnostics of the positional argument.
        void print_help_flags() const; // Private method to print the 'help' diagnostics of your flags.

        char m_help_short_flag; // The short flag of your 'help'.
        std::string m_help_long_flag; // The lang flag of your 'help'.
        std::ostream& m_out_stream; // The output streams. It will show to output of your help to, for example, the standard output.

        const collections::i_option_collection* m_options; // A constant, non-owning, pointer to a collection of options.
        const collections::i_positional_collection* m_positionals; // A constant, non-owning, pointer to a collection of positional 'options'.
    };
}

#endif