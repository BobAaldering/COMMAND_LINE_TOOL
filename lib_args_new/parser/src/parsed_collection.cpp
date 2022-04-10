#include <parsed_collection.h>

// The constructor. It is just a default constructor. Here for a better overview...
collections::parsed_collection::parsed_collection() :
    m_parsed_collection{}
{}

// Method to add a new parsed argument to your collection. There is no 'remove_parsed_option' method, because you never want to remove objects from the collection. Only what is parsed is added.
void collections::parsed_collection::add_parsed_option(std::unique_ptr<arguments::argument_base> argument) {
    // Check if your flag is not yet in the vector.
    auto value = std::find_if(m_parsed_collection.begin(), m_parsed_collection.end(), [&] (std::unique_ptr<arguments::argument_base>& find_argument) { return find_argument->get_identification() == argument->get_identification(); });

    // If the value is your end, it's not yet in your vector.
    if (value == m_parsed_collection.end())
        m_parsed_collection.push_back(std::move(argument)); // Add the argument.
    else
        value->swap(argument); // Your flag is already in the collection of parsed arguments. Swap the arguments.
}

// This is also a method. It is used to return a constant iterator to the beginning of your collection.
std::vector<std::unique_ptr<arguments::argument_base>>::const_iterator collections::parsed_collection::begin() const {
    return m_parsed_collection.begin(); // Return the beginning of the collection.
}

// This is also a method. It is used to return a constant iterator to the end of your collection.
std::vector<std::unique_ptr<arguments::argument_base>>::const_iterator collections::parsed_collection::end() const {
    return m_parsed_collection.end(); // Return the beginning of the collection.
}