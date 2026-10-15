# C Preprocessor

A mini project written in C that implements selected C-preprocessing tasks: comment removal, header-file inclusion, and macro expansion. The code is organized into separate source files and built using a Makefile.

> **Project scope:** This is an educational implementation of selected preprocessor features, not a complete replacement for GCC's preprocessor.

## Features

- **Comment removal:** Attempts to remove single-line (`//`) and block (`/* ... */`) comments while preserving comment-like text inside quoted strings.
- **Header-file inclusion:** Handles `#include` directives for user headers and searches common Linux include directories for system headers.
- **Macro expansion:** Supports object-like macros (for example, `#define VALUE 100`) and function-like macros (for example, `#define SQUARE(x) ((x) * (x))`).
- **Preprocessed output:** Writes the result to a file with the `.i` extension.
- **Modular source code:** Separates the main program, file reading/writing, comment removal, macro expansion, and header inclusion into individual C files.

## Repository structure

| File | Purpose |
|---|---|
| `main.c` | Coordinates the preprocessing steps |
| `header.h` | Shared declarations and standard-library includes |
| `readFromFIle.c` | Reads the input source file into memory |
| `remove_comments.c` | Removes source comments |
| `macro_expansions.c` | Collects and expands object-like and function-like macros |
| `headerfile_inclusion.c` | Reads and inserts included header files |
| `writeToFile.c` | Writes the result to an `.i` output file |
| `Makefile` | Compiles and links the project |
| `test.c`, `testheader.h` | Example/test input files |

## Requirements

- GCC
- GNU Make
- Linux or a compatible environment. System-header lookup currently uses Linux include paths.

## Build

Clone the repository and enter its directory:

```bash
git clone https://github.com/mohammednaveed-web/C-Preprocessor.git
cd C-Preprocessor
make
```

To remove generated object files and the executable:

```bash
make clean
```

## Run

Pass one input C filename as the command-line argument:

```bash
./mypreprocessor test.c
```

The output-writing code is intended to create an `.i` file from the supplied filename (for example, `test.i`).

## Example macros

Object-like macro:

```c
#define VALUE 100
int number = VALUE;
```

Function-like macro:

```c
#define SQUARE(x) ((x) * (x))
int result = SQUARE(5);
```

## Current limitations

This project implements selected preprocessing operations for learning purposes. It does not implement the complete C preprocessing specification, including full conditional-compilation handling (`#if`, `#ifdef`, `#ifndef`, `#elif`, and `#endif`) or every macro edge case. Header lookup is currently based on specific Linux include paths, and nested includes, include guards, and complex comments/macros may not behave exactly like a compiler's preprocessor. Check the output against your test cases before using it as input to a compiler.

## Learning goals

- Understand how preprocessing transforms source text before compilation.
- Practice string handling, file I/O, dynamic memory allocation, and modular C programming.
- Explore how include directives and macro replacement work.

## License

No license has been specified yet. Add a license file if you want to define permissions for reuse and distribution.
