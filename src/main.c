#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main() {
    printf("Hello from Cube!\n");
    
    // Note: To properly use OpenGL, we need to create a window and OpenGL context
    // For now, we'll just indicate that OpenGL is available but not initialized
    printf("OpenGL is available but not initialized in this simple example.\n");
    printf("To use OpenGL properly, we would need to create a window and context using GLFW or similar.\n");
    
    return 0;
} 