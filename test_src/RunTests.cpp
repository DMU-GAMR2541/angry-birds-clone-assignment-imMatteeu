#include <gtest/gtest.h>
#include "enemyTest.h"
#include "slingshotTest.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <list>

int initHP = 50;
int initTension = 0;

class EnemyTest : public testing::Test {
public:
    std::unique_ptr<enemyTest> enemy;
    std::unique_ptr<slingshotTest> slingshot;


protected:

    void SetUp() override 
    {
        enemy = std::make_unique<enemyTest>(initHP); // All enemnies in this test suite start with 50 HP.
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
    enemyTest e(initHP);

    EXPECT_EQ(e.getHealth(), initHP);
}

TEST(slingshot, iniTensionTest) 
{
	slingshotTest s;

	EXPECT_EQ(s.getTension(), initTension);
}

// Tests for Fatal Faand Non-Fatal Assetions

TEST(AssertionTests, FatalAssertion)
{
    // Applied Fatal Assertion

	slingshotTest s;

	ASSERT_EQ(s.getTension(), initTension); // Pass

	s.pullBack(50);

	ASSERT_EQ(s.getTension(), 50); // Pass

	ASSERT_EQ(s.getTension(), 100); // Fail, test will end due to fatal assertion

	ASSERT_EQ(s.getTension(), 50); // N/A, will not run due to fatal assertion
}

TEST(AssertionTests, NonFatalAssertions)
{
	// Applied Non-Fatal Assertion

	slingshotTest s;

	EXPECT_EQ(s.getTension(), initTension); // Pass

	s.pullBack(50);

	EXPECT_EQ(s.getTension(), 50); // Pass

	EXPECT_EQ(s.getTension(), 100); // Fail, but test will continue due to non-fatal assertion

	EXPECT_EQ(s.getTension(), 50); // Pass, test continues after non-fatal assertion failure
}

// Fixture Tests

// > Enemy Tests

TEST_F(EnemyTest, enemyCorrectlyInitialised)
{
	EXPECT_FALSE(enemy->checkIfPopped());
	EXPECT_EQ(enemy->getHealth(), initHP);
}

TEST_F(EnemyTest, takeDamageReducesHealth)
{
	enemy->takeDamage(20);
	EXPECT_EQ(enemy->getHealth(), 30);
}

TEST_F(EnemyTest, takeDamagePopsEnemy)
{
	enemy->takeDamage(50);
	EXPECT_TRUE(enemy->checkIfPopped());
	EXPECT_EQ(enemy->getHealth(), 0);
}

// > Slingshot Test

TEST_F(EnemyTest, slingshotCorrectlyInitialised)
{
	EXPECT_EQ(slingshot->getBirdType(), "Red");
	EXPECT_EQ(slingshot->getTension(), 0);
}

// Binary Comparison Tests

TEST(BinaryComparisonTests, operatorComparisons)
{
	enemyTest e1(initHP); // Sets up Enemy 1 with 50hp
	enemyTest e2(initHP); // Sets up Enemy 2 with 50hp

	EXPECT_EQ(e1.getHealth(), e2.getHealth()); // Pass, both have 50 HP

	EXPECT_NE(e1.getHealth(), 0); // Pass, both have 50 HP, not 0

	e1.takeDamage(20); // Enemy 1 takes 20 damage

	EXPECT_LT(e1.getHealth(), e2.getHealth()); // Pass, e1 has 30 HP, e2 has 50 HP
	EXPECT_GT(e2.getHealth(), e1.getHealth()); // Pass, e2 has 50 HP, e1 has 30 HP
}

// Param Tests

class ParamTest : public ::testing::TestWithParam<int> {};

TEST_P(ParamTest, damageValuesTest) {
	enemyTest e(initHP);

	int damage = GetParam(); // Grabs damage to deal from the test parameters

	e.takeDamage(damage); // Apply damage

	EXPECT_LE(e.getHealth(), initHP); // Compare current HP to initial HP
}

INSTANTIATE_TEST_CASE_P(DamageTests, ParamTest, ::testing::Values(10, 20, 30, 40, 50));

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}