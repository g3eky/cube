cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Cube)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Include OpenGL headers
include_directories(${OPENGL_INCLUDE_DIR})

# Add the executable
add_executable(cube src/main.c)

# Link against OpenGL libraries
target_link_libraries(cube ${OPENGL_LIBRARIES}) 