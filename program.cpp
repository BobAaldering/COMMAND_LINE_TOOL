#include "program.h"

// The constructor, the collection of parsed objects in passed to it.
program::program(std::unique_ptr<collections::i_parsed_collection> collection_of_arguments) :
    m_collection{std::move(collection_of_arguments)} // Move the ownership. This class ('program') is now owner of the collection of parsed objects.
{}

// The 'run' method. It is used to run the program.
void program::run() {
    // For debug purposes only: print all the arguments passed to the program.

    std::cout << "\nThe following arguments were passed to the program: \n";

    // Go through the collection of parsed arguments. You are using a base class, called 'argument_base'.
    // To get the value of a real argument, like an 'int_argument' of 'double_argument', you are using a dynamic cast.
    for (const auto& argument : *m_collection) {
        // Try to cast an 'argument_base' to an 'int_argument'.
        if (auto* int_argument = dynamic_cast<arguments::int_argument*>(argument.get()))
            std::cout << argument->get_identification() << ": " << int_argument->get_value() << std::endl;
        // Try to cast an 'argument_base' to a 'dbl_argument'.
        else if (auto* dbl_argument = dynamic_cast<arguments::dbl_argument*>(argument.get()))
            std::cout << argument->get_identification() << ": " << dbl_argument->get_value() << std::endl;
        // Try to cast an 'argument_base' to a 'text_argument'.
        else if (auto* text_argument = dynamic_cast<arguments::text_argument*>(argument.get()))
            std::cout << argument->get_identification() << ": " << text_argument->get_value() << std::endl;
        // Try to cast an 'argument_base' to a 'flag_argument'.
        else if (auto* flag_argument = dynamic_cast<arguments::flag_argument*>(argument.get()))
            std::cout << flag_argument->get_identification() << ": " << (flag_argument->get_has_argument() ? "true" : "false") << std::endl;
        // Try to cast an 'argument_base' to an 'invalid_argument'.
        else if (auto* invalid_argument = dynamic_cast<arguments::invalid_argument*>(argument.get()))
            std::cout << argument->get_identification() << ": " << invalid_argument->get_value() << std::endl;
    }
}