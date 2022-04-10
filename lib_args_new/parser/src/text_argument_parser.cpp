#include <text_argument_parser.h>

// The parse method for your textual argument.
std::unique_ptr<arguments::argument_base> parser_arguments::text_argument_parser::parse(const std::string &flag_identification, const std::string &argument_value) const {
    return std::make_unique<arguments::text_argument>(flag_identification, argument_value); // Return a new text argument, with its textual value.
}
