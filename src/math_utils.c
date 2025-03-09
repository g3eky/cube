#include "include/math_utils.h"
#include <math.h>
#include <string.h>

void mat4Identity(float* matrix) {
    // Initialize to zero
    memset(matrix, 0, 16 * sizeof(float));
    
    // Set diagonal to 1
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

void mat4Perspective(float* matrix, float fov, float aspect, float near, float far) {
    // Initialize to zero
    memset(matrix, 0, 16 * sizeof(float));
    
    float tanHalfFov = tanf(fov / 2.0f);
    
    matrix[0] = 1.0f / (aspect * tanHalfFov);
    matrix[5] = 1.0f / tanHalfFov;
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -1.0f;
    matrix[14] = -(2.0f * far * near) / (far - near);
}

void mat4RotateX(float* matrix, float angle) {
    // Initialize to identity
    mat4Identity(matrix);
    
    float c = cosf(angle);
    float s = sinf(angle);
    
    matrix[5] = c;
    matrix[6] = s;
    matrix[9] = -s;
    matrix[10] = c;
}

void mat4RotateY(float* matrix, float angle) {
    // Initialize to identity
    mat4Identity(matrix);
    
    float c = cosf(angle);
    float s = sinf(angle);
    
    matrix[0] = c;
    matrix[2] = -s;
    matrix[8] = s;
    matrix[10] = c;
}

void mat4RotateZ(float* matrix, float angle) {
    // Initialize to identity
    mat4Identity(matrix);
    
    float c = cosf(angle);
    float s = sinf(angle);
    
    matrix[0] = c;
    matrix[1] = s;
    matrix[4] = -s;
    matrix[5] = c;
}

void mat4Translate(float* matrix, float x, float y, float z) {
    // Initialize to identity
    mat4Identity(matrix);
    
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void mat4Multiply(float* result, float* a, float* b) {
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