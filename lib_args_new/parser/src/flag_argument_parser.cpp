#include <flag_argument_parser.h>

// The parse method for your flag argument.
std::unique_ptr<arguments::argument_base> parser_arguments::flag_argument_parser::parse(const std::string &flag_identification, const std::string &) const {
    // In the implementation it was decided to indicate the presence of a flag with a boolean.
    // If none are present, this respective value will be 'false'. If the flag is present, however, it will be 'true'.
    // Similarly, it is also possible to update flags, as they do not contain any arguments in the 'option_parser'.

    return std::make_unique<arguments::flag_argument>(flag_identification, true); // Return that a flag argument is present.
}