#ifndef COMMAND_LINE_TOOL_PARSED_COLLECTION_H
#define COMMAND_LINE_TOOL_PARSED_COLLECTION_H

#include <algorithm> // Add the 'algorithm' header.

#include <i_parsed_collection.h> // Add the 'i_parsed_collection' header.

namespace collections {
    // This is the class 'parsed_collection'. It inherits from 'i_parsed_collection'.
    // This class is used to store several parsed arguments by the 'option parser'.
    class parsed_collection : public i_parsed_collection {
    public:
        parsed_collection(); // The constructor.

        void add_parsed_option(std::unique_ptr<arguments::argument_base> argument) override; // Method to add a new parsed argument to your collection. There is no 'remove_parsed_option' method, because you never want to remove objects from the collection. Only what is parsed is added.

        // Below are given two methods, named 'begin' and 'end'.
        // They return a constant iterator to the beginning or end of the collection.
        // It has been decided to use constant iterators in the program, so as not to be able to change the content either. You can also use range-based for loops.
        [[nodiscard]] parsed_arguments_collection::const_iterator begin() const override; // This is also a method. It is used to return a constant iterator to the beginning of your collection.
        [[nodiscard]] parsed_arguments_collection::const_iterator end() const override; // This is also a method. It is used to return a constant iterator to the end of your collection.

    private:
        parsed_arguments_collection m_parsed_collection; // Field to your collection of parsed arguments.
    };
}

#endif