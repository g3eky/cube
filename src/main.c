#include <stdio.h>
#include <stdlib.h>
#include "renderer/renderer.h"

int main() {
    printf("Hello from Cube!\n");
    
    // Create default configurations
    RendererConfig rendererConfig = defaultRendererConfig();
    WindowConfig windowConfig = defaultWindowConfig();
    
    // Initialize renderer with window
    if (!initializeRendererWithWindow(rendererConfig, windowConfig)) {
        return EXIT_FAILURE;
    }
    
    // Run the main loop
    runMainLoop();
    
    // Clean up
    terminateRendererAndWindow();
    
    printf("Exiting Cube application\n");
    return EXIT_SUCCESS;
} 