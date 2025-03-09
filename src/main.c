#include <stdio.h>
#include <stdlib.h>
#include "include/window.h"
#include "include/renderer.h"

int main() {
    printf("Hello from Cube!\n");
    
    // Create default window configuration
    WindowConfig windowConfig = defaultWindowConfig();
    
    // Initialize window
    WindowHandle window = initializeWindow(windowConfig);
    if (!window) {
        return EXIT_FAILURE;
    }
    
    // Set up window callbacks
    setupWindowCallbacks(window);
    
    // Create default renderer configuration
    RendererConfig rendererConfig = defaultRendererConfig();
    
    // Initialize renderer
    initializeRenderer(rendererConfig);
    
    // Run the main render loop
    runRenderLoop(window);
    
    // Clean up
    terminateRenderer();
    terminateWindow(window);
    
    printf("Exiting Cube application\n");
    return EXIT_SUCCESS;
} 