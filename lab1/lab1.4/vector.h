// -------- file vector.h - Operator�verlagring, minneshantering.

// contiene la DEFINIZIONE della classe vector

/*
-- Skapa en vektorklass "Vector" f�r positiva heltal (unsigned int). 
Du f�r inte anv�nda klassen vector i STL i din l�sning (d�remot kan du, 
om du vill, implementera en referensl�sning f�r att j�mf�ra egna tester). 

-- L�t storleken vara FIXERAD (so we don't need to Expand the vector) och best�mmas av ett argument av typen (size_t) till konstruktorn. 
�ven nollstora vektorer ska kunna skapas.
Varje vektorelement ska initieras till 0.

-- Implementera tilldelningsoperator och kopieringskonstruktor. 
Tilldelning/kopiering av olika stora vektorer ska fungera.
 
-- Implementera �ven move-konstruktor och move-operator s� att std::move fungerar. 

-- Implementera en tilldelningsoperator som tar en initializer_list som parameter.

-- Vektorklassen ska �ven �verlagra indexoperatorn [] f�r snabb �tkomst av
elementen.
    ...
    int x = 2;
    int i = vektor[7];
    vektor[3] = x;      //// OBS, ska fungera!
    Vector v2;
    v2 = {1, 2, 5};

-- Kontrollera att det �r giltig �tkomst annnars ska std::out_of_range kastas!

-- Generellt �r det ofta en god id� att l�ta konstruktorer som tar ett argument
deklareras som explicit, g�r s� �ven i denna klass. Varf�r? Ange ett exempel d�r det annars kan bli dumt.
 
-- Prova din vektor med filen test_vec.cpp i kurskatalogen. 

-- Anv�nd valgrind. Detta testprogram kontrollerar inte all funktionalitet. Du m�ste sj�lv ansvara f�r att skriva ett b�ttre testprogram som testar 
randvillkoren ordentligt, t.ex. genom att anv�nda ett testramverk som cxxtest.

Tips: T�nk p� att operatorn [] m�ste vara en konstant medlemsfunktion i vissa
fall. N�r och varf�r? Hur kopierar man vektorn?

    Vector b = a;
    a[0] = 1;      // b ska inte �ndras av denna sats. SIDE EFFECT !!!

T�nk �ven p� vad som h�nder i f�ljande fall (dvs d� vektorn f�rv�ntas kopiera
sig sj�lv):
    Vector v; v = v;
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstddef>    //size_t type is defined in the cstddef header
#include <initializer_list> 

using namespace std;

class Vector
{ 
  friend istream &operator>> (istream &, Vector &);
  friend ostream &operator<< (ostream &, const Vector &);

  public:
    // Default constructor
    Vector();    

    //fixerad storlek och Varje element ska initieras till 0. 
    // Other constructor(size), initialize to 0  
    explicit Vector(const size_t size); 
                                             

    // kopieringskonstruktor.
    Vector(const Vector &);
    
    //init list copy constructor{1,2,3,...}
    Vector(const initializer_list<unsigned int> &);

    // Destructor     
    ~Vector();                 

    // Assignment operator
    const Vector& operator=(const Vector &);
 
    //tilldelningsoperator som tar en initializer_list som parameter.
    const Vector& operator=(const initializer_list<unsigned int> ); 
 

    //move-konstruktor och move-operator s� att std::move fungerar.
    Vector(Vector &&) noexcept;
  
    Vector& operator=(Vector &&) noexcept;


    //�verlagra indexoperatorn [] f�r snabb �tkomst av elementen
    unsigned int& operator[](const int ); 

    //operatorn [] som en konstant medlemsfunktion
    const unsigned int operator[](const int ) const; 

    // storleken
    size_t length() const; 

//======= ........................................................

    // Counter: return count of vectors instantiated
    static int get_vectorCount();  

    // Compar equal
    bool operator== (const Vector &) const;

    // Determine if 2 vectors are not equal and
    // return true, otherwise return false (uses operator==)
    bool operator!= (const Vector &right) const
    {
      return ! (*this == right);
    }

    static void runTestDriver(); 

  private: 
    size_t size;  // storleken ska vara FIXERAD 
                  // so we don't need to Expand the vectorS
  	
    unsigned int *ptr; // pointer to the first element 
    static int vectorCount;  // # of vectors instantiated
};

#endif
