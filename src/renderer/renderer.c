#include "renderer.h"
#include "../window/window.h"
#include "../utils/shader/shader.h"
#include "../utils/math/math.h"
#include "../utils/objects/cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GLFW/glfw3.h>

// Include OpenGL headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

// Global renderer configuration
static RendererConfig current_config;

// Window handle
static Window window = NULL;

// Shader program
static ShaderProgram shader_program;

// Cube object
static Cube* cube = NULL;

// Time tracking
static double last_frame_time = 0.0;

// Vertex shader source
static const char* vertex_shader_source = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "   vertexColor = aColor;\n"
    "}\0";

// Fragment shader source
static const char* fragment_shader_source = 
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0);\n"
    "}\0";

RendererConfig renderer_config_default(void) {
    RendererConfig config;
    config.clear_color_r = 0.2f;
    config.clear_color_g = 0.3f;
    config.clear_color_b = 0.3f;
    config.clear_color_a = 1.0f;
    config.rotation_speed = 1.0f; // 1 radian per second
    return config;
}

RendererWindowConfig renderer_window_config_default(void) {
    RendererWindowConfig config;
    config.width = 800;
    config.height = 600;
    config.title = "Cube";
    config.fullscreen = false;
    config.gl_major_version = 3;
    config.gl_minor_version = 3;
    return config;
}

bool renderer_init_with_window(RendererConfig renderer_config, RendererWindowConfig window_config) {
    // Store the renderer configuration
    current_config = renderer_config;
    
    // Convert our WindowConfig to the window module's format
    WindowConfig win_config;
    win_config.width = window_config.width;
    win_config.height = window_config.height;
    win_config.title = window_config.title;
    win_config.fullscreen = window_config.fullscreen;
    win_config.gl_major_version = window_config.gl_major_version;
    win_config.gl_minor_version = window_config.gl_minor_version;
    
    // Initialize window
    window = window_init(win_config);
    if (!window) {
        return false;
    }
    
    // Set up window callbacks
    window_setup_callbacks(window);
    
    // Print OpenGL information
    window_print_gl_info();
    
    // Create shader program
    shader_program = shader_create_program(vertex_shader_source, fragment_shader_source);
    
    // Initialize time tracking
    last_frame_time = glfwGetTime();
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // Create the cube
    cube = cube_create();
    if (!cube) {
        fprintf(stderr, "Failed to create cube\n");
        return false;
    }
    
    return true;
}

void renderer_render_frame(void) {
    // Calculate delta time
    double current_time = glfwGetTime();
    double delta_time = current_time - last_frame_time;
    last_frame_time = current_time;
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set the clear color (background)
    glClearColor(
        current_config.clear_color_r,
        current_config.clear_color_g,
        current_config.clear_color_b,
        current_config.clear_color_a
    );
    
    // Use shader program
    shader_use_program(shader_program);
    
    // Create view and projection matrices
    float view[16], projection[16];
    
    // View matrix - use look_at to position the camera
    // Position the camera at (0, 0, 4) looking at the origin (0, 0, 0) with up vector (0, 1, 0)
    matrix_look_at(view, 
                  0.0f, 0.0f, 4.0f,   // Eye position
                  0.0f, 0.0f, 0.0f,   // Look at point (center of the scene)
                  0.0f, 1.0f, 0.0f);  // Up vector
    
    // Get window size for aspect ratio
    int width, height;
    GLFWwindow* glfw_window = window_get_glfw_window(window);
    glfwGetFramebufferSize(glfw_window, &width, &height);
    float aspect_ratio = (float)width / (float)height;
    
    // Projection matrix - perspective projection
    matrix_perspective(projection, 45.0f * (3.14159f / 180.0f), aspect_ratio, 0.1f, 100.0f);
    
    // Set view and projection uniforms
    shader_set_mat4(shader_program, "view", view);
    shader_set_mat4(shader_program, "projection", projection);
    
    // Render the cube
    cube_render(cube, shader_program, (float)delta_time, current_config.rotation_speed);
}

void renderer_run_main_loop(void) {
    if (!window) {
        fprintf(stderr, "Cannot run main loop: window not initialized\n");
        return;
    }
    
    // Main loop
    while (!window_should_close(window)) {
        // Render a frame
        renderer_render_frame();
        
        // Swap front and back buffers
        window_swap_buffers(window);
        
        // Poll for and process events
        window_poll_events();
    }
}

void renderer_terminate(void) {
    // Clean up cube
    if (cube) {
        cube_destroy(cube);
        cube = NULL;
    }
    
    // Clean up shader
    shader_delete_program(shader_program);
    
    // Clean up window
    if (window) {
        window_terminate(window);
        window = NULL;
    }
} 