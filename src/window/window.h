#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

// Forward declaration of the window handle type
// This hides the implementation detail that we're using GLFW
typedef struct WindowImpl* Window;

// Window configuration structure
typedef struct {
    int width;
    int height;
    const char* title;
    bool fullscreen;
    int gl_major_version;
    int gl_minor_version;
} WindowConfig;

// Default window configuration
WindowConfig window_config_default(void);

// Initialize and create a window
Window window_init(WindowConfig config);

// Set up callbacks for the window
void window_setup_callbacks(Window window);

// Clean up and terminate window system
void window_terminate(Window window);

// Check if the window should close
bool window_should_close(Window window);

// Process window events
void window_poll_events(void);

// Swap the window buffers
void window_swap_buffers(Window window);

// Print OpenGL information
void window_print_gl_info(void);

// Set the clear color for the window
void window_set_clear_color(float r, float g, float b, float a);

// Clear the window
void window_clear(void);

#endif /* WINDOW_H */ 