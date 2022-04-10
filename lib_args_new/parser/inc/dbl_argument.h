#ifndef COMMAND_LINE_TOOL_DBL_ARGUMENT_H
#define COMMAND_LINE_TOOL_DBL_ARGUMENT_H

#include <argument_base.h> // Add the 'argument_base' header.

namespace arguments {
    // This is the class 'dbl_argument'. It inherits from 'argument_base'.
    // This class is able to store a double argument.
    class dbl_argument : public argument_base {
    public:
        dbl_argument(const std::string& flag_identification, double argument_value); // The constructor. The long flag of an option will be used for the identification.

        [[nodiscard]] double get_value() const; // A getter to your value, it is constant, so you are not able to modify its content.

    private:
        double m_argument_value; // The real value, in the case a double.
    };
}

#endif