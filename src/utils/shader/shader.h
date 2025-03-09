#ifndef SHADER_H
#define SHADER_H

// Shader program handle
typedef unsigned int ShaderProgram_t;

// Create a shader program from vertex and fragment shader source
ShaderProgram_t shader_create_program(const char* vertex_shader_source, const char* fragment_shader_source);

// Use a shader program
void shader_use_program(ShaderProgram_t program);

// Set a uniform float value in the shader
void shader_set_float(ShaderProgram_t program, const char* name, float value);

// Set a uniform 4x4 matrix in the shader
void shader_set_mat4(ShaderProgram_t program, const char* name, const float* matrix);

// Delete a shader program
void shader_delete_program(ShaderProgram_t program);

#endif /* SHADER_H */ 