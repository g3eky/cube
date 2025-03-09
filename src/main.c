#include <stdio.h>
#include <stdlib.h>
#include "include/window.h"

int main() {
    printf("Hello from Cube!\n");
    
    // Create default window configuration
    WindowConfig config = defaultWindowConfig();
    
    // Initialize window
    WindowHandle window = initializeWindow(config);
    if (!window) {
        return EXIT_FAILURE;
    }
    
    // Set up window callbacks
    setupWindowCallbacks(window);
    
    // Print OpenGL information
    printOpenGLInfo();
    
    // Main loop
    while (!windowShouldClose(window)) {
        // Clear the screen
        clearWindow();
        
        // Set the clear color (background)
        setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        // Swap front and back buffers
        swapWindowBuffers(window);
        
        // Poll for and process events
        pollWindowEvents();
    }
    
    // Clean up
    terminateWindow(window);
    
    printf("Exiting Cube application\n");
    return EXIT_SUCCESS;
} 