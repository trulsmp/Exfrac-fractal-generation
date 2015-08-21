
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main()
{
    FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
    int resolution = 800;
    
    double passes = 0.005;
    int pixel = (int) 4/passes;
    printf("%d ",pixel);
    (void) fprintf(fp, "P6\n%d %d\n255\n", pixel, pixel);
    
    double xLow = -2;
    double yLow = -2;
    double xHigh = 2;
    double yHigh = 2;
    
    double array[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    
    
    
    static unsigned char greenColor[3] = {0,255,0};
    static unsigned char blueColor[3] = {0,0,255};
    static unsigned char redColor[3] = {255,0,0};
    static unsigned char yellowColor[3] = {173,255,47};
    static unsigned char orangeColor[3] = {255,140,0};

    
    int max_iteration;
    int iteration;

    double x;
    double y;
    double TEMPX;
    
    int numberOfPasses = 0;
    for (double y0 = yLow; y0 <= yHigh; y0+=passes) {
        for (double x0 = xLow; x0 <= xHigh; x0+=passes) {
            y = 0;
            x = 0;
            numberOfPasses = 0;
            printf("%s","x value:");
            printf("%f ",x0);
            printf("%s","y value:");
            printf("%f ",y0);
            printf("%s ","\n");
            max_iteration = 300;
            iteration = 0;
            while ( x*x + y*y < 4  &&  iteration < max_iteration ) {
                TEMPX = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = TEMPX;
                iteration++;
            }
            
            printf("%s ","Number of passes:");
            printf("%d ",numberOfPasses);
//            
//            if (iteration == 1) {
//                /* color the pixel red */
//                (void) fwrite(redColor, 1, 3, fp);
//            }
//            else if (iteration == 2) {
//                /*color the pixel blue */
//                (void) fwrite(blueColor, 1, 3, fp);
//            }
//            else if (iteration == 3) {
//                /* color the pixel green */
//                (void) fwrite(greenColor, 1, 3, fp);
//            }
            
            if (iteration == 1) {
                (void) fwrite(greenColor, 1, 3, fp);
            }
            else if (iteration < 300) {
                (void) fwrite(yellowColor, 1, 3, fp);
                
            }
            else if(iteration == 300) {
                (void) fwrite(orangeColor, 1, 3, fp);
            }
            
        }
    }
    (void) fclose(fp);
    return EXIT_SUCCESS;
    
}
