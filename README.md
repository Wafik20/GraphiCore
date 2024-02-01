# GraphiCore
GraphiCore is a fun experiment aimed at developing a basic graphics library solely using POSIX functions, avoiding any standard C library dependencies. The project is an exploration into low-level graphics programming, emphasizing simplicity and direct hardware interaction.

## Files

- `library.c`: Contains the core implementations of the graphics functions.
- `library.h`: The header file for the library, declaring the functions and any necessary data structures.
- `iso_font.h`: Apple's bit font map. 
- `driver.c`: A test program demonstrating the capabilities of the library.

## Getting Started

### Prerequisites

Ensure you have a POSIX-compliant environment to compile and run this project. Tools like GCC (GNU Compiler Collection) for compilation and Make (optional) for automating the build process are recommended.

### Building the Project

1. Compile the library and driver files. If using GCC, the commands might look like this:

   ```bash
   gcc -c library.c -o library.o
   gcc driver.c library.o -o driver

2. This will create an executable named `driver`.

### Running the Project

Execute the `driver` program in your terminal:
This will run the demonstration defined in `driver.c`, utilizing the graphics functions implemented in `library.c`.

## Sample Driver Output
![Sample GraphiCore Output](https://github.com/Wafik20/GraphiCore/blob/master/sample_run1.png)
![Sample GraphiCore Output](https://github.com/Wafik20/GraphiCore/blob/master/sample_run2.png)
