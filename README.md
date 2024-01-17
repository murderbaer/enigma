# Enigma Backend

[![pipeline status](https://gitlab.rivercry.com/arifhasanic/enigma/badges/main/pipeline.svg)](https://gitlab.rivercry.com/arifhasanic/enigma/commits/main)
[![coverage report: backend](https://gitlab.rivercry.com/arifhasanic/enigma/badges/main/coverage.svg)](https://gitlab.rivercry.com/arifhasanic/enigma/-/commits/main)

## Quickstart

### Initialize git submodules

This project uses git submodules. To clone the project with all submodules run the following command:

```bash
git submodule init
git submodule update
```

### Install necessary dependencies

```bash
# arch
sudo pacman -S cjson

# debian based
sudo apt install libcjson-dev

# MacOS (homebrew), you may need to install homebrew first (https://brew.sh/)
brew install cjson
```
If you are on Mac and get and error that `cjson` try adding the homebrew library path to your `.zshrc` or `.bashrc` file:
```bash
export LDFLAGS="-L/opt/homebrew/lib"
export CPPFLAGS="-I/opt/homebrew/include"
```
It should work without this as there already is a condition in the `CMakeLists.txt` file that checks for the homebrew path.


Submodules are generally used to include other git repositories in a project. If you want to learn more about submodules you can read the [official git documentation](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

### Build the project

This project uses CMake as its build system. To build the project first make sure you have CMake installed. Then run the following commands:

```bash
mkdir build
cd build
cmake ../enigma_c
cmake --build .
```

This will create a binary called `enigma` and `enigma_test` in the `build/bin` directory. Running `enigma -h` will show you how to use the program. If you never used CMake before, an explanation of the commands is given [here](docs/CMakeLists.md).
