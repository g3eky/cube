#include "include/renderer.h"
#include "include/window.h"
#include <stdio.h>

// Global renderer configuration
static RendererConfig currentConfig;

RendererConfig defaultRendererConfig() {
    RendererConfig config;
    config.clearColorR = 0.2f;
    config.clearColorG = 0.3f;
    config.clearColorB = 0.3f;
    config.clearColorA = 1.0f;
    return config;
}

void initializeRenderer(RendererConfig config) {
    // Store the configuration
    currentConfig = config;
    
    // Print OpenGL information
    printOpenGLInfo();
}

void renderFrame() {
    // Clear the screen
    clearWindow();
    
    // Set the clear color (background)
    setClearColor(
        currentConfig.clearColorR,
        currentConfig.clearColorG,
        currentConfig.clearColorB,
        currentConfig.clearColorA
    );
    
    // Add more rendering code here as the application grows
}

void runRenderLoop(WindowHandle window) {
    // Main loop
    while (!windowShouldClose(window)) {
        // Render a frame
        renderFrame();
        
        // Swap front and back buffers
        swapWindowBuffers(window);
        
        // Poll for and process events
        pollWindowEvents();
    }
}

void terminateRenderer() {
    // Clean up renderer resources
    // Currently nothing to clean up
} 