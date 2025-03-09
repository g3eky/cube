#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"

// Renderer configuration structure
typedef struct {
    float clearColorR;
    float clearColorG;
    float clearColorB;
    float clearColorA;
    float rotationSpeed; // Rotation speed in radians per second
} RendererConfig;

// Default renderer configuration
RendererConfig defaultRendererConfig();

// Initialize the renderer
void initializeRenderer(RendererConfig config);

// Create the cube geometry
void createCube();

// Render a single frame
void renderFrame();

// Run the main render loop
void runRenderLoop(WindowHandle window);

// Clean up renderer resources
void terminateRenderer();

#endif /* RENDERER_H */ 