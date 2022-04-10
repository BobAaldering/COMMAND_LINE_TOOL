#ifndef COMMAND_LINE_TOOL_DBL_ARGUMENT_DECORATOR_H
#define COMMAND_LINE_TOOL_DBL_ARGUMENT_DECORATOR_H

#include <argument_decorator.h> // Add the 'argument_decorator' header.
#include <dbl_argument.h> // Add the 'dbl_argument' header.
#include <invalid_argument.h> // Add the 'invalid_argument' header.

namespace decorator {
    // This is the class 'dbl_argument_decorator'. It inherits from an 'argument_decorator'.
    // This decorator is used to check the values of an argument for its range. You add extra functionality to a parser for an argument, which is why a decorator was chosen.
    class dbl_argument_decorator : public argument_decorator {
    public:
        explicit dbl_argument_decorator(std::unique_ptr<parser_arguments::argument_parser> inner_value, const std::pair<double, double>& ranges); // The constructor, with the inner value to an 'argument_parser', and the range-values. For this a 'pair' is used that contains the minimum and maximum value.

        [[nodiscard]] std::unique_ptr<arguments::argument_base> parse(const std::string &flag_identification, const std::string &argument_value) const override; // The 'parser' method. It will parse an option with its argument.

    private:
        double m_minimum_range; // The minimum value of the range.
        double m_maximum_range; // The maximum value of the range.
    };
}

#endif