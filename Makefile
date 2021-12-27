all: NBody

NBody: nbody.o main.o
	g++ nbody.o main.o -o NBody -lsfml-graphics -lsfml-window -lsfml-system

nbody.o: nbody.cpp nbody.h
	g++ -c nbody.cpp -Wall -Werror -pedantic

main.o: main.cpp
	g++ -c main.cpp -Wall -Werror -pedantic
clean:
	rm *.o NBody
