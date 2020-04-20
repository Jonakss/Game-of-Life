CC=g++
CLIB=-L/opt/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
CINCLUDE=-I/opt/SFML-2.5.1/include
CFLAGS=-Wall -std=c++11
DEPS=./headers/main.hpp ./headers/Base.hpp
OBJ_MAIN=main.o Base.o

all: Base clean

Base: $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) -o Base $(CLIB) $(CINCLUDE)

main.o: src/main.cpp
	$(CC) -c src/main.cpp $(CINCLUDE)

Base.o: src/Base.cpp headers/Base.hpp
	$(CC) -c src/Base.cpp $(CINCLUDE)

clean:
	rm -fr *.o
	echo "Cleaning done"
