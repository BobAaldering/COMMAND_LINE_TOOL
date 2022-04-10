#ifndef COMMAND_LINE_TOOL_I_PARSED_COLLECTION_H
#define COMMAND_LINE_TOOL_I_PARSED_COLLECTION_H

#include <memory> // Add the 'memory' header.
#include <vector> // Add the 'vector' header.

#include <argument_base.h> // Add the 'argument_base' header.

namespace collections {
    // This is the abstract class 'i_parsed_collection'. It has only abstract methods, so you can see this also as an interface.
    class i_parsed_collection {
    public:
        using parsed_arguments_collection = std::vector<std::unique_ptr<arguments::argument_base>>; // The container used for storing parsed arguments is a vector with an owning pointer, to your argument base. It is possible to use polymorphism in this context. Here, the type it is called 'collection'.

        virtual void add_parsed_option(std::unique_ptr<arguments::argument_base> argument) = 0; // Abstract method to add a new parsed argument to your collection.

        // Below are given two methods, named 'begin' and 'end'.
        // They return a constant iterator to the beginning or end of the collection.
        // It has been decided to use constant iterators in the program, so as not to be able to change the content either. You can also use range-based for loops.
        [[nodiscard]] virtual parsed_arguments_collection::const_iterator begin() const = 0; // This is also an abstract method. It is used to return a constant iterator to the beginning of your collection.
        [[nodiscard]] virtual parsed_arguments_collection::const_iterator end() const = 0; // This is also an abstract method. It is used to return a constant iterator to the end of your collection.

        virtual ~i_parsed_collection() = default; // Virtual destructor.
    };
}

#endif