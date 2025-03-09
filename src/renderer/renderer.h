#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

// Renderer configuration structure
typedef struct {
    float clear_color_r;
    float clear_color_g;
    float clear_color_b;
    float clear_color_a;
    float rotation_speed; // Rotation speed in radians per second
} renderer_config_t;

// Window configuration structure
typedef struct {
    int width;
    int height;
    const char* title;
    bool fullscreen;
    int gl_major_version;
    int gl_minor_version;
} renderer_window_config_t;

// Default renderer configuration
renderer_config_t renderer_config_default(void);

// Default window configuration
renderer_window_config_t renderer_window_config_default(void);

// Initialize the renderer with window
bool renderer_init_with_window(renderer_config_t renderer_config, renderer_window_config_t window_config);

// Create the cube geometry
void renderer_create_cube(void);

// Render a single frame
void renderer_render_frame(void);

// Run the main render loop
void renderer_run_main_loop(void);

// Clean up renderer and window resources
void renderer_terminate(void);

#endif /* RENDERER_H */ 