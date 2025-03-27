
all: MS1

# Executables
MS1: assg.o vector.o spheres.o
	gcc -Wall -std=c99 assg.o vector.o spheres.o -o MS1_assg -lm

MS2: # TODO ...

FS: # TODO ...

# Object files
assg.o: src/assg.c src/vector.h src/spheres.h
	gcc -Wall -std=c99 -c src/assg.c -o assg.o

vector.o: src/vector.c src/vector.h
	gcc -Wall -std=c99 -c src/vector.c -o vector.o

spheres.o: src/spheres.c src/spheres.h
	gcc -Wall -std=c99 -c src/spheres.c -o spheres.o

# Clean up object files and executables
clean:
	rm -f *.o MS1_assg
