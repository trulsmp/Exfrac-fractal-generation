//
//  Header.h
//  HPC
//
//  Created by Truls Mørk Pettersen on 30/08/2015.
//  Copyright (c) 2015 Truls Mørk Pettersen. All rights reserved.
//


// Write the color of each pixel to a ppm file
void writeColor(int iteration, int max_iterations,FILE *fp, double zIm, double zRe);


// Performs the mandelbrot calculation
void mandelbrot(int resolution, int max_iterations, double xRange, double yRange, double yLow, double xLow);


// Parsing the inputs of the user
void parseInputs(int argc, char* argv[], int *resolution, int *max_iterations);
