#ifndef COMMAND_LINE_TOOL_ARGUMENTS_COLLECTION_H
#define COMMAND_LINE_TOOL_ARGUMENTS_COLLECTION_H

#include <cstring> // Add the 'cstring' header.

#include <i_arguments_collection.h> // Add the 'i_arguments_collection' header.

namespace collections {
    // This is the class 'arguments_collection'. It inherits from 'i_argument_collection'.
    // The class is used for storing program arguments, that are passed through your main function.
    // Also, a singleton pattern is used for this class. You can only have one instance.
    class arguments_collection : public i_arguments_collection{
    public:
        [[nodiscard]] const collection& get_arguments() const override; // The getter, to retrieve all your arguments.

        static void initialize(int argc, char* argv[]); // Static method to initialize the arguments, and arguments count.
        static const i_arguments_collection& get_instance(); // Static constant method to get your only instance.

        arguments_collection(const arguments_collection&) = delete; // Delete the copy constructor. No copies are allowed.
        arguments_collection& operator=(const arguments_collection&) = delete; // Delete the copy assignment operator. No copies are allowed.

    private:
        arguments_collection(int argc, char* argv[]); // Private constructor, used for your singleton pattern.

        collection m_arguments_value; // The collection of arguments.

        static inline int m_static_count; // Static value for the arguments count.
        static inline char** m_static_value; // Static variable for the arguments value.
    };
}

#endif