#include "include/shader.h"
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
static void checkShaderErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    
    if (strcmp(type, "PROGRAM") == 0) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", type, infoLog);
        }
    }
}

ShaderProgram createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    // Create vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderErrors(vertexShader, "VERTEX");
    
    // Create fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderErrors(fragmentShader, "FRAGMENT");
    
    // Create shader program
    ShaderProgram program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkShaderErrors(program, "PROGRAM");
    
    // Delete shaders as they're linked into the program now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}

void useShaderProgram(ShaderProgram program) {
    glUseProgram(program);
}

void setShaderFloat(ShaderProgram program, const char* name, float value) {
    glUniform1f(glGetUniformLocation(program, name), value);
}

void setShaderMatrix4(ShaderProgram program, const char* name, const float* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, matrix);
}

void deleteShaderProgram(ShaderProgram program) {
    glDeleteProgram(program);
} 