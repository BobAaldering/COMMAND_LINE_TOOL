#ifndef COMMAND_LINE_TOOL_POSITIONAL_H
#define COMMAND_LINE_TOOL_POSITIONAL_H

#include <string> // Add the 'string' header.
#include <memory> // Add the 'memory' header.
#include <sstream> // Add the 'sstream' header.
#include <algorithm> // Add the 'algorithm' header.

#include <argument_parser.h> // Add the 'argument_parser' header.

namespace positional {
    // This is the 'positional' class. It may contain a single command line positional options.
    // Pay attention! In the implementation, positional arguments are considered a special kind of options.
    // I have chosen that it should not be seen specifically as an option, as it does not have certain properties of an option, such as a short flag for example. On the other hand, you have to give a positional argument an identifier etc.
    // That is why it has been decided to create a separate 'positional' class for this
    // Initially, each type of argument contained its own positional option, for example a double had a 'dbl_positional'. To better separate responsibilities, 'composition over inheritance' has been used. This was chosen because an 'positional' itself is not actually responsible for parsing arguments.
    // For further explanation see also: https://en.wikipedia.org/wiki/Composition_over_inheritance
    class positional {
    public:
        positional(std::string identification, std::string description, std::unique_ptr<parser_arguments::argument_parser> parser); // The constructor. It also has a unique, owning, pointer to a specific 'argument_parser' for the positional.

        [[maybe_unused]] [[nodiscard]] const std::string& get_identification() const; // Get your identification.
        [[maybe_unused]] [[maybe_unused]] [[nodiscard]] const std::string& get_description() const; // Get your description.

        [[nodiscard]] virtual std::string help_description() const; // The default help description for a positional. Can be overridden for flexibility. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
        [[nodiscard]] virtual std::string recognize_position() const; // Return the position of the positional argument. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
        [[nodiscard]] virtual std::unique_ptr<arguments::argument_base> parse_to_argument(const std::string& argument); // Virtual method special for parsing.

        virtual ~positional() = default; // Virtual destructor.

    private:
        std::string m_identification; // Your identification.
        std::string m_description; // Your description of the positional argument.

        std::unique_ptr<parser_arguments::argument_parser> m_parser; // A unique, owning, pointer to a specific argument parser. Here polymorphism is possible, as these can be objects inheriting from 'argument_parser'.
    };
}

#endif