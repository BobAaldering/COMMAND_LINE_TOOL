#ifndef COMMAND_LINE_TOOL_POSITIONAL_COLLECTION_H
#define COMMAND_LINE_TOOL_POSITIONAL_COLLECTION_H

#include <i_positional_collection.h> // Add the 'i_positional_collection' header.

namespace collections {
    // This is the class 'positional_collection'. It inherits from 'i_positional_collection'.
    // This class is used to store the positional arguments used in the program.
    class positional_collection : public i_positional_collection {
    public:
        positional_collection(); // The constructor.

        void add_positional(std::unique_ptr<positional::positional> positional) override; // Method to add a new positional argument to your collection.
        void remove_positional(const std::string &identification) override; // Method to remove a positional argument from your collection.

        // Below are given two methods, named 'begin' and 'end'.
        // They return a constant iterator to the beginning or end of the collection.
        // It has been decided to use constant iterators in the program, so as not to be able to change the content either. You can also use range-based for loops.
        [[nodiscard]] collection::const_iterator begin() const override; // This is also a method. It is used to return a constant iterator to the beginning of your collection.
        [[nodiscard]] collection::const_iterator end() const override; // This is also a method. It is used to return a constant iterator to the end of your collection.

    private:
        collection m_positional_collection; // Field to your collection of positional arguments 'options'.
    };
}

#endif