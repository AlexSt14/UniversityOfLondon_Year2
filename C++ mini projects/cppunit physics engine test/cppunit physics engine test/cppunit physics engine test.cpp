#include <cppunit/TestCase.h> 
#include <cppunit/TestCaller.h> 
#include <cppunit/ui/text/TestRunner.h> 
#include <cppunit/extensions/HelperMacros.h>
#include "physics.h"

class FixtureTests : public CppUnit::TestFixture { 
public: 
	void setUp() override { } 
	void tearDown() override { } 
	void testAddition() { 
		CPPUNIT_ASSERT(2+3 == 5); 
		CPPUNIT_ASSERT(2+3 == 5); 
	} 

	void testThingPosition() {
		Thing thing{ 5.0f, 10.0f, 1.0f };
		CPPUNIT_ASSERT(thing.getX() == 5.0f);
	}
	void testThingStartsStill() {
		Thing thing{ 5.0f, 10.0f, 1.0f };
		thing.update();
		CPPUNIT_ASSERT(thing.getX() == 5.0f);
	}
	void testThingMoves() {
		Thing thing{ 5.0f, 10.0f, 1.0f };
		thing.applyForce(1.0f, 1.0f);
		thing.update();
		//assuming there is a simple force model
		//where applying a force means it 
		//adds that dX each time I update
		CPPUNIT_ASSERT(thing.getX() == 6.0f);
	}
	void testWorldAddThings() {
		World world{ 100.0f, 100.0f, 9.8f };
		Thing thing{ 5.0f, 10.0f, 1.0f };
		Thing thin2{ 5.0f, 10.0f, 1.0f };
		world.addThing(&thing);
		world.addThing(&thin2);
		CPPUNIT_ASSERT(world.countThings() == 2);
	}
	void testWorldGravity() {
		World world{ 100.0f, 100.0f, 9.8f };
		Thing thing{ 5.0f, 10.0f, 1.0f };
		world.addThing(&thing);
		world.update();
		CPPUNIT_ASSERT(thing.getY() == 19.8f);
	}

	CPPUNIT_TEST_SUITE(FixtureTests);
	CPPUNIT_TEST(testAddition);
	CPPUNIT_TEST_SUITE_END();
}; 

int main() { 
	CppUnit::TextUi::TestRunner runner{}; 
	CppUnit::TestSuite* suite = new CppUnit::TestSuite{"FixtureTests"};
	suite->addTest(new CppUnit::TestCaller<FixtureTests>{ "test the addition operator", &FixtureTests::testAddition });
	suite->addTest(new CppUnit::TestCaller<FixtureTests>{ "test the thing position", &FixtureTests::testThingPosition });
	suite->addTest(new CppUnit::TestCaller<FixtureTests>{ "test the thing starts still", &FixtureTests::testThingStartsStill });
	suite->addTest(new CppUnit::TestCaller<FixtureTests>{ "test the thing moves", &FixtureTests::testThingMoves });
	suite->addTest(new CppUnit::TestCaller<FixtureTests>{ "test the world add things", &FixtureTests::testWorldAddThings });
	suite->addTest(new CppUnit::TestCaller<FixtureTests>{ "test the world gravity", &FixtureTests::testWorldGravity });
	runner.addTest(suite);
	runner.run(); 
	return 0; 
}