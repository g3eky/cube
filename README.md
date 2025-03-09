# Cube C Program with CMake

A simple C program built using CMake with OpenGL support.

## Project Structure

```
.
├── .gitignore        # Git ignore file
├── CMakeLists.txt    # CMake configuration file
├── README.md         # This file
└── src/              # Source code directory
    └── main.c        # Main C program
```

## Prerequisites

- C compiler (gcc, clang, etc.)
- CMake (version 3.10 or higher)
- OpenGL development libraries

### Installing OpenGL Dependencies

#### On Ubuntu/Debian:
```
sudo apt-get install libgl1-mesa-dev
```

#### On macOS:
OpenGL is included with the system.

#### On Windows:
OpenGL libraries are typically included with graphics drivers. You may also need:
```
vcpkg install opengl
```

## Building the Project

1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Generate the build files:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   cmake --build .
   ```

## Running the Program

After building, you can run the program from the build directory:

```
./cube
```

You should see the output:
```
Hello from Cube!
```

## Version Control

This project uses Git for version control. If you want to clone this repository:

```
git clone <repository-url>
```

To make changes and commit them:

```
git add .
git commit -m "Your commit message"
```