
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int resX;
    int resY;
    int max_iteration;
    double xLow;
    double yLow;
    double xHigh = 2;
    double yHigh = 2;
    
    if (argc < 2) {
        printf("%s","No input arguments given, setting to default values of 800x800 and 1000 iterations \n");
        printf("%s","To set parameters yourself, where ./a.out 1 2 3 4 5 is the different values. \n 1 = X resolution, \n 2 = Y resolution, \n 3 = max iterations, \n 4/5 - start points for algorithm between -2 and 2, 4 = X, 5 = Y");
        resX = 800;
        resY = 800;
        max_iteration = 1000;
        double xLow = -2;
        double yLow = -2;
    }
    else {
        resX = atoi(argv[1]);
        resY = atoi(argv[2]);
        max_iteration = atoi(argv[3]);
        if {argc > 5;
        double xLow = arg[4];
        double yLow = arg[5];
        
    }
    
    FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", resX, resY);
    
    double xLow = -2;
    double yLow = -2;
    double xHigh = 2;
    double yHigh = 2;
    
    static unsigned char blackColor[3] = {0,0,0};
    
    int iteration;

    double x;
    double y;
    double TEMPX;
    double y0;
    double x0;
    int N = 256;
    int N3 = N*N*N;
    
    for (double i = 0; i < resY; i+=1) {
        for (double j = 0; j < resX; j+=1) {
            y0 = ((i/resY)*4)+yLow;
            x0 = ((j/resX)*4)+xLow;
            y = 0;
            x = 0;
            iteration = 0;
            
            while ( x*x + y*y < 4  &&  iteration < max_iteration ) {
                TEMPX = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = TEMPX;
                iteration++;
            }
            
            
            if(iteration == max_iteration) {
                (void) fwrite(blackColor, 1, 3, fp);
            }
            else {
                double t = (double)iteration/(double)max_iteration;
                iteration = (int)(t* (double) N3);
                
                int blue = iteration/(N*N);
                int nn = iteration - blue * N * N;
                int red = nn/N;
                int green = nn - red * N;
                
                char Color[3] = {red,green,blue};
                (void) fwrite(Color, 1, 3, fp);
            }
            
        }
    }
    (void) fclose(fp);
    return EXIT_SUCCESS;
    
}
