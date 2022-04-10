#include <parser_decorator.h>

// This is the constructor. It will have ownership about the 'inner value', what a option parser is.
decorator::parser_decorator::parser_decorator(std::unique_ptr<parser::i_option_parser> inner_value) :
    m_inner_value{std::move(inner_value)}
{}

// The 'parser' method. It will parse all the arguments.
std::unique_ptr<collections::i_parsed_collection> decorator::parser_decorator::parse(const collections::i_arguments_collection &arguments_collection) {
    return m_inner_value->parse(arguments_collection); // Parse the argument for your 'inner_value'. You are using a constant collection of arguments.
}