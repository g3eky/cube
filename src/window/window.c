#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

// Define the actual window implementation structure
struct WindowImpl {
    GLFWwindow* glfw_window;
};

// Error callback for GLFW
static void error_callback(int error, const char* description) {
    fprintf(stderr, "Window System Error %d: %s\n", error, description);
}

// Key callback for GLFW
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// Framebuffer size callback
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

WindowConfig window_config_default(void) {
    WindowConfig config;
    config.width = 800;
    config.height = 600;
    config.title = "Cube";
    config.fullscreen = false;
    config.gl_major_version = 3;
    config.gl_minor_version = 3;
    return config;
}

Window window_init(WindowConfig config) {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize window system\n");
        return NULL;
    }
    
    // Set error callback
    glfwSetErrorCallback(error_callback);
    
    // Set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.gl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.gl_minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    // Create a window
    GLFWwindow* glfw_window;
    if (config.fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfw_window = glfwCreateWindow(mode->width, mode->height, config.title, monitor, NULL);
    } else {
        glfw_window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    }
    
    if (!glfw_window) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return NULL;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(glfw_window);
    
    // Set framebuffer size callback
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
    
    // Enable vsync
    glfwSwapInterval(1);
    
    // Initialize viewport
    glViewport(0, 0, config.width, config.height);
    
    // Create and return our window handle
    Window handle = (Window)malloc(sizeof(struct WindowImpl));
    if (!handle) {
        fprintf(stderr, "Failed to allocate window handle\n");
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
        return NULL;
    }
    
    handle->glfw_window = glfw_window;
    return handle;
}

void window_setup_callbacks(Window window) {
    if (!window) return;
    
    // Set key callback
    glfwSetKeyCallback(window->glfw_window, key_callback);
}

void window_terminate(Window window) {
    if (!window) return;
    
    glfwDestroyWindow(window->glfw_window);
    glfwTerminate();
    
    // Free our handle
    free(window);
}

bool window_should_close(Window window) {
    if (!window) return true;
    
    return glfwWindowShouldClose(window->glfw_window);
}

void window_poll_events(void) {
    glfwPollEvents();
}

void window_swap_buffers(Window window) {
    if (!window) return;
    
    glfwSwapBuffers(window->glfw_window);
}

void window_print_gl_info(void) {
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Window System Version: %s\n", glfwGetVersionString());
}

void window_set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void window_clear(void) {
    glClear(GL_COLOR_BUFFER_BIT);
} 