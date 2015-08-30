//
//  mandelbrot.c
//  HPC
//
//  Created by Truls Mørk Pettersen on 30/08/2015.
//  Copyright (c) 2015 Truls Mørk Pettersen. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"

char colors[40][3];
static unsigned char blackColor[3] = {0,0,0};

void mandelbrot(int resolution, int maxIterations, double xRange, double yRange, double yLow, double xLow) {

    // Generate the color map the draw the different colors
    createColorMap();
    
    // Opens a new ppm file to allow for colouring
    FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", resolution, resolution);
    
    int iteration;
    double zRe, zIm, nextZRe, yIm, xReal;
    
    //Iterates over x and y number of pixels defined
    for (double i = 0; i < resolution; i+=1) {
        for (double j = 0; j < resolution; j+=1) {
            
            // Finds the imaginary point y and real point x depending on what the parameters has been set to
            yIm = ((i/resolution)*yRange)+yLow;
            xReal = ((j/resolution)*xRange)+xLow;
            zIm = 0;
            zRe = 0;
            iteration = 0;
            
            // Iterate as long as the length of Z does not go out of the range bound.
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
    if(iteration == maxIterations) {
        (void) fwrite(blackColor, 1, 3, fp);
    }
    else {
        double conColor = iteration + 1 - log(log(zIm*zIm + zRe*zRe))/log(2);
        conColor = conColor /maxIterations * 20;
        int c = (int) conColor;
        //printf("%i \n", c);
        char Color[3] = {colors[c][0],colors[c][1],colors[c][2]};
        (void) fwrite(Color, 1, 3, fp);
    }
    
}

void createColorMap(){
    for (int i=0;i <20; i++) {
        colors[i][0] = i*11 + 25;
        colors[i][1] = i*5 + 6;
        colors[i][2] = 0;
    }
    for (int j = 20; j < 40; j++) {
        colors[j][0] = 255;
        colors[j][1] = j*5 +154;
        colors[j][2] = j*12 + 13;
    }
}
