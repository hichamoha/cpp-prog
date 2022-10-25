/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test_must_follow_a.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test_must_follow_a.cpp", 26, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_a_is_second_to_last : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 38, "test_a_is_second_to_last" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last(); }
} testDescription_MyTestSuite_test_a_is_second_to_last;

static class TestDescription_MyTestSuite_test_a_is_second_to_last_case1 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last_case1() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 45, "test_a_is_second_to_last_case1" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last_case1(); }
} testDescription_MyTestSuite_test_a_is_second_to_last_case1;

static class TestDescription_MyTestSuite_test_a_is_second_to_last_case2 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last_case2() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 53, "test_a_is_second_to_last_case2" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last_case2(); }
} testDescription_MyTestSuite_test_a_is_second_to_last_case2;

static class TestDescription_MyTestSuite_test_a_is_second_to_last_case3 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last_case3() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 60, "test_a_is_second_to_last_case3" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last_case3(); }
} testDescription_MyTestSuite_test_a_is_second_to_last_case3;

static class TestDescription_MyTestSuite_test_is_second_to_last_case4 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_is_second_to_last_case4() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 67, "test_is_second_to_last_case4" ) {}
 void runTest() { suite_MyTestSuite.test_is_second_to_last_case4(); }
} testDescription_MyTestSuite_test_is_second_to_last_case4;

#include <cxxtest/Root.cpp>
