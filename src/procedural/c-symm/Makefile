CC=gcc
#CFLAGS=-std=c99 -O3 -funroll-all-loops -fomit-frame-pointer
CFLAGS=-std=c99

performance: main.o
	gcc $(CFLAGS) *.o -o performance

clean:
	rm -f *.o performance result
	
