#include <positional_collection.h>

// The constructor. It is just a default constructor. Here for a better overview...
collections::positional_collection::positional_collection() :
    m_positional_collection{}
{}

// Method to add a new positional argument to your collection.
void collections::positional_collection::add_positional(std::unique_ptr<positional::positional> positional) {
    // First, check if your option is currently available in your collection with positional arguments.
    for (const auto& single_positional : m_positional_collection) {
        if (single_positional->get_identification() == positional->get_identification())
            throw std::invalid_argument("An error has happened! The appropriate positional argument for your command line is already there!"); // Throw an exception
    }

    m_positional_collection.push_back(std::move(positional)); // Your positional argument is not in the collection, add it.
}

// Method to remove a positional argument from your collection.
void collections::positional_collection::remove_positional(const std::string &identification) {
    // Find your flag, that is given as the argument of this method.
    for (auto iterator = m_positional_collection.begin(); iterator != m_positional_collection.end(); iterator++){
        if (iterator->get()->get_identification() == identification){
            m_positional_collection.erase(iterator); // Remove it from your collection.
            break;
        }
    }
}

// This is also a method. It is used to return a constant iterator to the beginning of your collection.
std::vector<std::unique_ptr<positional::positional>>::const_iterator collections::positional_collection::begin() const {
    return m_positional_collection.begin(); // Return the beginning of the collection.
}

// This is also a method. It is used to return a constant iterator to the end of your collection.
std::vector<std::unique_ptr<positional::positional>>::const_iterator collections::positional_collection::end() const {
    return m_positional_collection.end(); // Return the end of the collection.
}