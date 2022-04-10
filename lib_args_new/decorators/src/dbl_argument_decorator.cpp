#include <dbl_argument_decorator.h>

// The constructor, with the inner value to an 'argument_parser', and the range-values. For this a 'pair' is used that contains the minimum and maximum value.
decorator::dbl_argument_decorator::dbl_argument_decorator(std::unique_ptr<parser_arguments::argument_parser> inner_value, const std::pair<double, double> &ranges) :
    argument_decorator(std::move(inner_value)),
    m_minimum_range{ranges.first}, // The first value of the 'pair' is the minimum value.
    m_maximum_range{ranges.second} // The second value of the 'pair' is the maximum value.
{}

// The 'parser' method. It will parse an option with its argument.
std::unique_ptr<arguments::argument_base> decorator::dbl_argument_decorator::parse(const std::string &flag_identification, const std::string &argument_value) const {
    auto value = argument_decorator::parse(flag_identification, argument_value); // Parse an argument. The type of 'value' will be a particular class that inherits from an 'argument_base' class.

    // Check if your 'value' can be cast to a double argument with a 'dynamic_cast'.
    if (auto* dbl_value = dynamic_cast<arguments::dbl_argument*>(value.get())) {
        // Check if the value is not in the range that is defined for your argument.
        if (dbl_value->get_value() < m_minimum_range || dbl_value->get_value() > m_maximum_range)
            value = std::make_unique<arguments::invalid_argument>(flag_identification, "invalid range for value"); // You have an invalid range. Value is now an 'invalid_argument'.
    }
    return value; // Return 'value'.
}