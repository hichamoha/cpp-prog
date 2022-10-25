
/*
%%%%%%%%%%%%%%%%%% Uppgift 1.2b

Gör ett nytt test genom att ändra förutsättningarna så att funktionen must_follow_a
förväntas returnera två. 
För att automatisera testgenereringen kan du använda make genom att lägga till en ny regel i din makefile.

Funktionen är medvetet buggig och kan leta utanför det givna intervallet.
Denna typen av fel där man räknat fel på ett brukar kallas “off by one”. Gör
ännu ett nytt test där funktionen fallerar. Använd följande förutsättningar:
	vek = {’b’, ’b’, ’a’, ’b’, ’b’};"
	must_follow_a(vek, 3, ’a’, ’b’)

Om funktionen hade fungerat som det var tänkt borde man inte få någon
teckenföljdsförekomst. Redovisa minst tre testfunktioner vid redovisningen.

Varför är det så viktigt att testa randvillkoren?

*/

#include <cxxtest/TestSuite.h>

#include "must_follow_a.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:

    // Testcase 1

    // This testcase sets up a 5 sized array (precondition). Note that
    // the second argument (length) to must_follow_a is 4. The
    // expected result is successs.

    // Do make additional tests of your own and try it out. 

    void test_a_is_second_to_last( void )
    {
        char vek[] = {'x', 'x', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 1);
    }
  
     void test_a_is_second_to_last_case1( void )
     {//ingen teckenföljd

        char vek[] = {'b','b','b','b','a'};
        int result = must_follow_a(vek,5,'a','b');
        TS_ASSERT_EQUALS( result, 0);
     } 

    void test_a_is_second_to_last_case2( void )
    {
        char vek[] = {'a', 'b', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 2);
     }

     void test_a_is_second_to_last_case3( void )
     {
        char vek[] = {'b', 'b', 'a', 'b', 'b'};
        int result = must_follow_a(vek, 3, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0);
     }

     void test_is_second_to_last_case4( void )
     { //1 teckenföljd
        char vek[] = {'b','b','a','b','a'};
        int result = must_follow_a(vek,5,'a','b');
        TS_ASSERT_EQUALS( result, 1);
     }
};
