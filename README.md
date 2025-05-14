# strANSIseq

Simple library to format terminal text with ANSI escape sequences

# Building source code

To build the project run:
```bash
cd strANSIseq
mkdir build && cd build -DBUILD_EXAMPLES=ON
cmake .. && make
```

# Demonstration app

When the project have been built, you can run:
```bash
./strANSIseq -h
```
to get the demonstration app usage.

Note that zsh(macOS default) does not support fully all functions, and you need to run the app in bash.

# Example
Open the ![main.cpp](cpp:src/main.cpp) file to get an example how to use the lib.

# CONTRIBUTING
see [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.