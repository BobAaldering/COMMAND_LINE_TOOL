#ifndef COMMAND_LINE_TOOL_INVALID_ARGUMENT_H
#define COMMAND_LINE_TOOL_INVALID_ARGUMENT_H

#include <sstream> // Add the 'sstream' header.
#include <iomanip> // Add the 'iomanip' header.

#include <argument_base.h> // Add the 'argument_base' header.

namespace arguments {
    // This is the class 'invalid_argument'. It inherits from 'argument_base'.
    // This class indicates that the argument associated with a particular option is not correct, it is not valid.
    class invalid_argument : public argument_base {
    public:
        invalid_argument(const std::string& flag_identification, std::string error_message); // The constructor. The long flag of an option will be used for the identification. It also has an error message, which is used to indicate why the argument is not valid.

        [[nodiscard]] std::string get_value() const; // A getter to your value, in this case an error message, so you are not able to modify its content. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.

    private:
        std::string m_argument_value; // The error associated with the argument is stored in this field. A 'string' is used.
    };
}

#endif