#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main() {
    printf("Hello from Cube!\n");
    
    // Print OpenGL information
    const char* version = (const char*)glGetString(GL_VERSION);
    if (version) {
        printf("OpenGL Version: %s\n", version);
    } else {
        printf("OpenGL not initialized properly.\n");
    }
    
    return 0;
} 