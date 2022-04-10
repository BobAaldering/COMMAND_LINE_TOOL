#ifndef COMMAND_LINE_TOOL_OPTION_H
#define COMMAND_LINE_TOOL_OPTION_H

#include <string> // Add the 'string' header.
#include <memory> // Add the 'memory' header.
#include <sstream> // Add the 'sstream' header.

#include <argument_base.h> // Add the 'argument_base' header.
#include <argument_parser.h> // Add the 'argument_parser' header.

namespace options {
    // This is the 'option' class. It may contain a single command line option.
    // An option may contain a short flag along with a long flag. In addition, it also has a description. There are several getters that provide this information.
    // Initially, each type of argument contained its own option, for example a double had a 'dbl_option'. To better separate responsibilities, 'composition over inheritance' has been used. This was chosen because an 'option' itself is not actually responsible for parsing arguments.
    // For further explanation see also: https://en.wikipedia.org/wiki/Composition_over_inheritance
    class option {
    public:
        option(char short_flag, const std::string_view& long_flag, const std::string_view& description, int arguments_count, std::unique_ptr<parser_arguments::argument_parser> parser); // The constructor. It also has a unique, owning, pointer to a specific 'argument_parser'.

        // The getters of this 'option' class:
        [[maybe_unused]] [[maybe_unused]] [[nodiscard]] char get_short_flag() const; // Get your short flag.
        [[maybe_unused]] [[nodiscard]] const std::string& get_long_flag() const; // Get your long flag.
        [[maybe_unused]] [[maybe_unused]] [[nodiscard]] const std::string& get_description() const; // Get your description.
        [[nodiscard]] int get_number_of_arguments() const; // Get the number of arguments.

        // The methods are virtual, to allow re-implementation:
        [[nodiscard]] virtual std::string help_description() const; // The default help description for an option. Can be overridden for flexibility. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
        [[nodiscard]] virtual bool is_flag(const std::string& flag) const; // Check if the specific argument is a flag.
        [[nodiscard]] virtual bool can_parse(const std::string& argument) const; // Check if your argument is a long flag, or a short flag. Can be overridden for flexibility.
        [[nodiscard]] virtual std::unique_ptr<arguments::argument_base> parse_to_argument(const std::string& argument); // Virtual method special for parsing.

        virtual ~option() = default; // Virtual destructor.

    private:
        char m_short_flag; // Your short flag.
        std::string m_long_flag; // Your long flag.
        std::string m_description; // Your description.
        int m_number_of_arguments; // The number of arguments that an option can have.

        std::unique_ptr<parser_arguments::argument_parser> m_parser; // A unique, owning, pointer to a specific argument parser. Here polymorphism is possible, as these can be objects inheriting from 'argument_parser'.
    };
}

#endif