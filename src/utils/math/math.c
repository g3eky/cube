#include "math.h"
#include <math.h>
#include <string.h>

void math_mat4_identity(float* matrix) {
    // Initialize to zero
    memset(matrix, 0, 16 * sizeof(float));
    
    // Set diagonal to 1
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

void math_mat4_perspective(float* matrix, float fov, float aspect, float near, float far) {
    // Initialize to zero
    memset(matrix, 0, 16 * sizeof(float));
    
    float tan_half_fov = tanf(fov / 2.0f);
    float f = 1.0f / tan_half_fov;
    
    matrix[0] = f / aspect;
    matrix[5] = f;
    matrix[10] = (far + near) / (near - far);
    matrix[11] = -1.0f;
    matrix[14] = (2.0f * far * near) / (near - far);
}

void math_mat4_rotate_x(float* matrix, float angle) {
    // Initialize to identity
    math_mat4_identity(matrix);
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    
    matrix[5] = cos_angle;
    matrix[6] = sin_angle;
    matrix[9] = -sin_angle;
    matrix[10] = cos_angle;
}

void math_mat4_rotate_y(float* matrix, float angle) {
    // Initialize to identity
    math_mat4_identity(matrix);
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    
    matrix[0] = cos_angle;
    matrix[2] = -sin_angle;
    matrix[8] = sin_angle;
    matrix[10] = cos_angle;
}

void math_mat4_rotate_z(float* matrix, float angle) {
    // Initialize to identity
    math_mat4_identity(matrix);
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    
    matrix[0] = cos_angle;
    matrix[1] = sin_angle;
    matrix[4] = -sin_angle;
    matrix[5] = cos_angle;
}

void math_mat4_translate(float* matrix, float x, float y, float z) {
    // Initialize to identity
    math_mat4_identity(matrix);
    
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void math_mat4_multiply(float* result, float* a, float* b) {
    float temp[16];
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i * 4 + j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                temp[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
            }
        }
    }
    
    // Copy the result
    memcpy(result, temp, 16 * sizeof(float));
} 