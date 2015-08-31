CC=gcc
CFLAGS= -std=c99 -I.

main: mandelbrot.c exFrac.c
	gcc -o exfrac exFrac.c mandelbrot.c -I. -std=c99 -lm -O3

clean : 
	rm first.ppm exfrac
