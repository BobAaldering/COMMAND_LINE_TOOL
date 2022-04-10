#ifndef COMMAND_LINE_TOOL_I_OPTION_COLLECTION_H
#define COMMAND_LINE_TOOL_I_OPTION_COLLECTION_H

#include <memory> // Add the 'memory' header.
#include <vector> // Add the 'vector' header.

#include <option.h> // Add the 'option' header.

namespace collections {
    // This is the abstract class 'i_option_collection'. It has only abstract methods, so you can see this also as an interface.
    class i_option_collection {
    public:
        using collection = std::vector<std::unique_ptr<options::option>>; // The container used for storing arguments is a vector with an owning pointer, to your option. Here, the type it is called 'collection'.

        [[maybe_unused]] virtual void add_option(std::unique_ptr<options::option> option) = 0; // Abstract method to add a new option to your collection.
        [[maybe_unused]] virtual void remove_option(const std::string& long_flag) = 0; // Abstract method to remove an option from your collection.

        // Below are given two methods, named 'begin' and 'end'.
        // They return a constant iterator to the beginning or end of the collection.
        // It has been decided to use constant iterators in the program, so as not to be able to change the content either. You can also use range-based for loops.
        [[nodiscard]] virtual collection::const_iterator begin() const = 0; // This is also an abstract method. It is used to return a constant iterator to the beginning of your collection.
        [[nodiscard]] virtual collection::const_iterator end() const = 0; // This is also an abstract method. It is used to return a constant iterator to the end of your collection.

        virtual ~i_option_collection() = default; // Virtual destructor.
    };
}

#endif