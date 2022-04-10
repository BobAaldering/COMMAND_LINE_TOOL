#include <arguments_collection.h>

// Private constructor, used for your singleton pattern.
collections::arguments_collection::arguments_collection(int argc, char* argv[]) :
    m_arguments_value{}
{
    auto end_args = argv + argc; // Calculate the end of all the arguments.

    // Loop through the content of 'argv'.
    while (argv != end_args) {
        auto single_argument = std::strtok(*argv, "="); // Tokenize the character array. You are tokenizing with the '=' character. Pay attention. Here, you are using C-style character arrays.

        // While 'single_argument' is not NULL.
        while (single_argument != nullptr) {
            m_arguments_value.emplace_back(single_argument); // Add the argument to your collection.
            single_argument = std::strtok(nullptr, "="); // Tokenize the character array. You are tokenizing with the '=' character. Pay attention. Here, you are using C-style character arrays.
        }
        argv++; // Increment 'argv', to go to the next argument.
    }
}

// The getter, to retrieve all your arguments.
const collections::i_arguments_collection::collection &collections::arguments_collection::get_arguments() const {
    return m_arguments_value; // Return a constant reference to the collection of arguments. You cannot modify the content within the collection.
}

// Static method to initialize the arguments, and arguments count.
void collections::arguments_collection::initialize(int argc, char **argv) {
    // The variables 'argc' and 'argv' come from the arguments passed to the main function.
    m_static_count = argc; // Assign the value to the total count of arguments.
    m_static_value = argv; // Assign the value of the arguments (character arrays) to the value of arguments.
}

// Static constant method to get your only instance.
const collections::i_arguments_collection &collections::arguments_collection::get_instance() {
    static arguments_collection instance{m_static_count, m_static_value}; // The only instance. Only declared with the first call.
    return instance; // Return the only instance.
}