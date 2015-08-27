
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
static unsigned char blackColor[3] = {0,0,0};

void writeColor(int iteration, int max_iterations,FILE *fp);
void mandelbrot(int xResolution, int yResolution, int max_iterations, double xRange, double yRange, double yLow, double xLow);


int main(int argc, char *argv[])
{
    int xResolution, yResolution, max_iterations;
    double xLow = -2.0;
    double yLow = -2.0;
    double xHigh = 2.0;
    double yHigh = 2.0;
    double xRange, yRange;
    
    if (argc < 2) {
        //No input arguments given, setting to default values of 2000x2000, 1000 max_iterations,
        xResolution = 2000;
        yResolution = 2000;
        max_iterations = 1000;
        xLow = -2.0;
        yLow = -2.0;
    }
    else {
        // Checking the input arguments and setting the default data.
        xResolution = atoi(argv[1]);
        yResolution = atoi(argv[2]);
        max_iterations = atoi(argv[3]);
        
        // checks if there is arguments to enable zooming of the mandelbrot fractal
        if (argc > 5) {
            xLow = atof(argv[4]);
            yLow = atof(argv[5]);
            xHigh = atof(argv[6]);
            yHigh = atof(argv[7]);
        }
        
    }
    
    //Checks the distance of the calculation to enable zooming
    xRange = -xLow + xHigh;
    yRange = -yLow + yHigh;
    
    mandelbrot(xResolution,yResolution,max_iterations,xRange,yRange,yLow,xLow);
    
    return EXIT_SUCCESS;
    
}


void mandelbrot(int xResolution, int yResolution, int max_iterations, double xRange, double yRange, double yLow, double xLow) {
    
    // Opens a new ppm file to allow for colouring
    FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", xResolution, yResolution);
    
    int iteration;
    double x, y, TEMPX, y0, x0;
    
    for (double i = 0; i < yResolution; i+=1) {
        for (double j = 0; j < xResolution; j+=1) {
            y0 = ((i/yResolution)*yRange)+yLow;
            x0 = ((j/xResolution)*xRange)+xLow;
            y = 0;
            x = 0;
            iteration = 0;
            
            while ( x*x + y*y < 4  &&  iteration < max_iterations ) {
                TEMPX = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = TEMPX;
                iteration++;
            }
            
            writeColor(iteration, max_iterations,fp);
        }
    }
    (void) fclose(fp);

}

void writeColor(int iteration, int max_iterations,FILE *fp){
    if(iteration == max_iterations) {
        (void) fwrite(blackColor, 1, 3, fp);
    }
    else {
        double t = (double)iteration/(double)max_iterations;
        
        // 18609625 is a constant 256*256*256, replaced with numbers to lessen the calculations needed
        iteration = (int)(t* (double) 18609625);
        
        int blue = iteration/(65536);
        int nn = iteration - blue * 65536;
        int red = nn/256;
        int green = nn - red * 256;
        
        char Color[3] = {red,green,blue};
        (void) fwrite(Color, 1, 3, fp);
    }

}
