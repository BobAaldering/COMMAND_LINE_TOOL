#ifndef COMMAND_LINE_TOOL_ARGUMENT_BASE_H
#define COMMAND_LINE_TOOL_ARGUMENT_BASE_H

#include <string> // Add the 'string' header.

namespace arguments {
    // This is the class 'argument_base'. It is used as a base class for all the arguments.
    class argument_base {
    public:
        explicit argument_base(std::string flag_identification); // The constructor. The long flag is used as an identification.

        [[nodiscard]] const std::string& get_identification() const; // Get the identification, so your long flag.
        virtual ~argument_base() = default; // Virtual destructor.

    private:
        std::string m_long_flag; // The long flag is used to recognize an argument with its corresponding long flag.
    };
}

#endif