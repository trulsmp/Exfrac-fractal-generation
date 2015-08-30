CC=gcc
CFLAGS=-std=c99 -I.

hellomake: mandelbrot.c exFract.c
	gcc -o exfrac exFract.c mandelbrot.c -I.
