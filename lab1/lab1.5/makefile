# Makefiles are a simple way to organize code compilation. 

# The basic makefile is composed of: 
# target: dependencies
# [tab] system command

# Normally, you would compile a code hello.cpp by executing the following
# command: g++ -g -std=c++0x -Wall hello.cpp -o hello.out

# Suffix rules, based on file extensions, can define generic dependencies.
# This syntax applied to our example would look like:

#%.out : %.cpp
#	g++ -g -std=c++0x -Wall $*.cpp -o $*.out


CXXTESTPATH = cxxtest/
#CXXTESTPATH = /info/DD2387/kurskatalog/cxxtest/
CXXTESTGEN = $(CXXTESTPATH)cxxtestgen.py


all: test_vec test_template_vec our_tests

test_template_vec.o: vector.h
test_vec.o: vector.h

# compile when there isn't a main function, using g++ -c
%.o: %.cpp
	g++ -c -std=c++0x -Wall -Wextra -g $*.cpp

# old test program
test_template_vec: test_template_vec.o vector.h
        #g++ -g -std=c++0x -Wall test_template_vec.cpp -o test_template_vec.out
	g++ -g -std=c++0x -Wall -Wextra test_template_vec.o -o test_template_vec

test_vec: test_vec.o vector.h
	g++ -g -std=c++0x -Wall -Wextra test_vec.o -o test_vec

# my own test code
our_tests_gen.cpp: our_tests.cpp vector.h
	$(CXXTESTGEN) --error-printer -o $@ our_tests.cpp

our_tests: our_tests_gen.cpp our_tests.cpp vector.h
	g++ -g -std=c++0x -o our_tests -I $(CXXTESTPATH) our_tests_gen.cpp our_tests.cpp

# i/o wrapper used by kattis
kattis_wrapper:
	g++ -g -std=c++0x -Wextra -Wall ../../info-lab1/cprog09lab15.cpp -I. -o kattis_wrapper


clean:
	#-rm -f *.out *.o
	-$(RM) test_vec test_template_vec our_tests

.PHONY: clean



#%.out : generate  
#	g++ -o test_1.2b.out -I /info/cprog12/cxxtest/ 1.2b.cpp must_follow_a.o

#generate : 
#	/info/cprog12/cxxtest/cxxtestgen.py --error-printer -o 1.2b.cpp test_must_follow_a.cpp
 
