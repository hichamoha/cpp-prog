
#include "template_vector.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iomanip>

using namespace std;


// initialize static data member at file scope
//int Vector<T>::vectorCount = 0;   // no obects yet
int vectorCount = 0;   // no obects yet

int get_vectorCount()              // friend function
  //int Vector<T>::get_vectorCount()
{
  return vectorCount;
}

// TESTING DRIVER ===========================================
//void Vector<T>::runTestDriver()
void runTestDriver()
{ 
   // 1) no objects yet
   cout << "\n TEST 1: # of vectors instantiated = "
        //<< Vector::get_vectorCount() << '\n';
        << get_vectorCount() << '\n'; 

   // 2) create two vectors and print vector count
   Vector<int> v1( 7 ), v2;
   cout << "\n TEST 2: # of vectors instantiated = "
        << get_vectorCount() << "\n\n";

   // 3) print v1 size and contents
   cout << " TEST 3: Size of vector v1 is "
        << v1.size()
        << "\n vector after initialization:\n"
        << v1 << '\n';

   // 4) print v2 size and contents
   cout << " TEST 4: Size of vector v2 is "
        << v2.size() << '\n';   
        //<< "\n vector after initialization:\n"
        //<< v2 << '\n';

   // 5) create v3 using v1 as an
   // initializer; print size and contents
   Vector<int> v3(3);
   cout << "\n TEST 5: Size of vector v3 is " << v3.size()
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
   Vector<int> v4(v1);
   cout << "\n TEST 8: Size of vector v4, using v1 as initializer is: " 
        << v4.size()
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
//===================================================================

   v1.push_back(3);          // lägg till ett element sist
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 
   cout << " Size of vector v1 is "
        << v1.size() << '\n';
 
   v1.insert(0, 2); 
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 
   cout << " Size of vector v1 is "
        << v1.size() << '\n';

   v1.sort(true);              // sortera i fallande ordning 
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 
   cout << " Size of vector v1 is "
        << v1.size() << '\n'; 
 
   v3.sort(false);              // sortera i fallande ordning 
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 
   cout << " Size of vector v2 is "
        << v2.size() << '\n'; 

   v3.insert(3, 4);          // lägg till ett element sist
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 
   cout << " Size of vector v3 is "
        << v3.size() << '\n'; 
///*
   v3.erase(3); 
   cout << " v1:\n" << v1 
        << " v3:\n" << v3 << '\n'; 
   cout << " Size of vector v3 is "
        << v3.size() << '\n';
//*/ 
//===================================================================   
  // 12) attempt to use out of range subscript
   cout << "\n TEST 12: Attempt to assign 1000 to v1[15]" << endl;
   v1[15] = 1000;  // ERROR: out of range
   
}


int main()
{
  //Vector<T>::runTestDriver();
  runTestDriver();
}

