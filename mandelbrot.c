//
//  mandelbrot.c
//  HPC
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"

char colors[40][3];
static unsigned char blackColor[3] = {20,20,20};

void mandelbrot(int resolution, int maxIterations, double xRange, double yRange, double yLow, double xLow) {

    // Generate the color map to draw the different colors
    createColorMap();
    
    char filename[32];
    
    //Changing filename based on the resolution set
    snprintf(filename, sizeof(char) * 32, "./img/fractal%i.ppm", resolution);
    
    // Opens a new ppm file to allow for colouring.
    // Used http://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C for documentation on how to open, write and close a ppm file.
    FILE *fp = fopen(filename, "wb");
    (void) fprintf(fp, "P6\n%d %d\n255\n", resolution, resolution);
    
    int iteration;
    double zRe, zIm, nextZRe, yIm, xReal;
    
    //Iterates over x and y number of pixels defined
    for (double i = 0; i < resolution; i++) {
        for (double j = 0; j < resolution; j++) {
            
            // Finds the imaginary point y and real point x depending on what the parameters has been set to
            yIm = ((i/resolution)*yRange)+yLow;
            xReal = ((j/resolution)*xRange)+xLow;
            
            zIm = 0.0;
            zRe = 0.0;
            iteration = 0;
            
            
            // Iterate as long as the length of Z does not go out of the range bound.
            // Algorithm is further detailed in the report.
            while ( zRe*zRe + zIm*zIm < 4  &&  iteration < maxIterations ) {
                nextZRe = zRe*zRe - zIm*zIm + xReal;
                zIm = 2*zRe*zIm + yIm;
                zRe = nextZRe;
                iteration++;
            }
            
            writeColor(iteration, maxIterations,fp, zIm, zRe);
        }
    }
    (void) fclose(fp);
    
}

void writeColor(int iteration, int maxIterations,FILE *fp, double zIm, double zRe){
    
    //The point is a part of the mandelbrot set, paint it black
    if(iteration == maxIterations) {
        (void) fwrite(blackColor, 1, 3, fp);
    }
    
    // The point has escaped the bound set and is colored based on how close it is to the mandelbrot set.
    else {
        iteration+=2;
        // Normalized iteration count algorithm, detailed http://math.unipa.it/~grim/Jbarrallo.PDF to smooth the coloring
        double NormalizedValue = iteration + 1 - log(log(zIm*zIm + zRe*zRe))/log(2);
        NormalizedValue = NormalizedValue /maxIterations * 40;
        int colorIndex = (int) NormalizedValue;
        char Color[3] = {colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2]};
        (void) fwrite(Color, 1, 3, fp);
    }
    
}

void createColorMap(){
    for (int i=0;i <10; i++) {
        colors[i][0] = i*23 + 25;
        colors[i][1] = i*14 + 6;
        colors[i][2] = 0;
    }
    for (int j = 0; j < 10; j++) {
        colors[j+10][0] = 255;
        colors[j+10][1] = j*5 +154;
        colors[j+10][2] = j*12 + 13;
    }
    for (int i = 0; i < 10; i++) {
        colors[i+30][0] = 255;
        colors[i+30][1] = 255;
        colors[i+30][2] = 235+2*i;
    }
    for (int i = 0; i < 10; i++) {
        colors[i+20][0] = i + 245;
        colors[i+20][1] = 255;
        colors[i+20][2] = i*24;
    }
}
