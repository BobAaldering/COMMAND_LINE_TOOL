#include <help_decorator.h>

// This is the constructor. It has constant pointers to various collections.
decorator::help_decorator::help_decorator(char short_flag, std::string help_flag, std::ostream &out_stream, const collections::i_option_collection *options_collection, const collections::i_positional_collection* positional_collection, std::unique_ptr<parser::i_option_parser> inner_value) :
    parser_decorator(std::move(inner_value)),
    m_help_short_flag{short_flag},
    m_help_long_flag{std::move(help_flag)},
    m_out_stream{out_stream},
    m_options{options_collection},
    m_positionals{positional_collection}
{}

// This is the 'parse' method. It will parse the arguments given to the program.
std::unique_ptr<collections::i_parsed_collection> decorator::help_decorator::parse(const collections::i_arguments_collection &arguments_collection) {
    // Go through all of your arguments.
    for (const auto& argument : arguments_collection.get_arguments()) {
        // Check if a specific argument is your specified 'help' flag.
        if (((argument.length() == 2 && argument[0] == '-' && argument[1] != '-') || (argument.length() >= 4 && argument[0] == '-' && argument[1] == '-')) &&
                (m_help_long_flag == argument.substr(2) || m_help_short_flag == argument[1])) {

            m_out_stream << program_invocation_name << " [FLAGS] "; // Print a message. The variable 'program_invocation_name' contains the name of the program.
            print_help_positional(); // Print the positional arguments.
            print_help_flags(); // Print your flags.

            break; // Help was shown, no need to show it a user twice.
        }
    }

    return parser_decorator::parse(arguments_collection); // Parse the arguments. Return the result.
}

// Private method to print the 'help' diagnostics of the positional argument.
void decorator::help_decorator::print_help_positional() const {
    // Check if you have positional arguments.
    if (m_positionals->begin() != m_positionals->end()) {
        // Go through the positional arguments, and print the info of their position.
        for (const auto &positional: *m_positionals)
            m_out_stream << '<' << positional->recognize_position() << "> ";

        m_out_stream << "\n\n";

        // Go through the positional arguments, and print their help description.
        for (const auto &positional: *m_positionals)
            m_out_stream << positional->help_description() << std::endl;
    }
}

// Private method to print the 'help' diagnostics of your flags.
void decorator::help_decorator::print_help_flags() const {
    m_out_stream << "\nFlags:" << std::endl;
    // Go through all your options, and print their help description.
    for (const auto& option : *m_options)
        m_out_stream << option->help_description();
}