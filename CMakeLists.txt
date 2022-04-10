cmake_minimum_required(VERSION 3.20)
project(command_line_tool)

add_executable(command_line_tool)

set(target command_line_tool)

target_sources(${target}
        PRIVATE
        main.cpp # Add 'main.cpp' to the executable.
        program.cpp # Add 'program.cpp' to the executable.
        )

target_compile_features(${target} PRIVATE cxx_std_20) # Default C++ version is CPP20.
set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF) # Disable all language specific extensions.

# Set options for GNU-like compilers.
target_compile_options(${target} PRIVATE
        # Set warnings for all build types.
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer>
        # O3 optimisation in 'Release'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g>
        )

# Set options for MSVC compiler.
target_compile_options(${target} PRIVATE
        # Set warnings for all build types.
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        # O2 optimisation in 'Release'.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # Optimisation in 'Debug'
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )

# Enable the Address Sanitizer.
option(USE_ASAN "Use address sanitizer if available" ON)

execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(HAS_ASAN FALSE)

if (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    message("libasan found @${LIBASAN_PATH}")
    message("To disable the address sanitizer set USE_ASAN to OFF.\n")
    set(HAS_ASAN TRUE)
endif ()

if (HAS_ASAN AND USE_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
endif ()

add_subdirectory(lib_args_new)
target_link_libraries(${target} lib_args_new)