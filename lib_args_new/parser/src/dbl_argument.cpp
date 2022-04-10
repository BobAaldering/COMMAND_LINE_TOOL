#include <dbl_argument.h>

// The constructor. The long flag of an option will be used for the identification.
arguments::dbl_argument::dbl_argument(const std::string &flag_identification, double argument_value) :
    argument_base(flag_identification), // Assign the identification to the base class 'argument_base'.
    m_argument_value{argument_value} // Initialize the value to your 'm_argument_value' field.
{}

// A getter to your value, it is constant, so you are not able to modify its content.
double arguments::dbl_argument::get_value() const {
    return m_argument_value; // Return the value of your double argument.
}
