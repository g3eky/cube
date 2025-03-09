#ifndef SHADER_H
#define SHADER_H

// Shader program handle
typedef unsigned int ShaderProgram;

// Create a shader program from vertex and fragment shader source
ShaderProgram shader_create_program(const char* vertex_shader_source, const char* fragment_shader_source);

// Use a shader program
void shader_use_program(ShaderProgram program);

// Set a uniform float value in the shader
void shader_set_float(ShaderProgram program, const char* name, float value);

// Set a uniform 4x4 matrix in the shader
void shader_set_mat4(ShaderProgram program, const char* name, const float* matrix);

// Delete a shader program
void shader_delete_program(ShaderProgram program);

#endif /* SHADER_H */ 