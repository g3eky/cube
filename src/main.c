#include <stdio.h>
#include <stdlib.h>
#include "renderer/renderer.h"

int main() {
    printf("Hello from Cube!\n");
    
    // Create default configurations
    RendererConfig renderer_config = renderer_config_default();
    RendererWindowConfig window_config = renderer_window_config_default();
    
    // Initialize renderer with window
    if (!renderer_init_with_window(renderer_config, window_config)) {
        return EXIT_FAILURE;
    }
    
    // Run the main loop
    renderer_run_main_loop();
    
    // Clean up
    renderer_terminate();
    
    printf("Exiting Cube application\n");
    return EXIT_SUCCESS;
} 