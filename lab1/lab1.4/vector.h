// -------- file vector.h - Operatoröverlagring, minneshantering.

// contiene la DEFINIZIONE della classe vector

/*
-- Skapa en vektorklass "Vector" för positiva heltal (unsigned int). 
Du får inte använda klassen vector i STL i din lösning (däremot kan du, 
om du vill, implementera en referenslösning för att jämföra egna tester). 

-- Låt storleken vara FIXERAD (so we don't need to Expand the vector) och bestämmas av ett argument av typen (size_t) till konstruktorn. 
Även nollstora vektorer ska kunna skapas.
Varje vektorelement ska initieras till 0.

-- Implementera tilldelningsoperator och kopieringskonstruktor. 
Tilldelning/kopiering av olika stora vektorer ska fungera.
 
-- Implementera även move-konstruktor och move-operator så att std::move fungerar. 

-- Implementera en tilldelningsoperator som tar en initializer_list som parameter.

-- Vektorklassen ska även överlagra indexoperatorn [] för snabb åtkomst av
elementen.
    ...
    int x = 2;
    int i = vektor[7];
    vektor[3] = x;      //// OBS, ska fungera!
    Vector v2;
    v2 = {1, 2, 5};

-- Kontrollera att det är giltig åtkomst annnars ska std::out_of_range kastas!

-- Generellt är det ofta en god idé att låta konstruktorer som tar ett argument
deklareras som explicit, gör så även i denna klass. Varför? Ange ett exempel där det annars kan bli dumt.
 
-- Prova din vektor med filen test_vec.cpp i kurskatalogen. 

-- Använd valgrind. Detta testprogram kontrollerar inte all funktionalitet. Du måste själv ansvara för att skriva ett bättre testprogram som testar 
randvillkoren ordentligt, t.ex. genom att använda ett testramverk som cxxtest.

Tips: Tänk på att operatorn [] måste vara en konstant medlemsfunktion i vissa
fall. När och varför? Hur kopierar man vektorn?

    Vector b = a;
    a[0] = 1;      // b ska inte ändras av denna sats. SIDE EFFECT !!!

Tänk även på vad som händer i följande fall (dvs då vektorn förväntas kopiera
sig själv):
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
 

    //move-konstruktor och move-operator så att std::move fungerar.
    Vector(Vector &&) noexcept;
  
    Vector& operator=(Vector &&) noexcept;


    //överlagra indexoperatorn [] för snabb åtkomst av elementen
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
