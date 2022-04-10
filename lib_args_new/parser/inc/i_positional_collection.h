#ifndef COMMAND_LINE_TOOL_I_POSITIONAL_COLLECTION_H
#define COMMAND_LINE_TOOL_I_POSITIONAL_COLLECTION_H

#include <memory> // Add the 'memory' header.
#include <vector> // Add the 'vector' header.

#include <positional.h> // Add the 'positional' header.

namespace collections {
    // This is the abstract class 'i_positional_collection'. It has only abstract methods, so you can see this also as an interface.
    class i_positional_collection {
    public:
        using collection = std::vector<std::unique_ptr<positional::positional>>; // The container used for storing positional options is a vector with an owning pointer, to your positional option. Here, the type it is called 'collection'.

        // Pay attention! In the implementation, positional arguments are considered a special kind of options.
        // I have chosen that it should not be seen specifically as an option, as it does not have certain properties of an option, such as a short flag for example. On the other hand, you have to give a positional argument an identifier etc.
        // That is why it has been decided to create a separate 'positional' class for this, see its implementation.

        [[maybe_unused]] virtual void add_positional(std::unique_ptr<positional::positional> positional) = 0; // Abstract method to add a new positional option to your collection.
        [[maybe_unused]] virtual void remove_positional(const std::string& identification) = 0; // Abstract method to remove a positional option from your collection.

        // Below are given two methods, named 'begin' and 'end'.
        // They return a constant iterator to the beginning or end of the collection.
        // It has been decided to use constant iterators in the program, so as not to be able to change the content either. You can also use range-based for loops.
        [[nodiscard]] virtual collection::const_iterator begin() const = 0; // This is also an abstract method. It is used to return a constant iterator to the beginning of your collection.
        [[nodiscard]] virtual collection::const_iterator end() const = 0; // This is also an abstract method. It is used to return a constant iterator to the end of your collection.

        virtual ~i_positional_collection() = default; // Virtual destructor.
    };
}

#endif