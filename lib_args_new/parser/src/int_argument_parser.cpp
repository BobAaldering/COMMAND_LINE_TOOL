#include <int_argument_parser.h>

// The parse method for your integer argument.
std::unique_ptr<arguments::argument_base> parser_arguments::int_argument_parser::parse(const std::string &flag_identification, const std::string &argument_value) const {
    int result{}; // The variable that will store the result.
    std::string_view argument_parse = argument_value; // Use 'string_view' for simplicity (just a fancy wrapper around a character array).
    auto[value, exception] = std::from_chars(argument_parse.begin(), argument_parse.end(), result); // Try to parse your argument to a real integer value.

    // Check if parsing succeeded.
    if (exception == std::errc())
        return std::make_unique<arguments::int_argument>(flag_identification, result); // Return your result. It is a 'int_argument'.

    return nullptr; // Parsing failed. I used a 'nullptr' to indicate that parsing failed.
}