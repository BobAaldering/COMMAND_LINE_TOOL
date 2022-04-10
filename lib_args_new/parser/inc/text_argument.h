#ifndef COMMAND_LINE_TOOL_TEXT_ARGUMENT_H
#define COMMAND_LINE_TOOL_TEXT_ARGUMENT_H

#include <string> // Add the 'string' header.

#include <argument_base.h> // Add the 'argument_base' header.

namespace arguments {
    // This is the class 'text_argument'. It inherits from 'argument_base'.
    // This class is able to store a text argument.
    class text_argument : public argument_base {
    public:
        text_argument(const std::string& flag_identification, std::string argument_value); // The constructor. The long flag of an option will be used for the identification.

        [[nodiscard]] const std::string& get_value() const; // A getter to your value, it is constant, so you are not able to modify its content.

    private:
        std::string m_argument_value; // The real value, in the case a string.
    };
}

#endif