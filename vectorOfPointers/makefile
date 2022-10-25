SHELL=/bin/sh
CC=g++

CDFLAGS=-g -std=c++0x -c -Wall -Wextra
LDFLAGS=

SOURCES = delete_vector_pointers.cpp

OBJECTS = $(SOURCES:.cpp=.o) # Substitution variable that turns a list of *.cpp to *.o

EXECUTABLE = delete_vector_pointers

all : $(SOURCES) $(EXECUTABLE)

# $@ expands to the file name of the target
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Implicit rule (http://www.gnu.org/software/make/manual/make.html#Implicit-Rules)
# Double-suffix rule (old-fashioned way of implicit rules)
.cpp.o:
	$(CC) $(CDFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)

run: all
	./$(EXECUTABLE)
