all: bitmap.o rectangles.o main.o
	gcc bitmap.o rectangles.o main.o -o course
main.o: main.c rectangles.h bitmap.h
	gcc -c main.c
rectangles.o: rectangles.h rectangles.c
	gcc -c rectangles.c
bitmap.o: bitmap.c bitmap.h
	gcc -c bitmap.c