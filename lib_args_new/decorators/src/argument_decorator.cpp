#include <argument_decorator.h>

// This is the constructor. It will have ownership about the 'inner value', what an argument parser is.
decorator::argument_decorator::argument_decorator(std::unique_ptr<parser_arguments::argument_parser> inner_value) :
    m_inner_value{std::move(inner_value)}
{}

// The 'parser' method. It will parse an option with its argument.
std::unique_ptr<arguments::argument_base> decorator::argument_decorator::parse(const std::string &flag_identification, const std::string &argument_value) const {
    return m_inner_value->parse(flag_identification, argument_value); // Parse the argument for your 'inner_value'. You are using an identification for a flag, and the respective value of an argument.
}