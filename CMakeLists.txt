
cmake_minimum_required(VERSION 3.28.0)

project(MonLang, VERSION 0.0.1 LANGUAGES C)

add_executable("mon" src/main.c src/file.c src/tokenizer.c src/lexer.c src/parser.c src/hash.c src/cgen.c)