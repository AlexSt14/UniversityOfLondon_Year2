#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class FixtureTest : public CppUnit::TestFixture {
public:
	void setUp()  override {
		printf(" Setup is called\n");
	}
	void tearDown() override {
		printf(" TearDown is called\n");
	}

	void testAddition() {
		CPPUNIT_ASSERT(1 + 1 == 2);
		CPPUNIT_ASSERT(2 + 2 == 3);
	}
	void testSubtraction() {
		CPPUNIT_ASSERT(1 - 1 == 0);
		CPPUNIT_ASSERT(2 - 2 == 1);
	}

	CPPUNIT_TEST_SUITE(FixtureTest);
	CPPUNIT_TEST(testAddition);
	CPPUNIT_TEST_SUITE_END();
};

int main() {
	CppUnit::TextUi::TestRunner runner;	
	CppUnit::TestSuite* suite = new CppUnit::TestSuite("FixtureTest");
	suite->addTest(new CppUnit::TestCaller<FixtureTest>("testAddition", &FixtureTest::testAddition));
	suite->addTest(new CppUnit::TestCaller<FixtureTest>("testSubtraction", &FixtureTest::testSubtraction));
	runner.addTest(suite);
	runner.run();
	return 0;
}