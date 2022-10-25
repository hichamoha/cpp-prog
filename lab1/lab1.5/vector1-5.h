#ifndef VECTOR_H
#define	VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <algorithm>

template <class T>
class Vector
{
public:
  explicit Vector(); //Konstruktor utan parametrar default

  explicit Vector(const size_t size); //konstruktor m bara storlek. 
                                      //init till T() därnere
  //konstruktor som tar storlek och init värde 
  explicit Vector(const size_t size, T init); 
	
 //kopierings konstruktor
  Vector(const Vector<T>& source);

  //Konstruktor som tar emot en lista {x,x2,x3,....} 
  Vector(const std::initializer_list<T>& list);
 
  Vector(Vector<T>&& other); // move konstruktor
  ~Vector(); // destruktor
        
//Operator overload
  T& operator[](const int i); //bracket [] overload
  const T& operator[](const int i) const; //bracket [] overload
        
  Vector<T>& operator=(Vector<T>&& other); //move assignment

  // = {x1,x2,x3...} assignment
  Vector<T>& operator=(const std::initializer_list<T> list); 
  Vector<T>& operator=(const Vector<T>& rhs); // v1=v2 assignment 
        
// Nya funktioner
  void push_back(const T& var); //konstant tid??
  void insert(const size_t pos,const T& var);
  void erase(const size_t pos); // ta bort element på "i"
  void clear(); // ta bort alla element 
  size_t size() const; // hur stor
  void sort(bool ascending = true);
  bool exists(const T& var);
       
private:
  T* data;
  size_t vec_size;
  size_t tot_size;
        
  void expand_vector(const size_t amount);
        
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%% cpp implementation kod %%%%%%%%%%%%%%%%%%%%%%

//Konstruktor utan parametrar ==================================
template <class T>    
  Vector<T>::Vector() 
{
   vec_size = 0; 
   tot_size = 0;  
   data = NULL; 
}
        
//konstruktor som tar bara storlek. init med T() ===============
template <class T> 
  Vector<T>::Vector(const size_t size) : tot_size(0)
{
  expand_vector(size);
  vec_size = tot_size;

  for (int i=0; i<size;i++)
    data[i] = T();
}

//konstruktor som tar storlek och init värde =================== 
template <class T>    
  Vector<T>::Vector(const size_t size, T init) : tot_size(0)
{
  expand_vector(size);
  vec_size = tot_size;

  for (size_t i=0; i<size; i++) 
    data[i] = init;
}

//kopierings konstruktor ======================================
template <class T>    
  Vector<T>::Vector(const Vector<T>& other) : tot_size(0)
{
  vec_size = other.vec_size;
  expand_vector(vec_size);

  for (size_t i=0; i<vec_size; i++) 
    data[i] = other.data[i];
}
        
//Konstruktor som tar emot en lista {x,x2,x3,....} ===========
template <class T>    
  Vector<T>::Vector(const std::initializer_list<T>& list) : tot_size(0)
{
  vec_size=list.size();
  expand_vector(vec_size);
  typename std::initializer_list<T>::iterator it;

  int i=0;
  for ( it=list.begin(); it!=list.end(); ++it)
    data[i++]=*it;
}

// move konstruktor =========================================
template <class T>    
Vector<T>::Vector(Vector<T>&& rhs) : tot_size(0)
{
  data = rhs.data;
  tot_size = vec_size = rhs.vec_size;
  rhs.data = NULL; //annars tar destruktorn på den andra bort minnet
  rhs.vec_size = 0;
}

// destruktor =============================================
template <class T>
Vector<T>::~Vector()
{
  if (data!=NULL) 
    delete [] data;
}

//Operator overload =====================================
//Bracket [] overload
template <class T>
T& Vector<T>::operator[](const int i)
{
  if (i<0||i>=(int)vec_size) 
    throw std::out_of_range("Out of range"); 
  
  else return data[i];
}

//Bracket [] overload 2 ================================        
template <class T>
const T& Vector<T>::operator[](const int i) const
{
  if (i<0||i>=(int)vec_size) 
    throw std::out_of_range("Out of range"); 
  else return data[i];
}
        
//move assignment ======================================
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
  if (this == &other) 
    return *this;

  // ta bort data vi har.
  if (data!=NULL)
    delete [] data;

  // Kopiera datapekare och storlek
  data = other.data;
  tot_size = vec_size = other.vec_size;
  // rensa den andras datapekare och storlek
  other.data=NULL; //Annars tar den andra destruktorn bort minnet
  other.vec_size = 0;

  return *this;
}
        
// = {x1,x2,x3...} assignment ===================================
template <class T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T> list)
{
  clear();
  vec_size=list.size();
  expand_vector(vec_size);
  typename std::initializer_list<T>::iterator it; // same as: const int* it

  int i=0;
  for ( it=list.begin(); it!=list.end(); ++it)
    data[i++]=*it;

  return *this;
}

//v1=v2 assignment ================================================
template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& source) {
  if (this == &source)
    return *this;    // samma object?

  clear();
  vec_size = source.vec_size; //storleken på vektorn
  expand_vector(vec_size);// else data=new T[1]; //allokera

  for (int i=0; i<vec_size; i++)
    data[i] = source.data[i]; //kopiera
   
  return *this;
}
        
//%%%%%%%%%%%%% Nya Funktioner %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// push_back()=========================================
template <class T>
void Vector<T>::push_back(const T& var)
{
  //vec_size++;
  if (vec_size==tot_size) {
    expand_vector(100);
  }

  data[vec_size] = var;
  vec_size++;
}

//%%%%%%%%%%  expand_vector() =========================       
template <class T>
  void Vector<T>::expand_vector(const size_t amount)
{
  //flytta hit all expanderings kod
  if (tot_size>0) 
  { 
    // must copy stuff
    T* tmp_data = data;

    tot_size += amount;
    data = new T[tot_size];

    if (tmp_data!=NULL) 
    {
      for (size_t i=0; i<vec_size; i++)
        data[i] = tmp_data[i];
       
      delete [] tmp_data;
    }

  }else 
    {  data = new T[amount]; 
       tot_size = amount; 
    }
}

// insert() ==========================================        
template <class T>
void Vector<T>::insert(const size_t pos,const T& var)
{
  if (pos<0||pos>vec_size)
    //1999 ISO C standard size_t är unsigned int. 
    //behöver inte kolla <0 egentligen 
    throw std::out_of_range("Out of range"); 

  if (tot_size==vec_size) 
    expand_vector(100);
            
  for (size_t i=vec_size; i>pos; i--)
    data[i] = data[i-1];

  data[pos] = var;
  vec_size++;
}

// erase() =============================================       
template <class T>
  void Vector<T>::erase(const size_t pos) // ta bort element på "pos"
{
  if (pos<0||pos>=vec_size)
    throw std::out_of_range("Out of range");

  vec_size--;
  for (size_t i=pos; i<vec_size; i++) 
    data[i] = data[i+1];
}

// clear() ==========================================       
template <class T>
void Vector<T>::clear() // ta bort alla element 
{
  if (data!=NULL)
  {  
    delete [] data; 
    data = NULL;
  }
    tot_size = vec_size = 0;
}

// size() =============================================       
template <class T>
  size_t Vector<T>::size() const // hur stor
{
  return vec_size;
}

// sort() ==========================================        
template <class T>
  void Vector<T>::sort(const bool ascending)
{
  if (vec_size<2) 
    return; //är vi 0 eller 1 är vi redan sorterade.

  //else std::sort(data,data+c,revSortOrder<T>);          
  std::sort(&data[0],&data[vec_size]); 
            
  if (ascending == false) 

  {
    T* tmp_data = new T[tot_size];

    for (size_t i=0;i<vec_size;i++)
      tmp_data[vec_size-i-1] = data[i];

    delete [] data;
    data = tmp_data;
  }
}

// exists() ============================================       
template <class T>
bool Vector<T>::exists(const T& var)
{
  if (vec_size==0)
    return 0;
   
  T* p = std::find(&data[0],&data[vec_size],var);
  // p inte sista elementet så fanns den =true annars false

  // return (p != data + vec_size);
  return (p != data[vec_size]); 
}
        
#endif	/* VECTOR_H */

