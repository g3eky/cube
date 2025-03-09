# Cube C Program with CMake

A simple C program built using CMake with OpenGL and GLFW support. This program creates a window and initializes OpenGL.

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
- GLFW (automatically downloaded if not found)

### Installing OpenGL Dependencies

#### On Ubuntu/Debian:
```
sudo apt-get install libgl1-mesa-dev libglfw3-dev
```

#### On macOS:
OpenGL is included with the system. GLFW can be installed via Homebrew:
```
brew install glfw
```

#### On Windows:
OpenGL libraries are typically included with graphics drivers. GLFW can be installed via vcpkg:
```
vcpkg install glfw3
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

This will open a window with a teal background. Press ESC to close the window.

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