/*
 * http://charette.no-ip.com:81/programming/2010-01-03_LibXml2/
 * $Id: 2011-12-24_GCCv47.cpp 290 2012-01-01 01:58:49Z stephane $
 *
 * Example code to demonstrate C++11 delegating constructors in GCC's g++ v4.7.
 *
 * Compiled using g++ v4.7+:
 *
 *		g++ -std=C++11 2011-12-24_GCCv47.cpp
 */


#include <iostream>


class A
{
	public:
		~A( void ) { return; }
		A( const int i );
		A( void );

		int value;
};


A::A( const int i ) :
	value( i )
{
	// this is our normal constructor -- nothing out of the ordinary
	return;
}


A::A( void ) :
	A( 3 )	// delegate the construction to the other constructor of class A;
			// any version of g++ prior to v4.7 will fail to compile this line
{
	// By the time execution reaches here, the object is fully constructed.
	// Even if an exception was thrown at this point, the destructor for A will
	// still be called.
	return;
}


int main( int argC, char *argV[] )
{
	// instantiate an object which happens to use the delegating constructor
	A a;

	// prove that constructor delegation works by printing "a.value"
	std::cout << "a.value == " << a.value << std::endl;

	return 0;
}

