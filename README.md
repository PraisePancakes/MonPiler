# Mon Transpiler

The Mon Transpiler is a simple transpiler project designed to tokenize and lex a source file written in the Mon language, converts it to a gcc compatible file.

## Table of Contents
- [Introduction](#introduction)
- [Usage](#usage)
- [Components](#components)
    - [Tokenizer](#tokenizer)
    - [Lexer](#lexer)
- [Build and Run](#build-and-run)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The Mon Transpiler processes Mon language source files, providing tokenization and lexical analysis.At this early stage, the Transpiler so far includes a Tokenizer and Lexer and can parse a simple main function e.g. 
```
function main : int() {
    printf("hello");
    return 0;
}
```

## Usage

To use the Mon Transpiler, provide the path to a Mon language source file as a command-line argument.

```bash
./mon <path/to/inputfile.mon>
```

# COMPONENTS (EARLY STAGE)

## File

The file component, will take in external files via the command line, and give the file attributes such as a token count, word count, and file length (total characters), the file structure also contains the contents of a file

## Tokenizer

The tokenizer simply takes in an input file as long as its token count, and splits the input into individual valid tokens

## Lexer

The lexer iterates through each Node and attaches an enumerated value to its respective token, it returns a linked list of lexed tokens such that each node now has a non zero token type value.

# BUILD AND RUN

- create a sample.mon file

- here is some valid syntax that can be tokenized so far

```
function main : int(a : char, b : int, c : int[]) {
    return 0;
}
```

- copy the syntax into the sample.mon and then complete the steps below to build and run the lexer


## !! PROJECT USES CMAKE !! 
### FOLLOW STEPS TO BUILD PROJECT
- `cd "path_to_project_folder"`
- `mkdir build`
- `cd build`
- `cmake -G "preferred-generator" ..` e.g.. `cmake -G "MinGW Makefiles" ..`
- if preferred generator is MinGW use `mingw32-make` to build
- `./mon <path/to/inputfile.mon>`

## CONTRIBUTING

Contributions to the Mon Compiler project are welcome. If you find issues or want to enhance the functionality, please open a GitHub issue or submit a pull request.

## LICENSE

This project is licensed under the MIT License.









