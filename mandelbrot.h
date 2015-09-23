
#ifndef __HPC__mandelbrot__
#define __HPC__mandelbrot__

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

typedef struct {
    pixel_t *pixels;
    size_t width;
    size_t height;
} bitmap_t;


// Writes the points to the ppm file specified
void writeColor(int iteration, int max_iterations, double zIm, double zRe, int i, int j, bitmap_t *mandelbrot);

// The main algorithm were everything important happens.
// Checks all the points and determines if they are in the mandelbrot set, calling the writeColor Function
void mandelbrot(int resolution, int max_iterations, double xRange, double yRange, double yLow, double xLow);


// Initalizes different colors to draw the fractal image
void createColorMap();


#endif /* defined(__HPC__mandelbrot__) */