#include <iostream>
#include <stdexcept>
#include "vector.h"     // inkludera din headerfil här
#include "vector.cpp"

int main()
{
    // Några saker som ska fungera:
    Vector a(7);           // initiering med 7 element

   // test1: print a size and contents
   cout << " TEST 1: Size of vector a is "
        << a.length()
        << "\n vector after initialization:\n"
        << a << '\n';

    Vector b(a);           // kopieringskonstruktor 

   // test2: create b using a as an
   // initializer; print size and contents
   cout << "\n TEST 2: Size of vector b is " << b.length()
        << "\n vector after initialization:\n"
        << b << '\n';

   // test3: input and print a
   cout << " TEST 3: Input 7 integers:\n";
   cin >> a;
   cout << "After input, a contains:\n"
        << " a:\n" << a;
       

    Vector c = a;          // kopieringskonstruktor 
   // Test4: use overloaded assignment = operator
   cout << " TEST 4: Assigning a to c:\n";
   cout << " a:\n" << a 
        << " c:\n" << c << '\n'; 

    a = b;   //Test5: tilldelning genom kopiering
   // use overloaded assignment = operator
   cout << " TEST 5: Assigning b to a:\n";
   cout << " a:\n" << a 
        << " b:\n" << b << '\n'; 

    a[5] = 7;              // tilldelning till element
    cout << " a:\n" << a;

    // Test6: konstant objekt med 10 element
    const Vector e(10);   
    // vi kan initialisera men int modifiera const objekt
    /*      
    cout << " TEST 6: Input 10 integers:\n";
    cin >> e;
    cout << "After input, e contains:\n"
        << " e:\n" << e;
    */
    
    cout << " TEST 6: Size of vector e is "
        << e.length()
        << "\n vector after initialization:\n"
        << e << '\n';
    
    int i = e[5];          // const int oper[](int) const körs
    cout << " Vector e at index 5 is:" << i << '\n';

    i = a[0];              // vektorn är nollindexerad
    cout << " Vector a at index 0 is:" << i << '\n';

    i = a[5];              // int oper[](int) körs
    cout << " Vector a at index 5 is:" << i << '\n';
    
    a[5]++;                // öka värdet till 8
    cout << " Increment of a[5] is:" << a[5] << '\n';

    try {
        i = e[10];             // försöker hämta element som ligger utanför e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }
    
#if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall behållas frigörs
#endif

    return 0;
}
