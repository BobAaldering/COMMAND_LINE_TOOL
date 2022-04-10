#ifndef COMMAND_LINE_TOOL_OPTION_PARSER_H
#define COMMAND_LINE_TOOL_OPTION_PARSER_H

#include <invalid_argument.h> // Add the 'invalid_argument' header.

#include <i_positional_collection.h> // Add the 'i_positional_collection' header.
#include <i_option_collection.h> // Add the 'i_option_collection' header.
#include <i_option_parser.h> // Add the 'i_option_parser' header.

namespace parser {
    // This is the class 'option_parser'. It inherits form 'i_option_parser'.
    // Here, all 'raw' arguments are parsed with its corresponding flags.
    class option_parser : public i_option_parser {
    public:
        option_parser(std::unique_ptr<collections::i_option_collection> option_collection, std::unique_ptr<collections::i_positional_collection> positional_collection, std::unique_ptr<collections::i_parsed_collection> parsed_collection); // The constructor of your 'option_parser'.

        [[nodiscard]] std::unique_ptr<collections::i_parsed_collection> parse(const collections::i_arguments_collection& arguments_collection) override; // This is the 'parse' method. It is used to parse all the argument given to the main function into specific options, and eventually positional arguments.

    private:
        void parse_to_arguments(const collections::i_arguments_collection& arguments_collection) const; // Private method, for the inner-loop of the parser.

        std::unique_ptr<collections::i_option_collection> m_options; // Owning pointer to your collection of options.
        std::unique_ptr<collections::i_positional_collection> m_positionals; // Owning to your collection of positional options/arguments.
        std::unique_ptr<collections::i_parsed_collection> m_parsed; // Owning pointer to your collection of parsed arguments.
    };
}

#endif