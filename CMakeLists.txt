cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Cube)

# Silence OpenGL deprecation warnings on macOS
if(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Find GLFW package
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
    )
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
endif()

# Include OpenGL headers
include_directories(${OPENGL_INCLUDE_DIR})

# Add the executable
add_executable(cube src/main.c)

# Link against OpenGL and GLFW libraries
target_link_libraries(cube ${OPENGL_LIBRARIES} glfw) 