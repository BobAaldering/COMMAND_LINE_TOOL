#ifndef COMMAND_LINE_TOOL_FLAG_ARGUMENT_H
#define COMMAND_LINE_TOOL_FLAG_ARGUMENT_H

#include <argument_base.h> // Add the 'argument_base' header.

namespace arguments {
    // This is the class 'flag_argument'. It inherits from 'argument_base'.
    // This class is able to store a flag argument. In this case, this is a boolean value to indicate of a specific flag is present.
    class flag_argument : public argument_base {
    public:
        flag_argument(const std::string& flag_identification, bool has_argument); // The constructor. The long flag of an option will be used for the identification.

        [[nodiscard]] bool get_has_argument() const; // A getter to your value, it is constant, so you are not able to modify its content.

    private:
        bool m_has_argument; // The real value, in the case a boolean to indicate of a flag is present.
    };
}

#endif