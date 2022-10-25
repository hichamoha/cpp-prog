# Makefiles are a simple way to organize code compilation. 

# The basic makefile is composed of: 
# target : dependencies
# [tab] system command

# Normally, you would compile a code hello.cpp by executing the following
# command: g++ -g -std=c++0x -Wall hello.cpp -o hello.out

# Suffix rules, based on file extensions, can define generic dependencies.
# This syntax applied to our example would look like:

all: A.out Data.out

%.out: %.cpp
	g++ -g -std=c++0x -Wall $*.cpp -o $*.out

vg-A: A.out
	valgrind --tool=memcheck --leak-check=yes ./A.out

vg-Data: Data.out
	valgrind --tool=memcheck --leak-check=yes ./Data.out

clean : 
	-rm -f *.out
 
.PHONY : clean 
