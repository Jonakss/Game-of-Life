CC=g++
CLIB=-L/opt/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
CINCLUDE=-I/opt/SFML-2.5.1/include
CFLAGS=-Wall -std=c++11
DEPS=./headers/main.hpp ./headers/Base.hpp
OF=./out
OBJ_MAIN=$(OF)/main.o $(OF)/Base.o $(OF)/Cell.o
EXEC=GOL

GOL: $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) -o $(EXEC) $(CLIB) $(CINCLUDE)

./out/main.o: src/main.cpp
	$(CC) -c src/main.cpp $(CINCLUDE) -o $@

./out/Base.o: src/Base.cpp headers/Base.hpp
	$(CC) -c src/Base.cpp $(CINCLUDE) -o $@

./out/Cell.o: src/Cell.cpp headers/Cell.hpp
	$(CC) -c src/Cell.cpp $(CINCLUDE) -o $@

clean:
	rm -fr $(OF)/*.o
	echo "Cleaning done"
