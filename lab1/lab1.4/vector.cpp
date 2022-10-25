// File vector.cpp 
// contiene la definizione delle funzioni della classe vector

#include "vector.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iomanip>

using namespace std;

// initialize static data member at file scope
int Vector::vectorCount = 0;   // no obects yet


// TESTING DRIVER ===========================================
void Vector::runTestDriver()
{ 
   // 1) no objects yet
   cout << "\n TEST 1: # of vectors instantiated = "
        << Vector::get_vectorCount() << '\n';

   // 2) create two vectors and print vector count
   Vector v1( 7 ), v2;
   cout << "\n TEST 2: # of vectors instantiated = "
        << Vector::get_vectorCount() << "\n\n";

   // 3) print v1 size and contents
   cout << " TEST 3: Size of vector v1 is "
        << v1.length()
        << "\n vector after initialization:\n"
        << v1 << '\n';

   // 4) print v2 size and contents
   cout << " TEST 4: Size of vector v2 is "
        << v2.length() << '\n';   
        //<< "\n vector after initialization:\n"
        //<< v2 << '\n';

   // 5) create v3 using v1 as an
   // initializer; print size and contents
   Vector v3(3);
   cout << "\n TEST 5: Size of vector v3 is " << v3.length()
        << "\n vector after initialization:\n"
        << v3 << '\n';

   // 6) input and print V1 and V3
   cout << " TEST 6: Input 10 integers:\n";
   cin >> v1 >> v3;
   cout << "After input, the vectors contain:\n"
        << " v1:\n" << v1
        << " v3:\n" << v3 << '\n';

   // 7) use overloaded inequality (!=) operator
   cout << " TEST 7: Evaluating: v1 != v3\n";
   if (v1 != v3)
      cout << " They are not equal\n"; 

   // 8) create vector v4 using v1 as an
   // initializer; print size and contents
   Vector v4(v1);
   cout << "\n TEST 8: Size of vector v4 is, using v1 as initializer: " 
        << v4.length()
        << "\n vector v4 after initialization:\n"
        << v4 << '\n'; 

   // 9) use overloaded assignment = operator
   cout << " TEST 9: Assigning v3 to v1:\n";
   v1 = v3;
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 

  // 10) use overloaded equality (==) operator
   cout << " TEST 10: Evaluating: v1 == v3\n";
   if (v1 == v3)
      cout << " They are equal\n\n";

  // 11) use overloaded subscript operator to create rvalue
   cout << " TEST 11: v1[1] is " << v1[1] << '\n';

  // 12) attempt to use out of range subscript
   cout << "\n TEST 12: Attempt to assign 1000 to v1[15]" << endl;
   v1[15] = 1000;  // ERROR: out of range
   
}

//========================================== DEFAULT CONSTRUCTOR 

Vector::Vector()    
{
  size = 0;     // nollstora vektorer ska kunna skapas.
  ptr = nullptr;
  ++vectorCount;   // count one more object
}

//============================================ OTHER CONSRUCTOR
 
//fixerad storlek och Varje element ska initieras till 0.
// Other constructor(size, initialize to 0 )    
Vector::Vector(const size_t vecSize) : size(vecSize)
{
  if (size > 0)
  { 
    ptr = new unsigned int[size];  // create space for vector
    ++vectorCount;                 // count one more object
  } 

  else
    ptr = nullptr;
	
  for (size_t i=0; i<size; i++)    //for (auto i : v) 
    ptr[i] = 0;                    //initialize vector
}
 
//COPY CONSTRUCTOR =============================================== 
                                          
/*
   # E’ necessario creare esplicitamente un costruttore di
     copia quando un oggetto ha dati membro allocati
     dinamicamente.(in questo caso ptr=new unsigned int[size])
   # Per oggetti con dati allocati dinamicamente la copia bit-a-
     bit copia solo il dato puntatore, cioè l’indirizzo di
     memoria
*/
// Copy constructor: MUST receive a reference to prevent 
// infinite recursion(Dipendenza logica circolare) 
// Advice: use constructor initializers!   
Vector::Vector(const Vector &copia) : size(copia.size)  
{
  if (size > 0)
  {
    ptr = new unsigned int[size];    //create space for vector 
    ++vectorCount;                   // count one more object

    for (size_t i=0; i<size; i++)
      ptr[i] = copia.ptr[i];         //copy copia into object
  }
  else ptr = nullptr; 
}

// EXTRA COPY CONSTRUCTOR ============================================
// initializer_list copy constructor: {1,2,3,...}      
Vector::Vector(const initializer_list<unsigned int> &il) : size(il.size()) 
{
  if (size > 0)
  {
      ptr = new unsigned int[size];
      ++vectorCount;
  }

  else ptr = nullptr; 
/**
  begin and end return iterators of type 
  initializer_list<size_t>::iterator
  c++11 standard: auto iter = il.begin()
*/
  int i = 0;    
  for (auto iter=il.begin(); iter!=il.end(); ++iter)
      ptr[i++] = *iter;  // XXX
}

// DESTRUCTOR =========================================================
// Destructor 
Vector::~Vector()
{
  delete[] ptr;
  --vectorCount;    // one fewer object
} 

// OVERLOADING =======================================================
/**
############    Overloading di Operatori

• Perché un operatore possa operare sugli oggetti di
  una classe deve necessariamente essere ridefinito
• fanno eccezione:
   – operatore di assegnamento =
     il suo comportamento di default è di eseguire una copia di
     membro a membro dei dati di una classe
   – operatore di indirizzo &
     il suo comportamento di default è di restituire l’indirizzo di
     memoria dell’oggetto
• tuttavia anche = e & possono essere ridefiniti se serve
*/
// Overloaded assignment operator                
// const return avoids: (a1 = a2) = a3
const Vector & Vector::operator= (const Vector &right)
{
  if (&right == this)   //check for self-assignment
      return *this;     //same object
  
  //for vector of different sizes, deallocate original
  //left side vector then allocate new left side vector
  
  else if (size != right.size)
  {
     delete [] ptr;
     size = right.size;
     ptr = new unsigned int[size];
     assert(ptr != nullptr);    //terminate if memory not allocated
  } 
 
  for (size_t i=0; i<size; i++)
  {
     ptr[i] = right.ptr[i];
  }  
    
  return *this;
}

// ASSIGNMENT ===========================================================

//tilldelningsoperator som tar en initializer_list som parameter.
const Vector &Vector::operator=(const initializer_list<unsigned int> rightlist)
{
  if (ptr != nullptr)
    delete [] ptr;

  size = rightlist.size();
  ptr = new unsigned int[size];

  int i = 0;
  for (auto it=rightlist.begin(); it!=rightlist.end(); ++it)
    ptr[i++] = *it;  //XXX

  return *this;
}   

// MOVE CONSTRUCTOR ====================================================
/**
Move semantics enables you to write code that transfers, "steal", resources 
(such as dynamically allocated memory) from one object to another.
 Move semantics works because it enables resources to be transferred 
from temporary objects that cannot be referenced elsewhere in the program.

To implement move semantics, you typically provide a move constructor, 
and optionally a move assignment operator (operator=), to your class.
Unlike the default copy constructor, the compiler does not provide a 
default move constructor.

By "noexcept" we explicitly tell the library that our move constructor
is safe to use in circumstances such as vector reallocation.
*/

//move-konstruktor:operates by "moving" resources from
//the given object to the object being constructed
Vector::Vector(Vector &&tomove) noexcept
{
  ptr = tomove.ptr;       //assign the class data members from the source 
  size = tomove.size;     //object to the object that is being constructed

  tomove.ptr = nullptr;  //Assign the data members of the source object to 
  tomove.size = 0;       //default values. This prevents the destructor from 
                         //freeing resources (such as memory) multiple times.
} 

// MOVE-OPERATOR ====================================================
//move-operator så att std::move fungerar    
Vector &Vector::operator=(Vector &&source) noexcept
{
  if (this == &source)       //Self-assignment     
    return *this;
  
  if (ptr != nullptr)
    delete[] ptr;
  
  ptr = source.ptr;          // Copy the vector pointer and its  
  size = source.size;        // size from the source object.
  

  source.ptr = nullptr;     // Release the data members from the source 
  source.size = 0;          // object so that the destructor does not 
                            // free the memory multiple times.

  return *this;             // Return a reference to the current object
}

// INDEX OPERATOR =====================================================

//överlagra indexoperatorn [] för snabb åtkomst av elementen
// Overloaded subscript operator for non-const vectors
// reference return creates an lvalue
unsigned int &Vector::operator[](const int subscript)
{
   // check for subscript out of range error
   if ((subscript<0)||(subscript>(int)size-1))
     throw std::out_of_range(" Out of range !");

   return ptr[subscript]; // reference return
} 

// INDEX OPERATOR 2 ===================================================

//operatorn [] som en konstant medlemsfunktion
// Overloaded subscript operator for const vectors
// const reference return creates an rvalue
const unsigned int Vector::operator[](const int subscript) const
{
  // check for subscript out of range error
   if ((subscript<0)||(subscript>(int)size-1))
     throw std::out_of_range(" Out of range !!");

   return ptr[subscript]; // const reference return
} 

// STORLEK =========================================================

size_t Vector::length() const
{
  return size;
} 

// Extra functions utility %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Return number of vector objects instantiated
// static functions cannot be const
int Vector::get_vectorCount()
{
  return vectorCount;
}

//=================================================

  // Overload input operator for class vector;
  // inputs values for entire vector.
istream &operator>> (istream &input, Vector &v)
{
  for (unsigned int i=0; i<v.size; i++)
    input >> v.ptr[i];
  
  return input;   // enables cin >> x >> y;
}

//==================================================
// Overload output operator for class vector
ostream &operator<< (ostream &output, const Vector &v)
{
  unsigned int i;
  for (i=0; i<v.size; i++)
  {  
     output << setw(5) << v.ptr[i];
     if ((i+1) % 3 == 0)  // 3 elements per row
       output << endl;
  }

  if (i % 3 != 0)
    output << endl;

  return output;    // enables cout << x << y;
}

//====================================================
// Determine if 2 vectors are equal and
// return true, otherwise return false.
bool Vector::operator== (const Vector &right) const
{
  if (size != right.size)
    return false;       // vectors of different sizes

  for (unsigned int i=0; i<size; i++)
    if (ptr[i] != right.ptr[i])
      return false;     // vectors are not equal

  return true;          // vectors are equal   
}

//====================================================
/*
int main()
{
  Vector::runTestDriver();
}
*/

