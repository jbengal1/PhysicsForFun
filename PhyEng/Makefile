all: compile link

compile:
	g++ -c main.cpp particle.hh particle.cc globalVar.hh globalVar.cc interaction.hh interaction.cc

link:
	g++ main.o particle.o globalVar.o interaction.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system