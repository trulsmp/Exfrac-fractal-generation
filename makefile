CC=gcc
CFLAGS=-std=c99 -I.

hellomake: mandelbrot.c exFract.c png.c
	gcc -o exfrac exFract.c mandelbrot.c png.c -I.
