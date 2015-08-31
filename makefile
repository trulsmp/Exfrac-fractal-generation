CC=gcc
CFLAGS= -std=c99 -I.

main: mandelbrot.c exFract.c
	gcc -o exfrac exFract.c mandelbrot.c -I. -O3 -std=c99 -lm

clean : 
	rm first.ppm exfrac
