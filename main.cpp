#include <arguments_collection.h> // Add the 'arguments_collection' header.
#include <parser_builder.h> // Add the 'parser_builder' header.

#include "program.h" // Add the 'program' header.

// This is the main function of the program.
int main(int argc, char *argv[]) {
    collections::arguments_collection::initialize(argc, argv); // Initialize a collection that contains arguments here. Do this with 'argc' and 'argv'.

    // This is where your parser is created, along with its options.
    auto parser = builder::default_builder()
            .with_help_configuration('h', "help", std::cout) // Add a 'help' configuration. Here 'help' is used as an identifier to display the help menu in the console.
            .with_option('v', "verbose", "prints verbose diagnostics", false) // Add the 'verbose' option.
            .with_dbl_option('l', "level", "sets compression level", 1, {0.0, 1.0}, 0.5) // Add the 'level' option, with range-based values.
            .with_int_option('s', "size", "dictionary size in kB", 1, {1, 1000}, 500) // Add the 'size' option, with range-based values.
            .with_text_positional("output", "output file name", "./out.txt/") // Add a positional argument, with the default './out.txt/' value.
            .make(); // Create a parser object.

    auto parsed_collection = parser->parse(collections::arguments_collection::get_instance()); // Parse all the arguments. The parser returns the collection of parsed arguments.

    program program{std::move(parsed_collection)}; // The collection of parsed objects is injected into your 'program'.

    program.run(); // Run the program.

    return 0;
}