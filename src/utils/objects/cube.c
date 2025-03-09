#include "cube.h"
#include "../shader/shader.h"
#include "../math/math.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

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

Cube* cube_create(void) {
    Cube* cube = (Cube*)malloc(sizeof(Cube));
    if (!cube) {
        return NULL;
    }
    
    // Initialize rotation angle
    cube->rotation_angle = 0.0f;
    
    // Generate and bind Vertex Array Object
    glGenVertexArrays(1, &cube->vao);
    glBindVertexArray(cube->vao);
    
    // Generate and bind Vertex Buffer Object
    glGenBuffers(1, &cube->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cube->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Generate and bind Element Buffer Object
    glGenBuffers(1, &cube->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube->ebo);
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
    
    return cube;
}

void cube_render(Cube* cube, ShaderProgram shader_program, float delta_time, float rotation_speed) {
    if (!cube) return;
    
    // Update rotation angle
    cube->rotation_angle += rotation_speed * delta_time;
    
    // Create transformation matrices
    float model[16], rotation_y[16], rotation_x[16];
    
    // Model matrix - rotate the cube
    matrix_rotate_y(rotation_y, cube->rotation_angle);
    matrix_rotate_x(rotation_x, cube->rotation_angle * 0.5f);
    matrix_multiply(model, rotation_y, rotation_x);
    
    // Set model uniform
    shader_set_mat4(shader_program, "model", model);
    
    // Draw the cube
    glBindVertexArray(cube->vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void cube_destroy(Cube* cube) {
    if (!cube) return;
    
    // Delete buffers and vertex array
    glDeleteVertexArrays(1, &cube->vao);
    glDeleteBuffers(1, &cube->vbo);
    glDeleteBuffers(1, &cube->ebo);
    
    // Free the cube object
    free(cube);
} 