CC=gcc
CFLAGS= -std=c99 -I.

<<<<<<< HEAD
main: mandelbrot.c exFract.c
	gcc -o exfrac exFract.c mandelbrot.c -I. -std=c99 -lm -pg

clean : 
	rm first.ppm exfrac
=======
hellomake: mandelbrot.c exFract.c png.c
	gcc -o exfrac exFract.c mandelbrot.c png.c -I.
>>>>>>> 81eff19f0f7d77cc0d723412a05657344c98edcb
