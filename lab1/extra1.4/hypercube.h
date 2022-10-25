#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include <iostream>

#include "vector.h"

// The original template
template<unsigned int N> //N is the dimension of the hypercube
class Hypercube : private Vector< Hypercube<N-1> >{
  public:

    Hypercube(){
        //std::cout << "Hypercube<"<<N<<">::Hypercube()" << std::endl;
    };

    Hypercube (const std::size_t size): 
              Vector< Hypercube<N-1> >(size, Hypercube<N-1>(size)){
    //std::cout << "Hypercube<" << N << ">::Hypercube(size_t size)" << std::endl;
    
    //previous size will not be taken into consideration but dimension must 
    //still be correct, ex. Hypercube<2> m(3); 
                          //Hypercube<4> m2(5); m = m2[0][0]; OK
    };

    using Vector< Hypercube<N-1> >::operator[];
    //operator= will be inherited from Vector class so no need to define it
};

/*  ............................................................................

  NOTE (Lippman p709): Class Template Specializations
  When we can't (or don't want to) use the template version, we can define a 
  specialized version of the class or function template.
*/

// The following defines a SPECIALIZATION of Hypercube for 1u:

template<>				   // we're defining a SPECIALIZATION with
class Hypercube<1> : private Vector<int>{ // the template parameter of 1 (base case)
  public:

    // Default constructor
    Hypercube(){
        //std::cout << "Hypercube<1>::Hypercube()"<<std::endl;
    };

    // constructor with one argument
    Hypercube (const std::size_t i): Vector<int>::Vector(i) {
        //std::cout << "Hypercube<1>::Hypercube(size_t i)"<<std::endl;
    };

    using Vector<int>::operator[];
};

  // NOTE: without specialization can't evaluate array subscripts at compile time

#endif
