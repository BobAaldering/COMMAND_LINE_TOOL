add_library(lib_args_new)

target_sources(lib_args_new
        PRIVATE

        parser/src/option.cpp
        parser/src/positional.cpp

        parser/src/int_argument_parser.cpp
        parser/src/dbl_argument_parser.cpp
        parser/src/text_argument_parser.cpp
        parser/src/flag_argument_parser.cpp

        parser/src/argument_base.cpp
        parser/src/int_argument.cpp
        parser/src/dbl_argument.cpp
        parser/src/text_argument.cpp
        parser/src/flag_argument.cpp
        parser/src/invalid_argument.cpp

        parser/src/option_parser.cpp

        parser/src/option_collection.cpp
        parser/src/parsed_collection.cpp
        parser/src/positional_collection.cpp

        parser/src/arguments_collection.cpp

        builders/src/parser_builder.cpp

        decorators/src/parser_decorator.cpp
        decorators/src/help_decorator.cpp

        decorators/src/argument_decorator.cpp
        decorators/src/int_argument_decorator.cpp
        decorators/src/dbl_argument_decorator.cpp
        )

target_compile_features(lib_args_new PUBLIC cxx_std_17) # Default C++ version is CPP17.

target_include_directories(lib_args_new PUBLIC parser/inc/ decorators/inc/ builders/inc/) # Include these extra libraries. Used for a better overview of this library.

set_target_properties(lib_args_new PROPERTIES CXX_EXTENSIONS OFF) # Disable all language specific extensions.

# Set options for GNU-like compilers.
target_compile_options(lib_args_new PUBLIC
        # Set warnings for all build types.
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer>
        # O3 optimisation in 'Release'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g>
        )

# Set options for MSVC compiler.
target_compile_options(lib_args_new PUBLIC
        # Set warnings for all build types.
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        # O2 optimisation in 'Release'.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )