#ifndef COMMAND_LINE_TOOL_OPTION_COLLECTION_H
#define COMMAND_LINE_TOOL_OPTION_COLLECTION_H

#include <stdexcept> // Add the 'stdexcept' header.

#include <i_option_collection.h> // Add the 'i_option_collection' header.

namespace collections {
    // This is the class 'option_collection'. It inherits from 'i_option_collection'.
    // This class is used to store several options.
    class option_collection : public i_option_collection {
    public:
        option_collection(); // The constructor.

        void add_option(std::unique_ptr<options::option> option) override; // Method to add a new option to your collection.
        void remove_option(const std::string& long_flag) override; // Method to remove an option from your collection.

        // Below are given two methods, named 'begin' and 'end'.
        // They return a constant iterator to the beginning or end of the collection.
        // It has been decided to use constant iterators in the program, so as not to be able to change the content either. You can also use range-based for loops.
        [[nodiscard]] collection::const_iterator begin() const override; // This is also a method. It is used to return a constant iterator to the beginning of your collection.
        [[nodiscard]] collection::const_iterator end() const override; // This is also a method. It is used to return a constant iterator to the end of your collection.

    private:
        collection m_option_collection; // Field to your collection of options.
    };
}

#endif