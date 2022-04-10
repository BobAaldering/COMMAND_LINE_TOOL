#include <option_collection.h>

// The constructor. It is just a default constructor. Here for a better overview...
collections::option_collection::option_collection() :
    m_option_collection{}
{}

// Method to add a new option to your collection.
void collections::option_collection::add_option(std::unique_ptr<options::option> option) {
    // First, check if your option is currently available in your collection with options.
    for (const auto& single_option : m_option_collection) {
        if (single_option->get_long_flag() == option->get_long_flag())
            throw std::invalid_argument("An error has happened! The appropriate option for your command line is already there!"); // Throw an exception.
    }

    m_option_collection.push_back(std::move(option)); // Your option is not in the collection, add it.
}

// Method to remove an option from your collection.
void collections::option_collection::remove_option(const std::string &long_flag) {
    // Find your flag, that is given as the argument of this method.
    for (auto iterator = m_option_collection.begin(); iterator != m_option_collection.end(); iterator++){
        if (iterator->get()->get_long_flag() == long_flag){
            m_option_collection.erase(iterator); // Remove the option.
            break;
        }
    }
}

// This is also a method. It is used to return a constant iterator to the beginning of your collection.
std::vector<std::unique_ptr<options::option>>::const_iterator collections::option_collection::begin() const {
    return m_option_collection.begin(); // Return the beginning of the collection.
}

// This is also a method. It is used to return a constant iterator to the end of your collection.
std::vector<std::unique_ptr<options::option>>::const_iterator collections::option_collection::end() const {
    return m_option_collection.end(); // Return the end of the collection.
}