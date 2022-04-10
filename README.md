# Command line tool

## Description
This project provides an implementation of a command line argument parser. You can give multiple arguments to your program. For example `./prog --verbose -s=344 -l=0.44`. These arguments are then properly parsed and displayed in the console. Various OOP techniques were used in the implementation.

For this project, old C++ code has been completely adapted, and provided with new functionality. In case one is curious about the old implementation, see the following files in this repository: [header file](lib_args_old/inc/lib_args.h) and [source file](lib_args_old/src/lib_args.cpp).

## Library format
The generated files for this project are given in the `lib_args_new` folder. This is a library in which all header and source files are given. However, various files are also classified in a subfolder. For example, all files associated with the `builder` pattern are in the `builders` folder. This gives more overview to all files that are present for the option parser.

The other files such as `main.cpp`, and the source files that 'run' the code, such as `program.h` and `program.cpp` are given outside this library.

Below is a file format for the folder `lib_args`. To indicate header files `[header files]` is used, to indicate all source files `[source files]` is used.
```text
lib_args_new/
+-- builders/
|  +-- inc/
|     +-- [header files]
|  +-- src/
|     +-- [source files]
+-- decorators/
|  +-- inc/
|     +-- [header files]
|  +-- src/
|     +-- [source files]
+-- parser/
|  +-- inc/
|     +-- [header files]
|  +-- src/
|     +-- [source files]
+-- CMakeLists.txt
```

## Overview of completed tasks
Below is a representation of various tasks that I have performed to make the application more accessible to OOP/SOLID principles.

1. A separate class has been created for an `option`. For this I created an abstract class. This class contains information about the short flag, long flag and a description for each option. In addition, a method has also been added that checks whether a specific argument from the command line can be parsed. A fully virtual parse method has also been added, to allow you to parse an argument to your option.
2. Concrete implementations have been made for the abstract `option` class. These are the following classes: `int_option`, `dbl_option`, `text_option`, and `flag_option`. These concrete classes also provide an implementation for the method that causes its representative argument to be parsed.
3. A base class has been created for an argument. An argument will belong to an option. This class is called `argument_base` in this case. It contains one method, which will return the identification of a long flag. It contains a virtual destructor, to enable polymorphism.
4. Concrete classes have been created for an argument. These classes inherit from the `argument_base` class. The following classes have been created: `int_argument`, `dbl_argument`, `text_argument` and `flag_argument`. These classes contain a specific field that stores the value with your long flag of an option.
5. A class `option_parser` has been created. This class implements its associated interface `i_option_parser`. The interface is designed to implement inheritance. It contains a method that parses all arguments (coming from the main function). It also contains a collection of all options created for the program. The parse method returns a collection of arguments that have actually been parsed.
6. The implementation of `program.cpp` has been changed to work with polymorphism for a collection of options that has been parsed.
7. After the first tests of the new program, the responsibilities should be better separated from each other. This is because an 'option' should not actually be responsible for parsing its argument, if any. Because of this, I have separated parsing from an option. However, it was no longer a necessity for an abstract `option` class. This allowed me to make a composition of this. It has become a composition in this case, because a specific `argument_parser` can only belong to one option at a time.
8. I have created an abstract `argument_parser`. These classes that implement this will implement the parsing.
9. To implement parsing for a specific type of argument, the following classes implement an `argument_parser`: `int_argument_parser`, `dbl_argument_parser`, `text_argument_parser` and a `flag_argument_parser`. Pay attention! There is also a `flag_argument_parser`, because a flag associated with it has a boolean value to indicate that it is present. All of these named classes implement parsing for an argument themselves.
10. Since an option has now become a composition (and is no longer an abstract class), the concrete implementations that inherit from an option are no longer necessary. For this reason, the classes `int_option`, `dbl_option`, `text_option` and `flag_option` have been removed.
11. Enabled to implement a collection of `options` within the `options_collection` class. It also adds and removes options. Your parser should not be responsible for this either. In addition, a collection has been created for parsed options. This is called `parsed_collection`. Both implement two different interfaces, to be able to separate the definition from the implementation (work via pointers).
12. The main function has been adjusted again to see if the composition has been implemented correctly.
13. After careful testing, options that are flags should now also be taken into account. Because of this, that `parse` method of the `option_parser` class has to be re-implemented. In addition, it must be possible to work with a wide variety of arguments from the command line. For example `--size=345` should also be able to be processed. For this I generated an `initialize_argument` class.
14. The `initialize_arguments` class ensures that all arguments coming from the command line are prepared. It generates a collection of arguments, all of which are separate from each other. This way you can constantly remove values from the front of the collection to get to the next argument. To apply any inheritance, and to decouple the concrete implementation, I also generated an interface for this called `i_initialize_arguments`.
15. The rest of the implementation has been modified to work with a collection of arguments.
16. The implementation of the parse method within `option_parser` has been changed to work with the collection of arguments. Getting this to work was pure pain, resulting in an explosion of my head (as stated in the order information). In the end it worked, so that a greater variety of command line arguments can be used.
17. After several tests, the error handling of options that have an argument, but is not given, has not yet been taken into account. Minor changes have been made to the implementation for this.
18. To display errors an `invalid_argument` class has been implemented for this. It inherits from `argument_base`. This also makes polymorphism possible for invalid arguments. If an option has no argument, or it is not valid, it will be noted in this class.
19. Minor bug fixed to the parse method, to enable proper error handling. Yes, it really is pure pain when you want to make this possible...
20. Extensive testing performed with a large number of arguments. All tests have been successfully completed.
21. Functionality for showing the help associated with all flags present. An extra method has been added to `option_parser`, along with its accompanying interface. This method returns all available options, in the form of a pointer. Pay attention! This is a constant reference, so making changes to the collection of options as an outsider is not possible. This method can also indicate which options are available for your parser. In addition, the `options_help` associated with all options can show a help. This class implements an interface. This disconnects the implementation. **Pay attention! Later on, this implementation was removed, as it was configured with a configurable help for your option parser. For further explanation, please refer to point 23.**
22. A builder has been added. This builder makes it possible to create complex objects in a simple and clear manner. In this case, it's an option parser. An interface called `i_parser_builder` is used for a builder. The class `parser_builder` implements this interface, and gives an implementation.
23. The possibility for a configurable 'help' has now been added. Two methods are available in the builder for this. One is for a default help where your flags should be `-h` or `--help`. With the other method you can determine this yourself. To make this possible I made a decorator for your option parser. You add an extra functionality to it, namely showing a help functionality associated with your parser. I have also chosen that your 'help' should use a collection of options. Since your option parser takes ownership of this collection, this class will also return a collection. However, your parser is for parsing only, and should not return a collection. In order not to create a dependency on this, I used a decorator. All files for this decorator are given as `parser_decorator` and `help_decorator`.
24. Numerical values of arguments are now checked for associated boundary values during parsing. You can indicate this via the builder. Then during parsing it will be checked whether your value is valid. This functionality is implemented with a `argument_parser` decorator. This decorator adds an extra functionality to a specific `argument_parser`, which checks whether the values fall within its limits.
25. The `arguments_collection` class is equipped with a singleton pattern, which means that only one instance of this class can exist. The instance is read-only, so no changes can be made to this only instance that allows it.
26. By creating a singleton pattern for `arguments_collection` the arguments from your command line can only be read. As a result, the implementation within the `option_parser` class had to be changed to work with only constant values of the arguments to be parsed.
27. Added support for positional arguments. This is applied in the same way as an `option` is implemented. 'Composition over inheritance' is also used. Also, the `option_parser` is provided with implementation for positional arguments.
28. Several improvements have been made to parsing positional arguments. In addition, an error handler has also been added for this, which shows when a certain positional argument cannot be parsed. The positional argument will contain an 'invalid_argument' in its own way.
29. Added support for default values of arguments. Each argument that is specified has a default value. First, all default arguments are passed to the `parser_builder`. Then these arguments are already added, and then the ownership of these parsed arguments is transferred to an `option_parser`. After parsing all arguments, this collection will be returned.

## Testing the program
It was checked whether the program correctly parsed all arguments, which are actually passed to the program. Several shell commands have been added for this, along with its output. Of course, you are completely free to test the program yourself, and to give it commands.

**Test 1:**

In this test, no specific arguments are passed to the program. The arguments are shown with their default values.

```shell
./my_app

The following arguments were passed to the program:
verbose: false
level: 0.5
size: 500
output: ./out.txt/
```

**Test 2:**

In this test you are asked to show the help of the program, so a description for all flags along with the positional arguments. Any ranges of options/flags are also shown along with default values.
Since your 'help' configuration can also be seen as an option/flag, this will also be reflected in the options output that has been parsed.

```shell
./my_app --help
my_app [FLAGS] <OUTPUT>

<OUTPUT>                output file name (default: ./out.txt/)

Flags:
-h, --help              print this help diagnostic
-v, --verbose           prints verbose diagnostics (default: false)
-l, --level             sets compression level (double in range: 0-1, default: 0.500000)
-s, --size              dictionary size in kB (integer in range: 1-1000, default: 500)

The following arguments were passed to the program:
verbose: false
level: 0.5
size: 500
output: ./out.txt/
help: true
```

**Test 3:**

Here only a flag is passed to the program. By default, the `verbose` option is set to 'false'. But since he is now present, this will yield 'true'.

```shell
./my_app --verbose

The following arguments were passed to the program:
verbose: true
level: 0.5
size: 500
output: ./out.txt/
```

**Test 4:**

A number of arguments are passed to the program. The result is then displayed. As you can see, the default value for the options that are provided is changed.

```shell
./my_app --size 455 -l 0.988 ./in.txt/

The following arguments were passed to the program:
verbose: false
level: 0.988
size: 455
output: ./in.txt/
```

**Test 5:**

Here the arguments passed to the program are not separated. Each option is provided with an argument by means of '='. As you can see this does not affect what is being parsed by the program.

```shell
./my_app -s=4559 -l=0.344

The following arguments were passed to the program:
verbose: false
level: 0.344
size: invalid argument - ERROR MESSAGE: "invalid range for value" -
output: ./out.txt/
```

**Test 6:**

Now the program is given the same options several times, but with different arguments. It has been decided to only link the last possible value associated with a certain option. Also, the positional argument is changed.

```shell
./my_app --size=455 --size=466 --size=788 ./in.txt/

The following arguments were passed to the program:
verbose: false
level: 0.5
size: 788
output: ./in.txt/
```

**Test 7:**

Now options are passed to the program, but it contains no arguments. This is considered an error, so an option now contains an 'invalid_argument'.

```shell
./my_app -v --size= -l

The following arguments were passed to the program:
verbose: true
level: invalid argument - ERROR MESSAGE: "no argument provided" -
size: invalid argument - ERROR MESSAGE: "no argument provided" -
output: ./out.txt/
```

**Test 8:**

Again no arguments are given to several options, but instead a positional argument is now given to the program. Options that do not contain an argument are of course provided with an 'invalid_argument'.

```shell
./my_app -v --size= --level ./file.txt/

The following arguments were passed to the program:
verbose: true
level: invalid argument - ERROR MESSAGE: "no argument provided" -
size: invalid argument - ERROR MESSAGE: "no argument provided" -
output: ./file.txt/
```

**Test 9:**

In this test a number of arguments are again passed to the program. But now one option contains no argument, and one option contains an invalid range. A positional argument is also provided. The output is visible in the `shell` command. You can see that an 'invalid argument' applies to these valid options.

```shell
./my_app -v -l 4.556 --size ./file.dsp/

The following arguments were passed to the program:
verbose: true
level: invalid argument - ERROR MESSAGE: "invalid range for value" -
size: invalid argument - ERROR MESSAGE: "no argument provided" -
output: ./file.dsp/
```

**Test 10:**

Of course there is also the chance that an option that contains a `double` or `int` will be accompanied by a text. In this case, this is also an 'invalid_argument'. The argument that is incorrect is also shown here.

```shell
./my_app --level=text_lvl -s text_sz ./outfile.dsp/

The following arguments were passed to the program:
verbose: false
level: invalid argument - ERROR MESSAGE: "text_lvl" -
size: invalid argument - ERROR MESSAGE: "text_sz" -
output: ./outfile.dsp/
```