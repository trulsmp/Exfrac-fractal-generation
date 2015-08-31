
#ifndef __HPC__mandelbrot__
#define __HPC__mandelbrot__

#include <stdio.h>

// Writes the points to the ppm file specified
void writeColor(int iteration, int max_iterations, FILE *fp, double zIm, double zRe);

// The main algorithm were everything important happens.
// Checks all the points and determines if they are in the mandelbrot set, calling the writeColor Function
void mandelbrot(int resolution, int max_iterations, double xRange, double yRange, double yLow, double xLow);


// Initalizes different colors to draw the fractal image
void createColorMap();


#endif /* defined(__HPC__mandelbrot__) */