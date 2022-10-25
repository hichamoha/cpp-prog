//%%%%%%%%%%%%%%%%%%%% 1.5 Templates(mallar) 

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
//#include <cstring>
//#include <iomanip>
#include <iterator>
//#include <iostream>
//#include <cstddef>    //size_t type is defined in the cstddef header
#include <initializer_list> 
//#include <cassert>
#include <algorithm>  // to call find() and sort(begin, end)

//using namespace std;

template <typename T>
class Vector
{ 
  public:
    /*
    // Funktionsobjekt(Functor): less_than()
    // Functor är objekt som imiterar syntaxen hos en funktion
       The function-object classes that represent operators (here <) are often  
       used to override the default operator used by an algorithm (i.e. sort()).
    */   
/*    struct less_than
    {
      bool operator()(T x, T y)
      {   
         return x < y; 
      }
    };
*/   
// Default constructor
    Vector();    

// Other constructor(size)  
    explicit Vector(const size_t size); 

// Other constructor(size, init), initialize to default value for all elements 
    Vector(const size_t size, T init);                                            

// kopieringskonstruktor.
    Vector(const Vector<T> &);
    
    //init list copy constructor{1,2,3,...}
    Vector(const std::initializer_list<T> &);

// Destructor     
    ~Vector();                 

// Assignment operator
    Vector<T>& operator=(const Vector<T> &);
 
    //tilldelningsoperator som tar en initializer_list som parameter.
    Vector<T>& operator=(const std::initializer_list<T> ); 
 

//move-konstruktor och move-operator så att std::move fungerar.
    Vector(Vector<T> &&);
  
    Vector<T>& operator=(Vector<T> &&);


//överlagra indexoperatorn [] för snabb åtkomst av elementen
    T& operator[](const int ); 

//operatorn [] som en konstant medlemsfunktion
    const T& operator[](const int ) const; 

// ====== Ny funktionalitet i klassen  Vector ===================
    //bool less_than (const T&, const T&);
    void push_back(const T&); 
    void insert(const size_t i, const T& );
    void erase(const size_t i); 
    void clear(); // ta bort alla element 
    size_t size() const; 
    void sort(bool ascending = true);
    bool exists(const T& );

  private: 
    size_t nbElements; // the logical size: nb of elements it ALREADY holds 
    size_t capacity; // the maximum possible size (max nb of elements can hold)  
 	
    T *ptr;       // pointer to the first element 
    //static int vectorCount;  // # of vectors instantiated
    
    void extend_vec (const size_t sz);  // to expand the vector 

};

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%% Cpp Implementation code %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
A central problem in programming is the fixed size of arrays. This problem can be avoided by dynamically allocating vectors. The way to handle this is to make the vector bigger: Expanding the vector.

Geometric expansion and amortized cost:
To avoid incurring the cost of resizing many times, dynamic arrays resize by a large amount, such as doubling in size, and use the reserved space for future expansion.
*/

// resize vector (Ridimensionamento)
// Strategy of DOUBLING of the current capacity
template <typename T>
  void Vector<T>::extend_vec(const size_t sz)
{   
  if (capacity>0)
  {
     T *temp = ptr;
     // capacity is the real size of the allocated memory
     capacity += sz;  // double the previous allocated memory
    
     ptr = new T[capacity]; // create the new extended vector(memory allocation)
     
     if (temp != nullptr)
     {
     for (size_t i=0; i<nbElements; i++)  // copy the elements from the old memory
       ptr[i] = temp[i];

     delete[] temp; // deallocation of the old memory
     }
  }else
   {
      ptr = new T[sz];
      capacity = sz;  
   }
}  

// # Old Definitions

//========================================== DEFAULT CONSTRUCTOR
// Defaultkonstruktorn ska skapa en tom vektor. 
template <typename T>
  Vector<T>::Vector()    
{
  nbElements = 0;  //nb of elements it ALREADY holds 
  capacity = 0;    // the max nb of elements can hold 
  ptr = nullptr;
}

//============================================ OTHER CONSRUCTOR 
//Om man anger en storlek till konstruktorn ska elementen 
//initieras till defaultvärdet för typen (tilldela värdet T() till elementen).
// Other constructor(size, initialize to t()) 
template <typename T>   
  Vector<T>::Vector(const size_t size) : capacity(0)
{
  extend_vec(size);  // Expand the vector to a new size
  nbElements = capacity;
  
  for (size_t i=0; i<size; i++) //for (auto i : v) // C++11
    ptr[i] = T();               //elementen initieras till defaultvärdet för T
}

//==================================== CONSTRUCTOR WITH 2 ARGUMENTS
// Other constructor(size, init) 
// initialize all elements to a default value  
    
template <typename T>   
  Vector<T>::Vector(const size_t size, T init) : capacity(0)
{ 
  extend_vec(size);  // Expand the vector to a new size
  nbElements = capacity;   // resize the vector 

  for (size_t i=0; i<size; i++) //for (auto i : v) // C++11
    ptr[i] = init;              //elementen initieras till ett defaultvärdet 
}
 
// =============================================== COPY CONSTRUCTOR
                                          
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
template <typename T>  
  Vector<T>::Vector(const Vector<T> &copia) : capacity(0)  
{
  nbElements = copia.nbElements;
  extend_vec(nbElements);     // expand vector if it is necessary 

  for (size_t i=0; i<nbElements; i++)
  { 
    ptr[i] = copia.ptr[i];         //copy copia into object
    //nbElements++;
  } 
}

//  ============================================ EXTRA COPY CONSTRUCTOR
// initializer_list copy constructor: {1,2,3,...}  
template <typename T>    
  Vector<T>::Vector(const std::initializer_list<T> &il) : capacity(0) 
{
  nbElements = il.size();
  extend_vec(nbElements);     // Expand vector if it is necessary
 
  /**
  begin and end return iterators of type 
  initializer_list<size_t>::iterator
  c++11 standard: auto iter = il.begin()
  */
  //typename initializer_list<T>::iterator iter;
  int i = 0;    
  for (auto iter=il.begin(); iter!=il.end(); ++iter)
  {
     ptr[i++] = *iter;
     //nbElements++;
  }   
}

// ====================================================== DESTRUCTOR 
template <typename T>
  Vector<T>::~Vector()
{
  if (ptr != nullptr)
    delete[] ptr;
} 

// OVERLOADING =======================================================
/**
############    Overloading di Operatori

• Perché un operatore possa operare su gli oggetti di
  una classe deve necessariamente essere ridefinito
• fanno eccezione:
   – operatore di assegnamento =
     il suo comportamento di default è di eseguire una copia di
     membro a membro dei dati di una classe
   – operatore di indirizzo &
     il suo comportamento di default è di restituire l’indirizzo di
     memoria dell’oggetto
• tuttavia anche = e & possono essere ridefiniti se
  serve
*/
// ========================================== ASSIGNMENT OPERATOR                 
// const return avoids: (a1 = a2) = a3
template <typename T>
  Vector<T> &Vector<T>::operator=(const Vector<T> &right)
{
  if (&right == this)   //check for self-assignment
      return *this;     //same object
  
  //for vector of different sizes, deallocate original
  //left side vector then allocate new left side vector
  
  clear();
  nbElements = right.nbElements;
     
  extend_vec(nbElements);  // Expand the vector to a new size
     
  for (size_t i=0; i<nbElements; i++)
  {   
     ptr[i] = right.ptr[i];
     //nbElements++;
  }
  //extend_vec();
    
  return *this;
}

//  ======================================== ASSIGNMENT {x1,x2,x3...}
//tilldelningsoperator som tar en initializer_list som parameter.
template <typename T>
  Vector<T> &Vector<T>::operator=(const std::initializer_list<T> rightlist)
{
  clear();

  nbElements = rightlist.size();
  extend_vec(nbElements);  // Expand the vector to a new size
  
  //typename initializer_list<T>::iterator iter;
  int i = 0;
  for (auto it=rightlist.begin(); it!=rightlist.end(); ++it)
  {
    ptr[i++] = *it;
    //nbElements++;
  }
  //extend_vec();
  
  return *this;
}   

//================================================== MOVE CONSTRUCTOR
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
template <typename T>
  Vector<T>::Vector(Vector<T> &&tomove) : capacity(0)
{
  ptr = tomove.ptr;           //assign the class data members from the source 
  capacity = tomove.nbElements; //object to the object that is being constructed
  nbElements = tomove.nbElements;
  
  //extend_vec();

  tomove.ptr = nullptr;  //Assign the data members of the source object to 
  tomove.nbElements = 0;   //default values. This prevents the destructor from 
                         //freeing resources (such as memory) multiple times.
} 

//================================================== MOVE-OPERATOR
//move-operator så att std::move fungerar 
template <typename T>   
  Vector<T> &Vector<T>::operator=(Vector<T> &&source)
{
  if (this == &source)       //Self-assignment     
    return *this;
  
  if (ptr != nullptr)
    delete[] ptr;
  
  ptr = source.ptr;           // Copy the vector pointer and its  
  capacity = source.nbElements; // size from the source object.
  nbElements = source.nbElements;

  //extend_vec();
  

  source.ptr = nullptr;     // Release the data members from the source 
  source.nbElements = 0;      // object so that the destructor does not 
                            // free the memory multiple times.

  return *this;             // Return a reference to the current object
}

// ===================================================== INDEX OPERATOR
//överlagra indexoperatorn [] för snabb åtkomst av elementen
// Overloaded subscript operator for non-const vectors
// reference return creates an lvalue
template <typename T>
  T &Vector<T>::operator[](const int subscript)
{
   // check for subscript out of range error
   if ((subscript<0)||(subscript>=(int)nbElements))
     throw std::out_of_range(" Out of range !");

   else return ptr[subscript]; // reference return
} 

// =================================================== INDEX OPERATOR 2
//operatorn [] som en konstant medlemsfunktion
// Overloaded subscript operator for const vectors
// const reference return creates an rvalue
template <typename T>
  const T& Vector<T>::operator[](const int subscript) const
{
  // check for subscript out of range error
   if ((subscript<0)||(subscript>=(int)nbElements))
     throw std::out_of_range(" Out of range !!");

   else return ptr[subscript]; // const reference return
} 


//%%%%%%%%%%%%%%%%%% New Definitions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// ===================================================== push_back(T) 
// lägger till ett element sist i vektorn. 
// Det ska för det mesta ske i konstant tid.
/*
Every implementation is required to follow a strategy that ensures that it is 
efficient to use push_back to add elements to a vector.
The execution time of creating an n-element vector by calling push_back n times 
on an initially empty vector must never be more than a CONSTANT MULTIPLE  of n.

This effectively increases the vector size by one, which causes a reallocation 
of the internal allocated storage if the vector size was equal to the vector 
capacity before the call. 
*/
template <typename T>
  void Vector<T>::push_back(const T& element)
{ 
  if (nbElements==capacity)
  { 
    extend_vec(100);
    //assert (nbElements<capacity);
   
  }
   ptr[nbElements] = element;
   nbElements++; 
  //extend_vec();
}  

//========================================================== insert()
// insert(size_t i, T) lägger till ett element före plats i. Om i är lika
// med antal element i vektorn fungerar metoden som push_back.
template <typename T>
  void Vector<T>::insert(const size_t position, const T& element)
{
  //assert (nbElements<capacity);
  if ((position<0) || (position>nbElements))
    throw std::out_of_range(" Out of range !");
  
  if (capacity == nbElements)
    extend_vec(100);
 
  for (size_t i=nbElements; i>position; i--)
  {
     ptr[i] = ptr[i-1];   // Decale les elements vers le haut
  }
    
  ptr[position] = element;
  nbElements++;
  
  //extend_vec();
}  

//========================================================== erase()
// erase(size_t i) tar bort ett element på plats i
template <typename T>
  void Vector<T>::erase(const size_t position)
{
   //assert (nbElements != 0); 
   if ((position<0) || (position>=nbElements))
      throw std::out_of_range(" Out of range !");

   nbElements--;
   for (size_t i=position; i<nbElements; i++)
  {
     ptr[i] = ptr[i+1];   // Decale les elements vers le bas
  }
  //nbElements--;
}

//======================================================== clear()
//clear() tar bort alla element
template <typename T>
  void Vector<T>::clear()
{
  if (ptr != nullptr)
  {
    delete [] ptr; 
    ptr = nullptr;     
  }
  nbElements = capacity = 0; 
}

//======================================================== size()
// size() ger antal element i vektorn.
template <typename T>
  size_t Vector<T>::size() const
{
    return nbElements;
}   

//======================================================== sort()
/*
A call to sort() arranges the elements in the input range into sorted order using the element type's < operator.
sort() is not stable: equivalent elements that are ordered one way before sorting may be ordered differently after sorting.
*/
// sort(bool ascending = true) sorterar vektorn i angiven riktning på
// enklast möjliga sätt. Använd std::sort (datatyper som ska jämföras måste
// definiera operator<.)
template <typename T>
  void Vector<T>::sort(const bool ascending)
{
  if (nbElements < 2)
    return;
  
  std::sort(&ptr[0], &ptr[nbElements]);  // call to std::sort()

  //bool (*foo)(const T&, const T&);   // function pointer declaration
  //foo = less_than;
  //std::sort(&ptr[0], &ptr[nbElements], foo); 

  //std::sort(&ptr[0], &ptr[nbElements], less_than(const T&, const T& )); // why didn't work ?
  //std::sort(&ptr[0], &ptr[nbElements], less_than()); // functor less_than()
  // Overloaded version of sort()
  //this version of sort takes a third argument that is a predicate
      
  if (ascending == false)
  {
     T* temp = new T[capacity];

     for (size_t i=0; i<nbElements; i++)
       temp[nbElements-i-1] = ptr[i];

     delete [] ptr;
     ptr = temp;   
  }   

}

//======================================================== exists()
// exists(const T &) Returnerar true om elementet finns i vektorn annars
// false. Använd std::find för att implemtera funktionen.
template <typename T>
  bool Vector<T>::exists(const T& val)
{
  if (nbElements == 0)
    return 0;

  T* result = find(&ptr[0], &ptr[nbElements], val);

  return (result != ptr[nbElements]);  
}

#endif 
