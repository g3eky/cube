#ifndef CUBE_H
#define CUBE_H

#include <stdbool.h>

// Forward declaration for shader program
typedef unsigned int ShaderProgram;

// Cube object structure
typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    float rotation_angle;
} Cube;

// Create a new cube
Cube* cube_create(void);

// Render the cube with the given shader program
void cube_render(Cube* cube, ShaderProgram shader_program, float delta_time, float rotation_speed);

// Destroy the cube and free resources
void cube_destroy(Cube* cube);

#endif /* CUBE_H */ 