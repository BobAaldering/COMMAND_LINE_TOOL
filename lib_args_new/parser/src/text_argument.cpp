#include <text_argument.h>

// The constructor. The long flag of an option will be used for the identification.
arguments::text_argument::text_argument(const std::string &flag_identification, std::string argument_value) :
    argument_base(flag_identification), // Assign the identification to the base class 'argument_base'.
    m_argument_value{std::move(argument_value)} // Initialize the value to your 'm_argument_value' field.
{}

// A getter to your value, it is constant, so you are not able to modify its content.
const std::string &arguments::text_argument::get_value() const {
    return m_argument_value; // Return the value of your string argument.
}