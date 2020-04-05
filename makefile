CC=g++
CLIB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
CFLAGS=-Wall -std=c++11
DEPS=./headers/main.hpp ./headers/Base.hpp
OBJ_MAIN=main.o Base.o

Base: $(OBJ_MAIN)
	$(CC) -o Base -L/usr/lib/SFML-2.5.1/lib -I/lib/usr/SFML-2.5.1/include $(OBJ_MAIN)

main.o: src/main.cpp
	$(CC) -c src/main.cpp $(CFLAGS)

Base.o: src/Base.cpp headers/Base.hpp
	$(CC) -c src/Base.cpp $(CFLAGS)

.PHONY: clean
	rm -fr *.o
