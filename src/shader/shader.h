#ifndef SHADER_H
#define SHADER_H

// Shader program handle
typedef unsigned int ShaderProgram;

// Create a shader program from vertex and fragment shader source
ShaderProgram createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

// Use a shader program
void useShaderProgram(ShaderProgram program);

// Set a uniform float value in the shader
void setShaderFloat(ShaderProgram program, const char* name, float value);

// Set a uniform 4x4 matrix in the shader
void setShaderMatrix4(ShaderProgram program, const char* name, const float* matrix);

// Delete a shader program
void deleteShaderProgram(ShaderProgram program);

#endif /* SHADER_H */ 