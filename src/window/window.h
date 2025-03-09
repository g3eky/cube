#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

// Forward declaration of the window handle type
// This hides the implementation detail that we're using GLFW
typedef struct WindowHandle* window_handle_t;

// Window configuration structure
typedef struct {
    int width;
    int height;
    const char* title;
    bool fullscreen;
    int gl_major_version;
    int gl_minor_version;
} window_config_t;

// Default window configuration
window_config_t window_config_default(void);

// Initialize and create a window
window_handle_t window_init(window_config_t config);

// Set up callbacks for the window
void window_setup_callbacks(window_handle_t window);

// Clean up and terminate window system
void window_terminate(window_handle_t window);

// Check if the window should close
bool window_should_close(window_handle_t window);

// Process window events
void window_poll_events(void);

// Swap the window buffers
void window_swap_buffers(window_handle_t window);

// Print OpenGL information
void window_print_gl_info(void);

// Set the clear color for the window
void window_set_clear_color(float r, float g, float b, float a);

// Clear the window
void window_clear(void);

#endif /* WINDOW_H */ 