#include "include/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

// Error callback for GLFW
static void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
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

GLFWwindow* initializeWindow(WindowConfig config) {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
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
    GLFWwindow* window;
    if (config.fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, config.title, monitor, NULL);
    } else {
        window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
    }
    
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    // Enable vsync
    glfwSwapInterval(1);
    
    return window;
}

void setupWindowCallbacks(GLFWwindow* window) {
    // Set key callback
    glfwSetKeyCallback(window, keyCallback);
}

void terminateWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool windowShouldClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void pollWindowEvents() {
    glfwPollEvents();
}

void swapWindowBuffers(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void printOpenGLInfo() {
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    printf("GLFW Version: %s\n", glfwGetVersionString());
}

void setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void clearWindow() {
    glClear(GL_COLOR_BUFFER_BIT);
} 