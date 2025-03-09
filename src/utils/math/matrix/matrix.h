#ifndef MATRIX_H
#define MATRIX_H

// Create a 4x4 identity matrix
void matrix_identity(float* matrix);

// Create a 4x4 perspective projection matrix
void matrix_perspective(float* matrix, float fov, float aspect, float near, float far);

// Create a 4x4 rotation matrix around the X axis
void matrix_rotate_x(float* matrix, float angle);

// Create a 4x4 rotation matrix around the Y axis
void matrix_rotate_y(float* matrix, float angle);

// Create a 4x4 rotation matrix around the Z axis
void matrix_rotate_z(float* matrix, float angle);

// Create a 4x4 translation matrix
void matrix_translate(float* matrix, float x, float y, float z);

// Multiply two 4x4 matrices
void matrix_multiply(float* result, float* a, float* b);

#endif /* MATRIX_H */ 