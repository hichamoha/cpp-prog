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
#include "our_tests.cpp"

static VectorTestSuite suite_VectorTestSuite;

static CxxTest::List Tests_VectorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VectorTestSuite( "our_tests.cpp", 51, "VectorTestSuite", suite_VectorTestSuite, Tests_VectorTestSuite );

static class TestDescription_VectorTestSuite_test_1_constructors : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_1_constructors() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 73, "test_1_constructors" ) {}
 void runTest() { suite_VectorTestSuite.test_1_constructors(); }
} testDescription_VectorTestSuite_test_1_constructors;

static class TestDescription_VectorTestSuite_test_2_assignment : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_2_assignment() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 89, "test_2_assignment" ) {}
 void runTest() { suite_VectorTestSuite.test_2_assignment(); }
} testDescription_VectorTestSuite_test_2_assignment;

static class TestDescription_VectorTestSuite_test_3_index : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_3_index() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 107, "test_3_index" ) {}
 void runTest() { suite_VectorTestSuite.test_3_index(); }
} testDescription_VectorTestSuite_test_3_index;

static class TestDescription_VectorTestSuite_test_4_index_ref : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_4_index_ref() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 128, "test_4_index_ref" ) {}
 void runTest() { suite_VectorTestSuite.test_4_index_ref(); }
} testDescription_VectorTestSuite_test_4_index_ref;

static class TestDescription_VectorTestSuite_test_5_out_of_bounds : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_5_out_of_bounds() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 153, "test_5_out_of_bounds" ) {}
 void runTest() { suite_VectorTestSuite.test_5_out_of_bounds(); }
} testDescription_VectorTestSuite_test_5_out_of_bounds;

static class TestDescription_VectorTestSuite_test_6_copy_constructor : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_6_copy_constructor() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 189, "test_6_copy_constructor" ) {}
 void runTest() { suite_VectorTestSuite.test_6_copy_constructor(); }
} testDescription_VectorTestSuite_test_6_copy_constructor;

static class TestDescription_VectorTestSuite_test_7_assignment_operator : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_7_assignment_operator() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 219, "test_7_assignment_operator" ) {}
 void runTest() { suite_VectorTestSuite.test_7_assignment_operator(); }
} testDescription_VectorTestSuite_test_7_assignment_operator;

static class TestDescription_VectorTestSuite_test_8_changes_to_copies : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_8_changes_to_copies() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 256, "test_8_changes_to_copies" ) {}
 void runTest() { suite_VectorTestSuite.test_8_changes_to_copies(); }
} testDescription_VectorTestSuite_test_8_changes_to_copies;

static class TestDescription_VectorTestSuite_test_9_defaults : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_9_defaults() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 281, "test_9_defaults" ) {}
 void runTest() { suite_VectorTestSuite.test_9_defaults(); }
} testDescription_VectorTestSuite_test_9_defaults;

static class TestDescription_VectorTestSuite_test_10_custom_defaults : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_10_custom_defaults() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 302, "test_10_custom_defaults" ) {}
 void runTest() { suite_VectorTestSuite.test_10_custom_defaults(); }
} testDescription_VectorTestSuite_test_10_custom_defaults;

static class TestDescription_VectorTestSuite_test_11_push_back : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_11_push_back() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 318, "test_11_push_back" ) {}
 void runTest() { suite_VectorTestSuite.test_11_push_back(); }
} testDescription_VectorTestSuite_test_11_push_back;

static class TestDescription_VectorTestSuite_test_12_insert : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_12_insert() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 339, "test_12_insert" ) {}
 void runTest() { suite_VectorTestSuite.test_12_insert(); }
} testDescription_VectorTestSuite_test_12_insert;

static class TestDescription_VectorTestSuite_test_13_erase : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_13_erase() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 382, "test_13_erase" ) {}
 void runTest() { suite_VectorTestSuite.test_13_erase(); }
} testDescription_VectorTestSuite_test_13_erase;

static class TestDescription_VectorTestSuite_test_14_clear : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_14_clear() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 432, "test_14_clear" ) {}
 void runTest() { suite_VectorTestSuite.test_14_clear(); }
} testDescription_VectorTestSuite_test_14_clear;

static class TestDescription_VectorTestSuite_test_15_sort : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_15_sort() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 444, "test_15_sort" ) {}
 void runTest() { suite_VectorTestSuite.test_15_sort(); }
} testDescription_VectorTestSuite_test_15_sort;

static class TestDescription_VectorTestSuite_test_16_vector_as_elements : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_16_vector_as_elements() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 508, "test_16_vector_as_elements" ) {}
 void runTest() { suite_VectorTestSuite.test_16_vector_as_elements(); }
} testDescription_VectorTestSuite_test_16_vector_as_elements;

static class TestDescription_VectorTestSuite_test_17_capacity : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_17_capacity() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 560, "test_17_capacity" ) {}
 void runTest() { suite_VectorTestSuite.test_17_capacity(); }
} testDescription_VectorTestSuite_test_17_capacity;

static class TestDescription_VectorTestSuite_test_18_copy_empty : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_18_copy_empty() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 597, "test_18_copy_empty" ) {}
 void runTest() { suite_VectorTestSuite.test_18_copy_empty(); }
} testDescription_VectorTestSuite_test_18_copy_empty;

static class TestDescription_VectorTestSuite_test_19_destructors : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_19_destructors() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 635, "test_19_destructors" ) {}
 void runTest() { suite_VectorTestSuite.test_19_destructors(); }
} testDescription_VectorTestSuite_test_19_destructors;

static class TestDescription_VectorTestSuite_test_20_strings : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_20_strings() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 668, "test_20_strings" ) {}
 void runTest() { suite_VectorTestSuite.test_20_strings(); }
} testDescription_VectorTestSuite_test_20_strings;

static class TestDescription_VectorTestSuite_test_21_resize : public CxxTest::RealTestDescription {
public:
 TestDescription_VectorTestSuite_test_21_resize() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 703, "test_21_resize" ) {}
 void runTest() { suite_VectorTestSuite.test_21_resize(); }
} testDescription_VectorTestSuite_test_21_resize;

#include <cxxtest/Root.cpp>
