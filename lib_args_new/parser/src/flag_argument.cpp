#include <flag_argument.h>

// The constructor. The long flag of an option will be used for the identification.
arguments::flag_argument::flag_argument(const std::string &flag_identification, bool has_argument) :
    argument_base(flag_identification), // Assign the identification to the base class 'argument_base'.
    m_has_argument{has_argument} // Initialize the value to your 'm_has_argument' field.
{}

// A getter to your value, it is constant, so you are not able to modify its content.
bool arguments::flag_argument::get_has_argument() const {
    return m_has_argument; // Return the value of your flag argument.
}