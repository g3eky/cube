#include "include/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

// Define the actual window handle structure
struct WindowHandle {
    GLFWwindow* glfwWindow;
};

// Error callback for GLFW
static void errorCallback(int error, const char* description) {
    fprintf(stderr, "Window System Error %d: %s\n", error, description);
}

// Key callback for GLFW
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

WindowConfig defaultWindowConfig() {
    WindowConfig config;
    config.width = 800;
    config.height = 600;
    config.title = "Cube";
    config.fullscreen = false;
    config.glMajorVersion = 3;
    config.glMinorVersion = 3;
    return config;
}

WindowHandle initializeWindow(WindowConfig config) {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize window system\n");
        return NULL;
    }
    
    // Set error callback
    glfwSetErrorCallback(errorCallback);
    
    // Set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.glMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    // Create a window
    GLFWwindow* glfwWindow;
    if (config.fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindow = glfwCreateWindow(mode->width, mode->height, config.title, monitor, NULL);
    } else {
        glfwWindow = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    }
    
    if (!glfwWindow) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return NULL;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(glfwWindow);
    
    // Enable vsync
    glfwSwapInterval(1);
    
    // Create and return our window handle
    WindowHandle handle = (WindowHandle)malloc(sizeof(struct WindowHandle));
    if (!handle) {
        fprintf(stderr, "Failed to allocate window handle\n");
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
        return NULL;
    }
    
    handle->glfwWindow = glfwWindow;
    return handle;
}

void setupWindowCallbacks(WindowHandle window) {
    if (!window) return;
    
    // Set key callback
    glfwSetKeyCallback(window->glfwWindow, keyCallback);
}

void terminateWindow(WindowHandle window) {
    if (!window) return;
    
    glfwDestroyWindow(window->glfwWindow);
    glfwTerminate();
    
    // Free our handle
    free(window);
}

bool windowShouldClose(WindowHandle window) {
    if (!window) return true;
    
    return glfwWindowShouldClose(window->glfwWindow);
}

void pollWindowEvents() {
    glfwPollEvents();
}

void swapWindowBuffers(WindowHandle window) {
    if (!window) return;
    
    glfwSwapBuffers(window->glfwWindow);
}

void printOpenGLInfo() {
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Window System Version: %s\n", glfwGetVersionString());
}

void setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void clearWindow() {
    glClear(GL_COLOR_BUFFER_BIT);
} 