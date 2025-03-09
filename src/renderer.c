#include "include/renderer.h"
#include "include/window.h"
#include "include/shader.h"
#include "include/math_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Include OpenGL headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

// Global renderer configuration
static RendererConfig currentConfig;

// Shader program
static ShaderProgram shaderProgram;

// Vertex Array Object and Vertex Buffer Object
static unsigned int VAO, VBO, EBO;

// Rotation angle
static float rotationAngle = 0.0f;

// Time tracking
static double lastFrameTime = 0.0;

// Vertex shader source
static const char* vertexShaderSource = 
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
static const char* fragmentShaderSource = 
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

RendererConfig defaultRendererConfig() {
    RendererConfig config;
    config.clearColorR = 0.2f;
    config.clearColorG = 0.3f;
    config.clearColorB = 0.3f;
    config.clearColorA = 1.0f;
    config.rotationSpeed = 1.0f; // 1 radian per second
    return config;
}

void initializeRenderer(RendererConfig config) {
    // Store the configuration
    currentConfig = config;
    
    // Print OpenGL information
    printOpenGLInfo();
    
    // Create shader program
    shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    
    // Initialize time tracking
    lastFrameTime = (double)clock() / CLOCKS_PER_SEC;
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // Create the cube geometry
    createCube();
}

void createCube() {
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

void renderFrame() {
    // Calculate delta time
    double currentTime = (double)clock() / CLOCKS_PER_SEC;
    double deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    
    // Update rotation angle
    rotationAngle += currentConfig.rotationSpeed * deltaTime;
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set the clear color (background)
    glClearColor(
        currentConfig.clearColorR,
        currentConfig.clearColorG,
        currentConfig.clearColorB,
        currentConfig.clearColorA
    );
    
    // Use shader program
    useShaderProgram(shaderProgram);
    
    // Create transformation matrices
    float model[16], view[16], projection[16], rotationY[16], rotationX[16], temp[16];
    
    // Model matrix - rotate the cube
    mat4RotateY(rotationY, rotationAngle);
    mat4RotateX(rotationX, rotationAngle * 0.5f);
    mat4Multiply(model, rotationY, rotationX);
    
    // View matrix - move the camera back a bit
    mat4Translate(view, 0.0f, 0.0f, -3.0f);
    
    // Projection matrix
    mat4Perspective(projection, 45.0f * (3.14159f / 180.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    // Set uniforms
    setShaderMatrix4(shaderProgram, "model", model);
    setShaderMatrix4(shaderProgram, "view", view);
    setShaderMatrix4(shaderProgram, "projection", projection);
    
    // Draw the cube
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void runRenderLoop(WindowHandle window) {
    // Main loop
    while (!windowShouldClose(window)) {
        // Render a frame
        renderFrame();
        
        // Swap front and back buffers
        swapWindowBuffers(window);
        
        // Poll for and process events
        pollWindowEvents();
    }
}

void terminateRenderer() {
    // Clean up renderer resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    deleteShaderProgram(shaderProgram);
} 