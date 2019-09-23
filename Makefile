all: TrabRobo

TrabRobo: main.o Robo.o
#	g++ main.o Formigas.o -o IARformigas -lsfml-graphics -lsfml-window -lsfml-system
	g++ -L./SFML-2.5.1/lib main.o Robo.o -o TrabRobo -lsfml-graphics -lsfml-window -lsfml-system -Wl,-R./SFML-2.5.1/lib

main.o: main.cpp
#	g++ -I./SFML-2.5.1/include -L./SFML-2.5.1/lib -c main.cpp -o main.o 
	g++ -O3 -I./SFML-2.5.1/include -I. -c main.cpp -o main.o

Robo.o:
	g++ -I. -c Robo.cpp -o Robo.o

TrabRobo.0: Robo.cpp Robo.hpp
	g++ -O3 -c Robo.cpp -o Robo.o

.PHONY: clean mrproper

clean: 
	rm -f main.o Robo.o

mrproper: clean
	rm  -f TrabRobo
