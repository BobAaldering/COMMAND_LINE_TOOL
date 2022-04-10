#include <positional.h>

// The constructor. It also has a unique, owning, pointer to a specific 'argument_parser' for the positional.
positional::positional::positional(std::string identification, std::string description, std::unique_ptr<parser_arguments::argument_parser> parser) :
    m_identification{std::move(identification)},
    m_description{std::move(description)},
    m_parser{std::move(parser)}
{}

// Get your identification.
[[maybe_unused]] const std::string &positional::positional::get_identification() const {
    return m_identification; // Return the identification.
}

// Get your description.
[[maybe_unused]] const std::string &positional::positional::get_description() const {
    return m_description; // Return the description.
}

// The default help description for a positional. Can be overridden for flexibility. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
std::string positional::positional::help_description() const {
    std::stringstream help_string_stream{}; // A string stream, used for creating your complete help description.

    // Transform the identification to all capitals:
    auto to_caps{m_identification};
    std::transform(to_caps.begin(), to_caps.end(), to_caps.begin(), [] (unsigned char character) { return std::toupper(character); });

    help_string_stream << '<' << to_caps << ">\t\t" << m_description; // The description
    return help_string_stream.str(); // Return the string. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
}

// Return the position of the positional argument. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
std::string positional::positional::recognize_position() const {
    // Transform the identification to all capitals:
    auto to_caps{m_identification};
    std::transform(to_caps.begin(), to_caps.end(), to_caps.begin(), [] (unsigned char character) { return std::toupper(character); });

    return to_caps; // Return the string. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
}

// Virtual method special for parsing.
std::unique_ptr<arguments::argument_base> positional::positional::parse_to_argument(const std::string &argument) {
    return m_parser->parse(m_identification, argument); // Parse the argument for an option. You are calling the 'parse' method on the 'm_parser' field.
}