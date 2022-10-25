SHELL=/bin/sh
CC=g++

CDFLAGS=-g -std=c++0x -c -Wall -Wextra
LDFLAGS=

SOURCES = actor.cpp bag.cpp default_weapon.cpp environment.cpp merlin_cave.cpp exit.cpp food.cpp game.cpp commands.cpp human.cpp inside.cpp key.cpp excalibur.cpp object.cpp player.cpp room.cpp terminal.cpp goblin.cpp dragon.cpp dragon_factory.cpp wand.cpp weapon.cpp wizard.cpp container.cpp

OBJECTS = $(SOURCES:.cpp=.o) # Substitution variable that turns a list of *.cpp to *.o

EXECUTABLE = camelot

all : $(SOURCES) $(EXECUTABLE)

# $@ expands to the file name of the target
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Implicit rule (http://www.gnu.org/software/make/manual/make.html#Implicit-Rules)
# Double-suffix rule (old-fashioned way of implicit rules)
.cpp.o:
	$(CC) $(CDFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) saveFile

run: all
	./$(EXECUTABLE) 
