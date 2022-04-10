#include <option.h>

// The constructor. It also has a unique, owning, pointer to a specific 'argument_parser'.
options::option::option(char short_flag, const std::string_view &long_flag, const std::string_view &description, int arguments_count, std::unique_ptr<parser_arguments::argument_parser> parser) :
    m_short_flag{short_flag},
    m_long_flag{long_flag},
    m_description{description},
    m_number_of_arguments{arguments_count},
    m_parser{std::move(parser)}
{
    // Check if your option accepts more than one argument. There is only support for one argument for one option.
    if (arguments_count > 1)
        throw std::invalid_argument("An error has happened! Count of an option cannot be greater than one!"); // Throw an exception.
}

// Get your short flag.
[[maybe_unused]] char options::option::get_short_flag() const {
    return m_short_flag; // Return the short flag.
}

// Get your long flag.
const std::string &options::option::get_long_flag() const {
    return m_long_flag; // Return the long flag.
}

// Get your description.
[[maybe_unused]] const std::string &options::option::get_description() const {
    return m_description; // Return just the description.
}

// Get the number of arguments.
int options::option::get_number_of_arguments() const {
    return m_number_of_arguments; // Return the number of arguments for your option.
}

// The default help description for an option. Can be overridden for flexibility.
std::string options::option::help_description() const {
    std::stringstream help_string_stream{}; // A string stream, used for creating your complete help description.
    help_string_stream << "-" << m_short_flag << ", --" << m_long_flag << "\t\t" << m_description << std::endl; // The description
    return help_string_stream.str(); // Return the string. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
}

// Check if the specific argument is a flag.
bool options::option::is_flag(const std::string &flag) const {
    // Check if the argument of this method is a flag.
    return !flag.empty() &&
        !((flag.length() == 2 && flag[0] == '-' && flag[1] != '-') ||
            (flag.length() >= 4 && flag[0] == '-' && flag[1] == '-'));
}

// Check if your argument is a long flag, or a short flag. Can be overridden for flexibility.
bool options::option::can_parse(const std::string &argument) const {
    // Check if there is a possibility to parse the argument for this option.
    return (argument.length() == 2 && argument[0] == '-' && argument[1] != '-' && argument[1] == m_short_flag) ||
        (argument.length() >= 4 && argument[0] == '-' && argument[1] == '-' && argument.substr(2) == m_long_flag); // Check if your argument is a short flag, or a long flag.
}

// Pure virtual method special for parsing.
std::unique_ptr<arguments::argument_base> options::option::parse_to_argument(const std::string &argument) {
    return m_parser->parse(m_long_flag, argument); // Parse the argument for an option. You are calling the 'parse' method on the 'm_parser' field.
}