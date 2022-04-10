#ifndef COMMAND_LINE_TOOL_INT_ARGUMENT_H
#define COMMAND_LINE_TOOL_INT_ARGUMENT_H

#include <argument_base.h> // Add the 'argument_base' header.

namespace arguments {
    // This is the class 'int_argument'. It inherits from 'argument_base'.
    // This class is able to store an integer argument.
    class int_argument : public argument_base {
    public:
        int_argument(const std::string& flag_identification, int argument_value); // The constructor. The long flag of an option will be used for the identification.

        [[nodiscard]] int get_value() const; // A getter to your value, it is constant, so you are not able to modify its content.

    private:
        int m_argument_value; // The real value, in the case an integer.
    };
}

#endif