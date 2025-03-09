#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Create a 4x4 identity matrix
void mat4Identity(float* matrix);

// Create a 4x4 perspective projection matrix
void mat4Perspective(float* matrix, float fov, float aspect, float near, float far);

// Create a 4x4 rotation matrix around the X axis
void mat4RotateX(float* matrix, float angle);

// Create a 4x4 rotation matrix around the Y axis
void mat4RotateY(float* matrix, float angle);

// Create a 4x4 rotation matrix around the Z axis
void mat4RotateZ(float* matrix, float angle);

// Create a 4x4 translation matrix
void mat4Translate(float* matrix, float x, float y, float z);

// Multiply two 4x4 matrices
void mat4Multiply(float* result, float* a, float* b);

#endif /* MATH_UTILS_H */ 