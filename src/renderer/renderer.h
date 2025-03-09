#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

// Renderer configuration structure
typedef struct {
    float clearColorR;
    float clearColorG;
    float clearColorB;
    float clearColorA;
    float rotationSpeed; // Rotation speed in radians per second
} RendererConfig;

// Window configuration structure
typedef struct {
    int width;
    int height;
    const char* title;
    bool fullscreen;
    int glMajorVersion;
    int glMinorVersion;
} WindowConfig;

// Default renderer configuration
RendererConfig defaultRendererConfig();

// Default window configuration
WindowConfig defaultWindowConfig();

// Initialize the renderer with window
bool initializeRendererWithWindow(RendererConfig rendererConfig, WindowConfig windowConfig);

// Create the cube geometry
void createCube();

// Render a single frame
void renderFrame();

// Run the main render loop
void runMainLoop();

// Clean up renderer and window resources
void terminateRendererAndWindow();

#endif /* RENDERER_H */ 