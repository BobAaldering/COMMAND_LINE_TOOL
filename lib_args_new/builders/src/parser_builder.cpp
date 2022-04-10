#include <parser_builder.h>

// The constructor.
builder::parser_builder::parser_builder() :
    m_positional_collection{},
    m_option_collection{},
    m_parsed_collection{},
    m_parser{},
    m_is_decorated{}
{
    m_positional_collection = new collections::positional_collection; // A raw pointer to a collection of positional arguments.
    m_option_collection = new collections::option_collection; // A raw pointer to a collection of options.
    m_parsed_collection = new collections::parsed_collection; // A raw pointer to a collection of parsed objects.

    auto positional_collection = std::unique_ptr<collections::positional_collection>{m_positional_collection}; // Wrap the raw pointer into an owning pointer. Raw pointer will still point to the object. This will be further used in the builder.
    auto option_collection = std::unique_ptr<collections::option_collection>{m_option_collection}; // Wrap the raw pointer into an owning pointer. Raw pointer will still point to the object. This will be further used in the builder.
    auto parsed_collection = std::unique_ptr<collections::parsed_collection>{m_parsed_collection}; // Wrap the raw pointer into an owning pointer. Raw pointer will still point to the object. This will be further used in the builder.

    m_parser = std::make_unique<parser::option_parser>(std::move(option_collection), std::move(positional_collection), std::move(parsed_collection)); // Create a parser object.
}

// Method used for a default 'help' flag.
builder::i_parser_builder &builder::parser_builder::with_help_configuration(std::ostream &help_out_stream) {
    // Check if you not already have a decorator.
    if (m_is_decorated)
        throw std::invalid_argument("An error has happened! A decoration (help configuration) has already been added to the given parser!"); // Throw an exception.
    else
        m_is_decorated = true; // Assign 'true', you now will have a decorator for your help flag.

    // Add a decorator to the parser for showing your help.
    if (m_parser)
        m_parser = std::make_unique<decorator::help_decorator>('h', "help", help_out_stream, m_option_collection, m_positional_collection,std::move(m_parser));

    // Your 'help' is also an option, so also insert it as an option:
    if (m_option_collection)
        m_option_collection->add_option(std::make_unique<options::option>
                ('h', "help", "print this help diagnostic", 0,
                    std::make_unique<parser_arguments::flag_argument_parser>())); // Your 'help' flag will not have a default value.

    return *this;
}

// Method used for a customizable 'help' flag.
builder::i_parser_builder &builder::parser_builder::with_help_configuration(char help_short_flag, const std::string &help_long_flag, std::ostream& help_out_stream) {
    // Check if you not already have a decorator.
    if (m_is_decorated)
        throw std::invalid_argument("An error has happened! A decoration (help configuration) has already been added to the given parser!"); // Throw an exception.
    else
        m_is_decorated = true; // Assign 'true', you now will have a decorator for your help flag.

    // Add a decorator to the parser for showing your help.
    if (m_parser)
        m_parser = std::make_unique<decorator::help_decorator>(help_short_flag, help_long_flag, help_out_stream, m_option_collection, m_positional_collection, std::move(m_parser));

    // Your 'help' is also an option, so also insert it as an option:
    if (m_option_collection)
        m_option_collection->add_option(std::make_unique<options::option>
            (help_short_flag, help_long_flag, "print this help diagnostic", 0,
                std::make_unique<parser_arguments::flag_argument_parser>())); // Your 'help' flag will not have a default value.

    return *this;
}

// Method for a flag.
builder::i_parser_builder &builder::parser_builder::with_option(char short_flag, const std::string &long_flag, const std::string &description, bool default_value) {
    if (m_option_collection) {
        auto default_description = description + " (default: " + (default_value ? "true)" : "false)"); // This is used to add an extra description. It will include a default value within the description.

        // Add the option to your collection.
        m_option_collection->add_option(std::make_unique<options::option>
            (short_flag, long_flag, default_description, 0,
                std::make_unique<parser_arguments::flag_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::flag_argument>(long_flag, default_value));

    return *this;
}

// Method for an option with an integer argument.
builder::i_parser_builder &builder::parser_builder::with_int_option(char short_flag, const std::string &long_flag, const std::string &description, int arguments_count, int default_value) {
    if (m_option_collection) {
        auto default_description = description + " (default: " + std::to_string(default_value) + ")"; // This is used to add an extra description. It will include a default value within the description.

        // Add the option to your collection.
        m_option_collection->add_option(std::make_unique<options::option>
            (short_flag, long_flag, default_description, arguments_count,
                std::make_unique<parser_arguments::int_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::int_argument>(long_flag, default_value));

    return *this;
}

// Method for an option with an integer argument. It has range-based checking support for arguments.
builder::i_parser_builder &builder::parser_builder::with_int_option(char short_flag, const std::string &long_flag, const std::string &description, int arguments_count, const std::pair<int, int> &range_values, int default_value) {
    if (m_option_collection) {
        auto default_description = description + " (integer in range: " + std::to_string(range_values.first) + '-' + std::to_string(range_values.second) + ", default: " + std::to_string(default_value) + ")"; // This is used to add an extra description. It will include a default value within the description, and also range-based values.

        // Add the option to your collection.
        m_option_collection->add_option(std::make_unique<options::option>
            (short_flag, long_flag, default_description, arguments_count,
                std::make_unique<decorator::int_argument_decorator>(
                    std::make_unique<parser_arguments::int_argument_parser>(),
                        range_values)));

    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::int_argument>(long_flag, default_value));

    return *this;
}

// Method for an option with a double argument.
builder::i_parser_builder &builder::parser_builder::with_dbl_option(char short_flag, const std::string &long_flag, const std::string &description, int arguments_count, double default_value) {
    if (m_option_collection) {
        auto default_description = description + " (default: " + std::to_string(default_value) + ")"; // This is used to add an extra description. It will include a default value within the description.

        // Add the option to your collection.
        m_option_collection->add_option(std::make_unique<options::option>
            (short_flag, long_flag, default_description, arguments_count,
                std::make_unique<parser_arguments::dbl_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::dbl_argument>(long_flag, default_value));

    return *this;
}

// Abstract method for an option with a double argument. It has range-based checking support for arguments.
builder::i_parser_builder &builder::parser_builder::with_dbl_option(char short_flag, const std::string &long_flag, const std::string &description, int arguments_count, const std::pair<int, int> &range_values, double default_value) {
    if (m_option_collection) {
        auto default_description = description + " (double in range: " + std::to_string(range_values.first) + '-' + std::to_string(range_values.second) + ", default: " + std::to_string(default_value) + ")"; // This is used to add an extra description. It will include a default value within the description, and also range-based values.

        // Add the option to your collection.
        m_option_collection->add_option(std::make_unique<options::option>
            (short_flag, long_flag, default_description, arguments_count,
                std::make_unique<decorator::dbl_argument_decorator>(
                    std::make_unique<parser_arguments::dbl_argument_parser>(),
                        range_values)));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::dbl_argument>(long_flag, default_value));

    return *this;
}

// Method for an option with a text argument.
builder::i_parser_builder &builder::parser_builder::with_text_option(char short_flag, const std::string &long_flag, const std::string &description, int arguments_count, const std::string &default_value) {
    if (m_option_collection) {
        auto default_description = description + " (default: " + default_value + ")"; // This is used to add an extra description. It will include a default value within the description.

        // Add the option to your collection.
        m_option_collection->add_option(std::make_unique<options::option>
            (short_flag, long_flag, default_description, arguments_count,
                std::make_unique<parser_arguments::text_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::text_argument>(long_flag, default_value));

    return *this;
}

// Method for a text positional argument.
builder::i_parser_builder &builder::parser_builder::with_text_positional(const std::string &positional_identification, const std::string& description, const std::string &default_value) {
    if (m_positional_collection) {
        auto default_description = description + " (default: " + default_value + ")"; // This is used to add an extra description. It will include a default value within the description.

        // Add the positional option to your collection.
        m_positional_collection->add_positional(std::make_unique<positional::positional>
            (positional_identification, default_description,
                std::make_unique<parser_arguments::text_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::text_argument>(positional_identification, default_value));

    return *this;
}

// Method for an integer positional argument.
builder::i_parser_builder &builder::parser_builder::with_int_positional(const std::string &positional_identification, const std::string &description, int default_value) {
    if (m_positional_collection) {
        auto default_description = description + " (default: " + std::to_string(default_value) + ")"; // This is used to add an extra description. It will include a default value within the description.

        // Add the positional option to your collection.
        m_positional_collection->add_positional(std::make_unique<positional::positional>
            (positional_identification, default_description,
                std::make_unique<parser_arguments::int_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::int_argument>(positional_identification, default_value));

    return *this;
}

// Method for a double positional argument.
builder::i_parser_builder &builder::parser_builder::with_dbl_positional(const std::string &positional_identification, const std::string &description, double default_value) {
    if (m_positional_collection) {
        auto default_description = description + " (default: " + std::to_string(default_value) + ")"; // This is used to add an extra description. It will include a default value within the description.

        // Add the positional option to your collection.
        m_positional_collection->add_positional(std::make_unique<positional::positional>
            (positional_identification, default_description,
                std::make_unique<parser_arguments::dbl_argument_parser>()));
    }

    // Add the default value to the collections of parsed objects.
    if (m_parsed_collection)
        m_parsed_collection->add_parsed_option(std::make_unique<arguments::dbl_argument>(positional_identification, default_value));

    return *this;
}

// Method to create an option parser.
std::unique_ptr<parser::i_option_parser> builder::parser_builder::make() {
    m_option_collection = nullptr; // Assign NULL to this pointer. You cannot use it anymore when calling methods on an instance of this class.
    m_positional_collection = nullptr; // Assign NULL to this pointer. You cannot use it anymore when calling methods on an instance of this class.
    m_parsed_collection = nullptr; // Assign NULL to this pointer. You cannot use it anymore when calling methods on an instance of this class.

    return std::move(m_parser); // Move the ownership of your parser.
}

// Free function, just used for a fancy experience when creating a builder.
builder::parser_builder builder::default_builder() {
    return {};
}