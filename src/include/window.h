#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

// Forward declaration of GLFWwindow to avoid including GLFW in header
typedef struct GLFWwindow GLFWwindow;

// Window configuration structure
typedef struct {
    int width;
    int height;
    const char* title;
    bool fullscreen;
    int glMajorVersion;
    int glMinorVersion;
} WindowConfig;

// Default window configuration
WindowConfig defaultWindowConfig();

// Initialize GLFW and create a window
GLFWwindow* initializeWindow(WindowConfig config);

// Set up callbacks for the window
void setupWindowCallbacks(GLFWwindow* window);

// Clean up and terminate GLFW
void terminateWindow(GLFWwindow* window);

// Check if the window should close
bool windowShouldClose(GLFWwindow* window);

// Process window events
void pollWindowEvents();

// Swap the window buffers
void swapWindowBuffers(GLFWwindow* window);

// Print OpenGL information
void printOpenGLInfo();

// Set the clear color for the window
void setClearColor(float r, float g, float b, float a);

// Clear the window
void clearWindow();

#endif /* WINDOW_H */ 