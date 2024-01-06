# CMakeLists
## Why CMakelists?
At the beginning I tried to only use a singel Makefile. The handling became very clunky,
especially after trying to create a test suite. I decided to use CMake because it is fairly
popular so if someone wants to contribute they will probably know how to use it or at least
they will be able to learn a industry standard tool. This project should be designed to be 
easy to contribute to. The setup of CMake is a bit more complicated but after that it is
very easy to add new files to the project.

## Project Structure
The project is structured into 3 main directories:
- `src`: Contains all the source files
- `tests`: Contains all the test files
- `./`: Contains the root CMakeLists.txt files

### CMakeLists.txt (src)
The src CMakeLists.txt file is responsible for compiling the projects source files. 
The src CMakelists.txt file only compiles the files into an library. The library is then
linked to the main.c file in the root CMakeLists.txt file. The reason for this is that
every C programm is only allowed to have one main function.
The tests have their own main function so linking them together would result in an error.
Libraries are typically 'normal' C programs without a main function. This also means they 
can't be executed on their own. The main function is then defined in the root CMakeLists.txt
file. 
Try to keep the main.c file as small as possible. All the logic should be in other files.
This allows us to test the logic without having to test the main function.

### CMakeLists.txt (tests)


### CMakeLists.txt (root)
The root CMakeLists.txt file is responsible for setting up the project and linking the
subdirectories. The `src` and `tests` directories each have their own CMakeLists.txt file
which are responsible for compiling the files in their respective directories. 
