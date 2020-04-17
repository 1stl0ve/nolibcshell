# nolibcshell

This project is a minimal Linux shell written in C that is compiled 
without including libc.

## Compiling

There are three options for building this project:

1. An x86_64 binary using the `make shell` command.
2. An x86 binary using the `make shell32` command.
3. An x86_64 binary made with a unity build using the `make unity` command.

## Design

The shell is implemented in `shell.c` along with a custom library that
provides helpful functions needed by the shell.

The library is implemented in `strings.{c,h}` which contains helpful
functions for interacting with "strings," `heap.{c,h}` which contains
a simplistic heap implementation and `malloc()` and `free()` functions,
and `mylib.{c,h}` which primarily contains the wrapper functions for 
making system-calls.

System-calls are implemented in `$(ARCH)/syscall.h` as in-line assembly
macros. There are supported values for `$(ARCH)` are `x86` and `x86_64`.

The entrypoint for the shell is written in assembly in `$(ARCH)/entry.S`.
The `entry.S` file is necessary to provide the `_start` function and to
provide `argc`, `argv` and `envp` to `main()`.

## Credit

An excelent heap implementation tutorial: https://danlulu.com/malloc-tutorial.