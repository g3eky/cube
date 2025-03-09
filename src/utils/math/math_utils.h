#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Create a 4x4 identity matrix
void math_mat4_identity(float* matrix);

// Create a 4x4 perspective projection matrix
void math_mat4_perspective(float* matrix, float fov, float aspect, float near, float far);

// Create a 4x4 rotation matrix around the X axis
void math_mat4_rotate_x(float* matrix, float angle);

// Create a 4x4 rotation matrix around the Y axis
void math_mat4_rotate_y(float* matrix, float angle);

// Create a 4x4 rotation matrix around the Z axis
void math_mat4_rotate_z(float* matrix, float angle);

// Create a 4x4 translation matrix
void math_mat4_translate(float* matrix, float x, float y, float z);

// Multiply two 4x4 matrices
void math_mat4_multiply(float* result, float* a, float* b);

#endif /* MATH_UTILS_H */ 