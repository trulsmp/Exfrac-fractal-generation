CC=gcc
CFLAGS= -std=c99 -I.

main: mandelbrot.c exFrac.c png.c
	gcc -o exfrac exFrac.c mandelbrot.c png.c -I. -std=c99 -lm -O3 -lpng -fopenmp

clean : 
	rm  exfrac
