

#include <iostream>
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

#include <vector>
#include <memory>
 
class A {
public:
 
  void tellSomething() {
      std::cout << " \n\t A!" << std::endl;
      //return "foo";
  }

  A() {
      std::cout << " \n\t constructor" << std::endl;
  }

 
  ~A() {
      std::cout << " \n\t Destructor" << std::endl;
  }

};

// ...................................................
 /* let's consider a pointer to a dynamically allocated vector 
    which contains pointers to dynamically allocated objects. */

//int main(int argc, const char *argv[])
int main()
{
    // create the vector of pointers
    std::unique_ptr<std::vector<std::unique_ptr<A>>> v(new std::vector<std::unique_ptr<A>>);
    //std::vector<A *>* v = new std::vector<A *>;
 
    // create 2 objects
    std::unique_ptr<A> a1(new A);
    //A *a1 = new A;
    std::unique_ptr<A> a2(new A);
    //A *a2 = new A;
 
    a1->tellSomething();

    // populate the vector 
    //v->push_back(a1);          // push_back() stores a copy of the pointer returned by new XXX
    v->push_back(std::move(a1)); // we need to use move() because unique_ptr is not copyable
    //v->push_back(a2);   
    v->push_back(std::move(a2));
 
    // delete the vector XXX
    // NOTE: Here for iteration does not needed, it make it worse!..we can deallocate the memory 
    // for vector by calling clear() and then 'delete'...'for' make other memory leaks. 
  
    //for (std::vector<A *>::iterator it = v->begin(); it != v->end(); ++it) {
    //        delete *it;
    //} 
    
    //v->clear(); //clear() deletes all the elements in the vector, so it deletes only  
                  //the pointers but the objects themselves stay in memory.

    //delete v;
    
 
    // try accessing one of the objects
    a1->tellSomething();

    //std::cout << "\n\t " << v->size() << std::endl; // FIXME 2 'invalide read' errors

    //delete a1; delete a2;

     
    return 0;
}

	// standard input is empty
	// stdout:
          // A!
          // A!



/* Introduction: Containers and Smart pointers

   The problem with using pointers to objects is that the object 'leaks' if it is not 
   deleted when the last pointer to it goes out of scope, or its data structure containing 
   it is itself deleted.
   The existing STL containers already memory manage their contents - for example, when a 
   vector goes out of scope, its destructor will deallocate its contents. However, there are
   some situations where you need to store pointers, not objects, in containers. Container 
   classes will not deallocate those. These are the situations wher a smart pointer is needed.
   
   To illustrate this need, here's my top three situations where smart pointers are required:
   # Reason 1 - C++ Polymorphism Must be Implemented as Pointers to Objects  
   	base* b = new derived;
   	b->print(); // actually calls derived::print

   The reason that you must use pointers here is that classes base and derived could be of
   different sizes - so you cannot assign a derived to a variable of type base. This rule is
   enforced by C++. However, you can assign a (derived*) to a (base*) as in the example. 
   Thus, pointers have to be used to implement polymorphism in C++. 

   # Reason 2 - Minimising Reallocation Overhead

   The vector is one of the most useful template classes in the STL. It has one potential
   problem: when a vector has to resize, it does so by copying all of its contents into 
   a new vector. It does so by using the copy constructor of the contained type. 
   Therefore a vector of 1000 objects results in 1000 calls to the copy constructor.

   This is not itself a problem if the constructor is trivial since the call overhead is 
   negligible. However, if the type stored in the vector is big and/or complicated, then 
   the copy overhead can become serious. Storing a pointer to the object in the vector is 
   not a good idea - the memory will then not be managed by the vector. The solution is to 
   use a vector of smart pointers to objects. Then, when the vector resizes, it copies the 
   smart pointer, not the object. Then, when the vector is destroyed, its contents - smart 
   pointers - are destroyed and they in turn delete their contained objects.

   # Reason 3 - Returns Must be Implemented as Pass-by-Value

   It is often useful to write functions that create data structures and return them. 
   However, there are problems with this.

   Passing back a reference to a local (automatic) variable is illegal, since the variable 
   is destroyed in the return so that the reference returned now refers to destroyed memory. 
   This is a well-known pitfall in C++.

   Creating the object with new and passing back a pointer to the object seems to be a good 
   solution. The problem with this is that the returned value is not memory managed and will 
   leak in the case of an exception being thrown. It can also make code difficult to read 
   and debug because the place where the data structure is allocated is a very different place
   to where it is destroyed. 
   This separation of new and delete is a well-known source of memory bugs - inevitably the 
   question of which part of the program is responsible for the deallocation becomes confused 
   and you can end up with either leaky code or double-deletion and the memory corruption that 
   results.
   
   If you return by value, this causes a copy constructor to be called. This is fine for small 
   data structures where the copy overhead is correspondingly small, but it is undesirable if 
   the data staructure is big and impossible if the data structure cannot be copied (occasionally 
   it is necessary to design data structures that are not copiable).

   The solution is to create the object in a smart pointer and return it by value. Pass by value 
   with a smart pointer just creates an alias and so has negligible overhead. However, the smart 
   pointer is managing the object's memory, so the program does not need to remember to delete it 
   later. It will delete itself when it is no longer in use.

				Unique Ownership with unique_ptr
   The basic mechanism of unique_ptr is so simple that it costs nothing to use. Second, unique_ptr
   implements a unique ownership concept - an object can be owned by only one unique_ptr at a time 
   - the opposite of shared ownership.
 
   ### What makes the ownership unique?
   An object is owned by exactly one unique_ptr. The unique ownership is enforced by disallowing
   (with =delete) copy construction and copy assignment. So unlike built-in pointers or shared_ptr, 
   you can't copy or assign a unique_ptr to another unique_ptr.

   Notice that since copy construction is disallowed, if you want to pass a unique_ptr as a function
   argument, you have to do it by reference.
   A couple of additional goodies: You can test a unique_ptr to see if it owns an object (e.g. with
   if(p) ); there is a conversion to bool that supplies the value of the pointer member variable as 
   true/false. If you want to delete the object manually, call the reset() function – this does the
   delete and then resets the internal pointer to nullptr.

   Transferring ownership
   While unique_ptr is defined to help you avoid ambiguous ownership, it might be handy to transfer
   ownership of an object from one unique_ptr to another.  This is easily done with move semantics: 
   the move constructor and move assignment operator are defined for unique_ptr so that they transfer
   ownership from the original owner to the new owner.  
   Remember that the returned value of a function is a rvalue, so the presence of move construction 
   and assignment means that we can return a unique_ptr from a function and assign it to another 
   unique_ptr; the effect is that ownership of the object is passed out of the function into the 
   caller's unique_ptr. 
   Thus ownership can be transferred implicitly from an rvalue unique_ptr , but not from an lvalue
   unique_ptr.
 */

   				



