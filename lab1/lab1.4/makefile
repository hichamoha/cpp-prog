# Makefiles are a simple way to organize code compilation. 

# The basic makefile is composed of: 
# target: dependencies
# [tab] system command

# Normally, you would compile a code hello.cpp by executing the following
# command: g++ -g -std=c++0x -Wall hello.cpp -o hello.out

# Suffix rules, based on file extensions, can define generic dependencies.
# This syntax applied to our example would look like:

CXXTESTPATH = ../cxxtest/
CXXTESTGEN = $(CXXTESTPATH)cxxtestgen.py

all : test_vec my_tests

%.o : %.cpp
	g++ -c -std=c++0x $*.cpp

%.out : %.cpp
	g++ -g -std=c++0x -Wall $*.cpp -o $*.out

# old test program
test_vec : test_vec.out vector.o vector.h
	g++ -g -std=c++0x -Wall test_vec.out vector.o -o test_vec

# my own test code
my_tests_gen.cpp : my_tests.cpp vector.h
	$(CXXTESTGEN) --error-printer -o $@ my_tests.cpp

my_tests: my_tests_gen.cpp my_tests.cpp vector.h vector.o
	g++ -o my_tests -I $(CXXTESTPATH) my_tests_gen.cpp my_tests.cpp vector.o



clean:
	-rm -f *.out *.o	
	#-$(RM) test_vec

.PHONY: clean


#%.out : generate  
#	g++ -o test_1.2b.out -I /info/cprog12/cxxtest/ 1.2b.cpp must_follow_a.o

#generate : 
#	/info/cprog12/cxxtest/cxxtestgen.py --error-printer -o 1.2b.cpp test_must_follow_a.cpp
 
