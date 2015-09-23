CC=gcc
CFLAGS= -std=c99

main: mandelbrot.c exFrac.c png.c
	icc -o exfrac exFrac.c mandelbrot.c png.c -std=c99 -lm -O3 -openmp -I thirdparty/include/ -lpng -L thirdparty/lib/libpng16/ 

clean : 
	rm  exfrac
