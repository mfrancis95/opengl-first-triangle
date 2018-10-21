all: first-triangle

clean:
	rm first-triangle

first-triangle: first-triangle.c lib.c lib.h
	gcc first-triangle.c lib.c -lGL -lSDL2 -o first-triangle