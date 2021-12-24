IDIR = include
BINC = $(IDIR)/includes.hh
SDIR = src

all: compile link

compile:
	g++ -c main.cpp $(IDIR)/particle.hh $(SDIR)/particle.cc $(IDIR)/interaction.hh $(SDIR)/interaction.cc $(IDIR)/globalVar.hh $(SDIR)/globalVar.cc $(IDIR)/globalFunc.hh $(SDIR)/globalFunc.cc

link:
	g++ main.o particle.o interaction.o globalVar.o globalFunc.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system