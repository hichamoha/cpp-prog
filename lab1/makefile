# Makefiles are a simple way to organize code compilation. 

# The basic makefile is composed of: 
# target : dependencies
# [tab] system command

# Normally, you would compile a code hello.cpp by executing the following
# command: g++ -g -std=c++0x -Wall hello.cpp -o hello.out

# Suffix rules, based on file extensions, can define generic dependencies.
# This syntax applied to our example would look like:

%.out : %.cpp
	g++ -g -std=c++0x -Wall $*.cpp -o $*.out

%.out : generate  
	g++ -o test_1.2b.out -I /info/cprog12/cxxtest/ 1.2b.cpp must_follow_a.o

generate : 
	/info/cprog12/cxxtest/cxxtestgen.py --error-printer -o 1.2b.cpp test_must_follow_a.cpp

clean : 
	-rm -f *.out
 
.PHONY : clean 
