#include <gtest/gtest.h>
#include "enemyTest.h"
#include "slingshotTest.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <list>

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class Foo.
class EnemyTest : public testing::Test {
public:
    std::unique_ptr<enemyTest> enemy;
    std::unique_ptr<slingshotTest> slingshot;
protected:

    void SetUp() override 
    {
        enemy = std::make_unique<enemyTest>(50); // All enemnies in this test suite start with 50 HP.
		slingshot = std::make_unique<slingshotTest>();

		slingshot->loadBird("Red"); // All slingshots in this test suite start with a red bird loaded.
    }

    void TearDown() override 
    {
		enemy.reset();
		slingshot.reset();
    }


};

// Basic Tests for Enemy and Slingshot class members, checks for correct value initializations.

TEST(Enemy, First_test) 
{
    enemyTest e(100);

    EXPECT_EQ(e.getHealth(), 100);
}

TEST(slingshot, iniTensionTest) 
{
	slingshotTest s;

	EXPECT_EQ(s.getTension(), 0);
}

// Tests for Fatal and Non-Fatal Assetions

TEST(AssertionTests, FatalAssertion)
{
    // Applied Fatal Assertion

	slingshotTest s;

	ASSERT_EQ(s.getTension(), 0); // Pass

	s.pullBack(50);

	ASSERT_EQ(s.getTension(), 50); // Pass

	ASSERT_EQ(s.getTension(), 100); // Fail, test will end due to fatal assertion

	ASSERT_EQ(s.getTension(), 50); // Pass, will not run due to fatal assertion
}

TEST(AssertionTests, NonFatalAssertions)
{
	// Applied Non-Fatal Assertion

	slingshotTest s;

	EXPECT_EQ(s.getTension(), 0); // Pass

	s.pullBack(50);

	EXPECT_EQ(s.getTension(), 50); // Pass

	EXPECT_EQ(s.getTension(), 100); // Fail, but test will continue due to non-fatal assertion

	EXPECT_EQ(s.getTension(), 50); // Pass, test continues after non-fatal assertion failure
}


//TEST_F(EnemyTest, LethalDamagePopsPig)
//{
//    enemy->takeDamage(60);
//
//    EXPECT_TRUE(enemy->checkIfPopped());
//}
//
//TEST(SlingshotTest, tension_Test) {
//    slingshotTest s;
//    EXPECT_EQ(s.getTension(), 0);
//}
//
//
//
//class ParamTest : public ::testing::TestWithParam<int> {
//protected:
//    ParamTest() = default;
//    ~ParamTest() = default;
//
//    void SetUp() override {}
//    void TearDown() override {}
//};
//
//TEST_P(ParamTest, SimpleTest) {
//    int i_test;
//}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}