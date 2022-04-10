#include <invalid_argument.h>

// The constructor. The long flag of an option will be used for the identification. It also has an error message, which is used to indicate why the argument is not valid.
arguments::invalid_argument::invalid_argument(const std::string &flag_identification, std::string error_message) :
    argument_base(flag_identification), // Assign the identification to the base class 'argument_base'.
    m_argument_value{std::move(error_message)} // Initialize the value to your 'm_argument_value' field.
{}

// A getter to your value, in this case an error message, so you are not able to modify its content.
std::string arguments::invalid_argument::get_value() const {
    std::stringstream invalid_string_stream{}; // A string stream, used for creating your error message.
    invalid_string_stream << "invalid argument - ERROR MESSAGE: " << std::quoted(m_argument_value) << " -"; // Create the error message for your invalid argument.
    return invalid_string_stream.str(); // Return the string. Important to note is that this method return just a 'string', and not a reference. This is because you cannot return a reference if your string only exists in the scope of this method.
}
