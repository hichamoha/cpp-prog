# Makefiles are a simple way to organize code compilation. 

# The basic makefile is composed of: 
# target: dependencies
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

#============================= Lab2 makefile ====================================

all : executable

calendarmain:
	g++ -g -std=c++0x -Wall -c calendarMain.cpp date.cpp roman.cpp julian.cpp gregorian.cpp kattistime.cpp 	
	g++ -o test.out calendarMain.o date.o roman.o julian.o gregorian.o kattistime.o
	./test.out

# To do the Julian tests
#In computing, diff is a file comparison utility that outputs the differences between 
#two files. It is typically used to show the changes between one version of a file 
#and a former version of the same file.
testjulian:
	@echo Generates res1.out ...
	g++ -g -std=c++0x -Wall -c cprog09lab22a.cpp date.cpp roman.cpp julian.cpp kattistime.cpp 	
	g++ -o res1.out cprog09lab22a.o date.o roman.o julian.o kattistime.o
	#./res1.out < lab22a.in > output1.txt
	cat lab22a.in | ./res1.out > output1.txt
	diff lab22a.out output1.txt

# To do the Gregorian tests
testgregorian:
	g++ -g -std=c++0x -Wall -c cprog09lab22b.cpp date.cpp roman.cpp gregorian.cpp kattistime.cpp 	
	g++ -o res2.out cprog09lab22b.o date.o roman.o gregorian.o kattistime.o
	./res2.out < lab22a.in > output2.txt
	diff lab22a.out output2.txt

# To do datetest.cpp 
datetest : 
	g++ -g -std=c++0x -Wall -c datetest.cpp date.cpp roman.cpp julian.cpp gregorian.cpp kattistime.cpp   # compile all definitions.cpp with -c because
                               # they don't have main functions
	g++ -o res3.out datetest.o date.o roman.o julian.o gregorian.o kattistime.o
	./res3.out

# To do the Julian+Gregorian tests
test22c:
	g++ -g -std=c++0x -Wall -c cprog09lab22c.cpp date.cpp roman.cpp julian.cpp gregorian.cpp kattistime.cpp 	
	g++ -o res4.out cprog09lab22c.o date.o roman.o julian.o gregorian.o kattistime.o
	./res4.out < lab22c.in > output4.txt
	diff lab22c.out output4.txt

# To do the Calendar tests
testcalendar:
	g++ -g -std=c++0x -Wall -c cprog09lab23.cpp date.cpp roman.cpp julian.cpp gregorian.cpp kattistime.cpp calendar.h	
	g++ -o res5.out cprog09lab23.o date.o roman.o julian.o gregorian.o kattistime.o
	./res5.out < lab23.in > output5.txt
	diff lab23.out output5.txt

EXECUTABLE = res1.out res2.out res3.out res4.out res5.out

clean :
	rm -f *.o *.txt $(EXECUTABLE)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test.out # da vedere


