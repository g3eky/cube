#include "matrix.h"
#include <math.h>
#include <string.h>

void matrix_identity(float* matrix) {
    // Initialize to zero
    memset(matrix, 0, 16 * sizeof(float));
    
    // Set diagonal to 1
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

void matrix_perspective(float* matrix, float fov, float aspect, float near, float far) {
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

void matrix_rotate_x(float* matrix, float angle) {
    // Initialize to identity
    matrix_identity(matrix);
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    
    matrix[5] = cos_angle;
    matrix[6] = sin_angle;
    matrix[9] = -sin_angle;
    matrix[10] = cos_angle;
}

void matrix_rotate_y(float* matrix, float angle) {
    // Initialize to identity
    matrix_identity(matrix);
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    
    matrix[0] = cos_angle;
    matrix[2] = -sin_angle;
    matrix[8] = sin_angle;
    matrix[10] = cos_angle;
}

void matrix_rotate_z(float* matrix, float angle) {
    // Initialize to identity
    matrix_identity(matrix);
    
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);
    
    matrix[0] = cos_angle;
    matrix[1] = sin_angle;
    matrix[4] = -sin_angle;
    matrix[5] = cos_angle;
}

void matrix_translate(float* matrix, float x, float y, float z) {
    // Initialize to identity
    matrix_identity(matrix);
    
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

void matrix_look_at(float* matrix, 
                   float eye_x, float eye_y, float eye_z,
                   float center_x, float center_y, float center_z,
                   float up_x, float up_y, float up_z) {
    // Calculate forward vector (normalized)
    float forward_x = center_x - eye_x;
    float forward_y = center_y - eye_y;
    float forward_z = center_z - eye_z;
    
    // Normalize forward vector
    float length = sqrtf(forward_x * forward_x + forward_y * forward_y + forward_z * forward_z);
    if (length > 0.0f) {
        forward_x /= length;
        forward_y /= length;
        forward_z /= length;
    }
    
    // Calculate right vector (normalized)
    float right_x = forward_y * up_z - forward_z * up_y;
    float right_y = forward_z * up_x - forward_x * up_z;
    float right_z = forward_x * up_y - forward_y * up_x;
    
    // Normalize right vector
    length = sqrtf(right_x * right_x + right_y * right_y + right_z * right_z);
    if (length > 0.0f) {
        right_x /= length;
        right_y /= length;
        right_z /= length;
    }
    
    // Calculate up vector (normalized)
    float up2_x = right_y * forward_z - right_z * forward_y;
    float up2_y = right_z * forward_x - right_x * forward_z;
    float up2_z = right_x * forward_y - right_y * forward_x;
    
    // Set up the view matrix
    matrix[0] = right_x;
    matrix[1] = up2_x;
    matrix[2] = -forward_x;
    matrix[3] = 0.0f;
    
    matrix[4] = right_y;
    matrix[5] = up2_y;
    matrix[6] = -forward_y;
    matrix[7] = 0.0f;
    
    matrix[8] = right_z;
    matrix[9] = up2_z;
    matrix[10] = -forward_z;
    matrix[11] = 0.0f;
    
    matrix[12] = -(right_x * eye_x + right_y * eye_y + right_z * eye_z);
    matrix[13] = -(up2_x * eye_x + up2_y * eye_y + up2_z * eye_z);
    matrix[14] = forward_x * eye_x + forward_y * eye_y + forward_z * eye_z;
    matrix[15] = 1.0f;
}

void matrix_multiply(float* result, float* a, float* b) {
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