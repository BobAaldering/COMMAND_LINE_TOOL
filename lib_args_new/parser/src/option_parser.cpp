#include <option_parser.h>

// The constructor of your 'option_parser'.
parser::option_parser::option_parser(std::unique_ptr<collections::i_option_collection> option_collection, std::unique_ptr<collections::i_positional_collection> positional_collection, std::unique_ptr<collections::i_parsed_collection> parsed_collection) :
    m_options{std::move(option_collection)},
    m_positionals{std::move(positional_collection)},
    m_parsed{std::move(parsed_collection)}
{}

// This is the 'parse' method. It is used to parse all the argument given to the main function into specific options, and eventually positional arguments.
std::unique_ptr<collections::i_parsed_collection> parser::option_parser::parse(const collections::i_arguments_collection &arguments_collection) {
    // Make sure 'm_parser' is not NULL. To which all options have been parsed it will no longer be possible to do this again. After all, you only get command line arguments once or from the main function, so 'argc' and 'argv'.
    // For example, in the program itself it is not possible to add new options after 'building' an option parser. An option parser will therefore continue to use the same options, and once the program is started, no additional arguments can be passed.
    if (m_parsed == nullptr)
        throw std::invalid_argument("All options with their respective arguments are already parsed!"); // Throw an exception.

    parse_to_arguments(arguments_collection); // Parse all the arguments from 'arguments_collection'.

    return std::move(m_parsed); // Move the ownership of 'm_parsed' again. After parsing, this class is not an owner of a collection of parsed objects anymore. This is my design choice. For a specific parser, with specific arguments you only want to parse once. Since you only get 'argc' and 'argv' from your main function once.
}

// Private method, for the inner-loop of the parser.
void parser::option_parser::parse_to_arguments(const collections::i_arguments_collection &arguments_collection) const {
    auto arguments_ite = arguments_collection.get_arguments().begin(); // The iterator of the beginning of your arguments' collection.
    auto last = std::next(arguments_collection.get_arguments().begin()); // The iterator that will point to last, parsed, argument. In the first instance, this is the second argument of 'arguments_collection'.

    do {
        const auto argument = *(arguments_ite)++; // Get your argument, and increment the iterator.

        // Go through all your options.
        for (const auto& option : *m_options) {
            // Check if you can parse the specific 'argument'.
            if (option->can_parse(argument)) {
                // If you have only one argument for your flag.
                if (option->get_number_of_arguments() == 0) {
                    last = arguments_ite; // The current known last parsed argument.

                    // Try to parse the argument.
                    if (auto value = option->parse_to_argument(argument))
                        m_parsed->add_parsed_option(std::move(value)); // Parsing succeeded, add the parsed option.
                }
                // The option has arguments.
                else {
                    std::string next_argument{};
                    (arguments_ite == arguments_collection.get_arguments().end()) ? next_argument = "" : next_argument = *arguments_ite; // Additional check if 'arguments_ite' is not yet at the end.

                    last = arguments_ite; // The current known last parsed argument.

                    // Check if your 'next_argument' is not a flag.
                    // In addition, it is also checked whether you should not parse a positional argument yet. This is done by looking where the 'arguments_ite' is in the collection, minus the number of positional arguments present.
                    // For example, if you have a flag, but no argument is given for it, it will not consume any positional argument.
                    // After all, it is always expected that a positional argument is present in a certain composition.
                    if (option->is_flag(next_argument) && arguments_ite != (arguments_collection.get_arguments().end() - std::distance(m_positionals->begin(), m_positionals->end()))) {
                        auto number_of_arguments = option->get_number_of_arguments(); // Get the number of arguments for your option.

                        // As long as your option accepts arguments.
                        while (number_of_arguments) {
                            auto following_argument = *(arguments_ite)++; // Get your following argument, and increment the iterator.
                            last = arguments_ite; // The current known last parsed argument.

                            // Try to parse the argument.
                            if (auto value = option->parse_to_argument(following_argument)) {
                                m_parsed->add_parsed_option(std::move(value)); // Parsing succeeded, add the parsed option.
                                number_of_arguments--; // Parsed one argument. Decrement your number of arguments.
                            }
                            else {
                                m_parsed->add_parsed_option(std::make_unique<arguments::invalid_argument>(option->get_long_flag(), next_argument)); // Parsing did not succeed. Add an invalid argument.
                                number_of_arguments--; // Parsed one argument. Decrement your number of arguments.
                            }
                        }
                    }
                    // Your flag has no arguments. This is an error, so an invalid argument.
                    else
                        m_parsed->add_parsed_option(std::make_unique<arguments::invalid_argument>(option->get_long_flag(), "no argument provided")); // There was no argument provided. This is an 'invalid argument' for your option.
                }
            }
        }
    }
    while (arguments_ite != arguments_collection.get_arguments().end()); // While your iterator is not at the end of the collection.

    // At last, go through your positional arguments.
    for (const auto& positional : *m_positionals) {
        // You if there are still positional arguments. If not, the positional argument will keep its default value.
        if (last != arguments_collection.get_arguments().end()) {

            // Try to parse the positional argument.
            if (auto value = positional->parse_to_argument(*last))
                m_parsed->add_parsed_option(std::move(value)); // Parsing for the positional argument succeeded. Add it to all the 'parsed option'.
            else
                m_parsed->add_parsed_option(std::make_unique<arguments::invalid_argument>(positional->get_identification(), *last)); // Parsing did not succeed. Add an invalid argument.

            last++; // Increment 'last', its also just a simple constant iterator.
        }
    }
}