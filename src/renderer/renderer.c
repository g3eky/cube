#include "renderer.h"
#include "../window/window.h"
#include "../utils/shader/shader.h"
#include "../utils/math/math.h"
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

// Vertex Array Object and Vertex Buffer Object
static unsigned int VAO, VBO, EBO;

// Rotation angle
static double rotation_angle = 0.0;

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

// Cube vertices (position and color)
static float vertices[] = {
    // positions          // colors
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.5f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 1.0f
};

// Cube indices
static unsigned int indices[] = {
    0, 1, 2, 2, 3, 0, // Front face
    1, 5, 6, 6, 2, 1, // Right face
    5, 4, 7, 7, 6, 5, // Back face
    4, 0, 3, 3, 7, 4, // Left face
    3, 2, 6, 6, 7, 3, // Top face
    4, 5, 1, 1, 0, 4  // Bottom face
};

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
    
    // Create the cube geometry
    renderer_create_cube();
    
    return true;
}

void renderer_create_cube(void) {
    // Generate and bind Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Generate and bind Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Generate and bind Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderer_render_frame(void) {
    // Calculate delta time
    double current_time = glfwGetTime();
    double delta_time = current_time - last_frame_time;
    last_frame_time = current_time;
    
    // Update rotation angle
    rotation_angle += current_config.rotation_speed * delta_time;
    
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
    
    // Create transformation matrices
    float model[16], view[16], projection[16], rotation_y[16], rotation_x[16], temp[16];
    
    // Model matrix - rotate the cube
    matrix_rotate_y(rotation_y, rotation_angle);
    matrix_rotate_x(rotation_x, rotation_angle * 0.5f);
    matrix_multiply(model, rotation_y, rotation_x);
    
    // View matrix - move the camera back
    matrix_translate(view, 0.0f, 0.0f, -3.0f);
    
    // Get window size for aspect ratio
    int width, height;
    GLFWwindow* glfw_window = window_get_glfw_window(window);
    glfwGetFramebufferSize(glfw_window, &width, &height);
    float aspect_ratio = (float)width / (float)height;
    
    // Projection matrix - perspective projection
    matrix_perspective(projection, 45.0f * (3.14159f / 180.0f), aspect_ratio, 0.1f, 100.0f);
    
    // Set uniforms
    shader_set_mat4(shader_program, "model", model);
    shader_set_mat4(shader_program, "view", view);
    shader_set_mat4(shader_program, "projection", projection);
    
    // Draw the cube
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
    // Clean up renderer resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader_delete_program(shader_program);
    
    // Clean up window
    if (window) {
        window_terminate(window);
        window = NULL;
    }
} 