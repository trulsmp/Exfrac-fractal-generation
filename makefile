CC=gcc
CFLAGS= -std=c99 -I.

main: mandelbrot.c exFract.c
	gcc -o exfrac exFract.c mandelbrot.c -I. -std=c99 -lm -pg

clean : 
	rm first.ppm exfrac
