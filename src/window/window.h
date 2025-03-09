#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

// Forward declaration of the window handle type
// This hides the implementation detail that we're using GLFW
typedef struct WindowHandle* WindowHandle;

// Window configuration structure
typedef struct WindowConfig_Window {
    int width;
    int height;
    const char* title;
    bool fullscreen;
    int glMajorVersion;
    int glMinorVersion;
} WindowConfig_Window;

// Default window configuration
WindowConfig_Window defaultWindowConfig_Window();

// Initialize and create a window
WindowHandle initializeWindow(WindowConfig_Window config);

// Set up callbacks for the window
void setupWindowCallbacks(WindowHandle window);

// Clean up and terminate window system
void terminateWindow(WindowHandle window);

// Check if the window should close
bool windowShouldClose(WindowHandle window);

// Process window events
void pollWindowEvents();

// Swap the window buffers
void swapWindowBuffers(WindowHandle window);

// Print OpenGL information
void printOpenGLInfo();

// Set the clear color for the window
void setClearColor(float r, float g, float b, float a);

// Clear the window
void clearWindow();

#endif /* WINDOW_H */ 