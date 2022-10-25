#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

//#include "Matrix.h"
#include "OurMatrix.h"

//#include "/info/cprog09/cxxtest/cxxtest/TestSuite.h"
#include "/info/DD2387/kurskatalog/cxxtest/cxxtest/TestSuite.h"
//#include "../cxxtest/cxxtest/TestSuite.h"

#include <fstream>
#include <sstream>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        std::stringstream s("  [ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );   
        stream >> m;
    }

public:
    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );   // XXX
/* ASSERTION FAILED
g++ -I /info/DD2387/kurskatalog/cxxtest/ -o runtest03 testcode.cpp Matrix03.o
red-19:~/Desktop/c++prog/lab1/extra1.1>./runtest03
Running 1 test
In MatrixTestSuite::testIndexOperator:
example_test.h:32: Error: Assertion failed: m[ 0 ][ 0 ] == 1
Failed 1 of 1 test
Success rate: 0%
*/

        m = a_matrix_3by2();
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
    }
};

#endif


