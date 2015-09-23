//
//  mandelbrot.c
//  HPC
//

#include <math.h>
#include "mandelbrot.h"
#include "png.h"
#include <omp.h>

char colors[40][3];
static unsigned char blackColor[3] = {20,20,20};

void mandelbrot(int resolution, int maxIterations, double xRange, double yRange, double yLow, double xLow) {

    // Generate the color map to draw the different colors
    createColorMap();
    
    // Bitmap containing the
    bitmap_t mandelset;
    
    mandelset.height = resolution;
    mandelset.width = resolution;
    
    mandelset.pixels = calloc (sizeof (pixel_t), mandelset.width * mandelset.height);
    
    
    char filename[32];
    
    Changing filename based on the resolution set
    snprintf(filename, sizeof(char) * 32, "./img/fractal%i.png", resolution);
    
    // Opens a new ppm file to allow for colouring.
    // Used http://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C for documentation on how to open, write and close a ppm file.
    //FILE *fp = fopen(filename, "wb");
    //(void) fprintf(fp, "P6\n%d %d\n255\n", resolution, resolution);
    
    int iteration;
    double zRe, zIm, nextZRe, yIm, xReal;
    
    //Iterates over x and y number of pixels defined
    
    double i;
    double j;
#pragma omp parallel for private(i) schedule(dynamic,10)
    for (i = 0; i < resolution; i++) {
        for (j = 0; j < resolution; j++) {
            
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
            writeColor(iteration, maxIterations, zIm, zRe,i,j, &mandelset);
        }
    }
    
    save_png_to_file(&mandelset, filename,resolution);
    
}

void writeColor(int iteration, int maxIterations, double zIm, double zRe, int i, int j, bitmap_t *mandelset){
    
    pixel_t * pixel = (*mandelset).pixels + (*mandelset).width*i+j;
    
    
    //The point is a part of the mandelbrot set, paint it black
    if(iteration == maxIterations) {
        pixel->red = 0;
        pixel->green = 0;
        pixel->blue = 0;
    }
    
    // The point has escaped the bound set and is colored based on how close it is to the mandelbrot set.
    else {
        iteration+=2;
        // Normalized iteration count algorithm, detailed http://math.unipa.it/~grim/Jbarrallo.PDF to smooth the coloring
        double NormalizedValue = iteration + 1 - log(log(zIm*zIm + zRe*zRe))/log(2);
        NormalizedValue = NormalizedValue /maxIterations * 40;
        int colorIndex = (int) NormalizedValue;
        pixel->red = colors[colorIndex][0];
        pixel->green = colors[colorIndex][1];
        pixel->blue = colors[colorIndex][2];
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
