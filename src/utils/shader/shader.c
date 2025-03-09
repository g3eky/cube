#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include OpenGL headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

// Helper function to check shader compilation/linking errors
static void check_shader_errors(unsigned int shader, const char* type) {
    int success;
    char info_log[1024];
    
    if (strcmp(type, "PROGRAM") == 0) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);
            fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);
            fprintf(stderr, "ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", type, info_log);
        }
    }
}

ShaderProgram_t shader_create_program(const char* vertex_shader_source, const char* fragment_shader_source) {
    // Create vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    check_shader_errors(vertex_shader, "VERTEX");
    
    // Create fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    check_shader_errors(fragment_shader, "FRAGMENT");
    
    // Create shader program
    ShaderProgram_t program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    check_shader_errors(program, "PROGRAM");
    
    // Delete shaders as they're linked into the program now
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return program;
}

void shader_use_program(ShaderProgram_t program) {
    glUseProgram(program);
}

void shader_set_float(ShaderProgram_t program, const char* name, float value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

void shader_set_mat4(ShaderProgram_t program, const char* name, const float* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, matrix);
}

void shader_delete_program(ShaderProgram_t program) {
    glDeleteProgram(program);
} 