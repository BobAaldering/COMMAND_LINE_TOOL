#ifndef COMMAND_LINE_TOOL_I_ARGUMENTS_COLLECTION_H
#define COMMAND_LINE_TOOL_I_ARGUMENTS_COLLECTION_H

#include <vector> // Add the 'vector' header.
#include <string> // Add the 'string' header.

namespace collections {
    // This is the abstract class 'i_arguments_collection'. It has only abstract methods, so you can see this also as an interface.
    class i_arguments_collection {
    public:
        using collection = std::vector<std::string>; // The container used for storing arguments is a vector with strings. Here, the type it is called 'collection'.

        [[nodiscard]] virtual const collection& get_arguments() const = 0; // A getter to retrieve the arguments within the collection. It returns a constant reference, so you cannot modify the content of your collection.
        virtual ~i_arguments_collection() = default; // Virtual destructor.
    };
}

#endif