//1.3  Temporära objekt, minnesläckor, valgrind

/* Objects are the fundamental unit of abstraction in object-oriented 
 programming. In a broad sense, an object is a region of memory storage. 
 Class objects have properties that are determined when the object is created.
 
  Conceptually, every class object has four special member functions: 
 default constructor, copy constructor, assignment operator, and destructor.
 If these members are not explicitly declared by the programmer,
 the implementation implicitly declares them.
 
 Temporary objects (or temporaries, for short) differ in several aspects 
from ordinary objects with respect to both their lifetime and assignment.
in the evaluation of complex expressions, the compiler has to store
intermediary results in a temporary location.
 Temporary objects are unnamed objects created on the stack by the compiler.
you can't refer to them explicitly, nor can you assign a value to them.
You may, however, copy their values to a named object.

 When you define an auto object, it remains alive until its scope is exited.
By contrast, temporaries are destroyed as the last step in evaluating the
full-expression that contains the point where they were created.There is one 
exception to this rule, though. When you bind a reference to a temporary, 
the bound temporary persists for the lifetime of the reference. 
*/

#include <iostream>

class A {
public:
    A()   // Default constructor ==============================
    {
       std::cout << "The default contructor" << std::endl; 
    }

    // Costruttore di coppia ==================================
    A(const A & ref) 
    {
       std::cout << "The copy contructor" << std::endl; 
    } 
    
    ~A()  // Destructor ======================================= 
    {
       std::cout << "The destructor" << std::endl; 
    }

    A(char* s)  // Other constructor =========================
    //A(std::string s)  // Other constructor ==================
    {
       std::cout << "Some other constructor " << s << std::endl;
    }

  // Overloading dell'assegnazione =============================
  /* 
     Here assignment operator must be defined as a member function.
     ==> the left-hand operand is bound to the implicit "this" parameter.
   */     
    A& operator= (const A & s) 
    {
       std::cout << "The assignment operator" << std::endl; 
       return *this;
    }
};

void no_ref(A a) {}

void with_ref(const A & a) {}

int main()
{
    A a("my name is a");
    A b = a;         //initialization          // vad är skillnaden
    A c(a);          //initialization          // mellan dessa
    A d;             //Default constructor     // tre tekniker?
    d = a;           //Assignment, not copy constructor 

    no_ref(a);       //yes, parameter passing per value //Bildas temporära objekt?
    with_ref(a);     //NO ??                          // Bildas temporära objekt?

    A *aa = new A[5]; // allocate enough memory to hold 5 instances of type A
                      // contiguously and return its address.
                      //När du allokerar dynamiskt minne, se till att överlåta
                      // ansvaret att frigöra minnet till ett objekt så fort som
                      // möjligt efter allokeringen. Använd std::vector istället
                      // för new[] eller "smarta pekare" std::shared_ptr<>

    delete aa;       /* Vad kommer att hända? 
                        Invalid delete!..delete bara en object
                        of 5 allocated in memory */
    //delete [] aa;
    return 0;
}
/*********** Correction:
   a memory leak arises whenever memory allocated through new is never
   returned through delete.
    delete [] aa; fine !    delete aa;  Invalid delete !!!  
*/


/********** Analyse
==7186== Memcheck, a memory error detector
==7186== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==7186== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==7186== Command: ./A.out
==7186== 
Some other constructor my name is a
The copy contructor
The copy contructor
The default contructor
The assignment operator
The copy contructor
The destructor
The default contructor
The default contructor
The default contructor
The default contructor
The default contructor
The destructor
==7186== Invalid free() / delete / delete[] / realloc()
==7186==    at 0x4C2A4BC: operator delete(void*) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==7186==    by 0x400AA2: main (A.cpp:33)
==7186==  Address 0x59ff048 is 8 bytes inside a block of size 13 alloc'd
==7186==    at 0x4C2AC27: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==7186==    by 0x400A4D: main (A.cpp:32)
==7186== 
The destructor
The destructor
The destructor
The destructor
==7186== 
==7186== HEAP SUMMARY:
==7186==     in use at exit: 13 bytes in 1 blocks
==7186==   total heap usage: 1 allocs, 1 frees, 13 bytes allocated
==7186== 
==7186== 13 bytes in 1 blocks are definitely lost in loss record 1 of 1
==7186==    at 0x4C2AC27: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==7186==    by 0x400A4D: main (A.cpp:32)
==7186== 
==7186== LEAK SUMMARY:
==7186==    definitely lost: 13 bytes in 1 blocks
==7186==    indirectly lost: 0 bytes in 0 blocks
==7186==      possibly lost: 0 bytes in 0 blocks
==7186==    still reachable: 0 bytes in 0 blocks
==7186==         suppressed: 0 bytes in 0 blocks
==7186== 
==7186== For counts of detected and suppressed errors, rerun with: -v
==7186== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 2 from 2)

*/
