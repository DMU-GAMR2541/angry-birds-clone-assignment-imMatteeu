#include <gtest/gtest.h>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <vector>
#include <list>

#include "enemyTest.h"
#include "slingshotTest.h"

#include "Enemy.h"
#include "Bird.h"
#include "Slingshot.h"
#include "Structure.h"

int initHP = 50;
int initTension = 0;


class UnitTests : public testing::Test {
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

class EnemyTests : public testing::TestWithParam<b2Vec2>
{
public:
	b2Vec2 b2_gravity;
	b2World world;

	std::unique_ptr<Bird> bird;
	std::vector<std::unique_ptr<Enemy>> enemies;

	EnemyTests()
		: b2_gravity(0.0f, 9.8f), world(b2_gravity) {}

	void SetUp() override
	{
		enemies.clear();

		bird = std::make_unique<Bird>(&world, BirdType::Red, 0, 0);
		b2Body* body = bird->getBody();

		enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Small, 830, 660));
		enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Medium, 1100, 640));
		enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Big, 585, 510));
		enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Small, 300, 510));
	}
};

class BirdTests : public testing::TestWithParam<float>
{
public:
	b2Vec2 b2_gravity;
	b2World world;
	std::unique_ptr<Bird> bird;
	BirdTests()
		: b2_gravity(0.0f, 9.8f), world(b2_gravity) {
	}
	void SetUp() override
	{
		bird = std::make_unique<Bird>(&world, BirdType::Red, 0, 0);
	}
};

TEST_P(BirdTests, BirdMovementTest)
{
	float impulse = GetParam();
	float previousX = 0;

	b2Body* birdBod = bird->getBody();

	b2Vec2 startingPos = birdBod->GetPosition();

	birdBod->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0.f), true);

	for (int i = 0; i < 60; ++i) // Simulate 1 second of movement at 60 FPS
	{
		world.Step(1.0f / 60.0f, 8, 3);
	}

	b2Vec2 endingPos = birdBod->GetPosition();

	b2Vec2 distanceTravelled = (endingPos - startingPos);

	EXPECT_GT(distanceTravelled.x, previousX);
	EXPECT_GT(distanceTravelled.x, impulse * 0.1f); // Expect the bird to have traveled a reasonable distance based on the impulse applied

	//std::cout << "Impulse: " << impulse << " Starting X: " << startingPos.x << " Ending X: " << endingPos.x << " Distance Travelled: " << distanceTravelled.x << std::endl;

	previousX = endingPos.x;
}

TEST_F(BirdTests, TextureLoadedTest) 
{
	EXPECT_TRUE(bird->isTextureLoaded());
}

INSTANTIATE_TEST_SUITE_P(BirdMovementTest, BirdTests, ::testing::Values(5.f, 10.f, 15.f, 20.f, 50.f));

TEST_P(EnemyTests, RelativeLocationTest)
{
	b2Body* birdBod = bird->getBody();

	birdBod->SetTransform(GetParam(), 0); // Set bird position to the test parameter value

	b2Vec2 birdPos = birdBod->GetPosition();

	float totalDistance = 0.f; // Variable to accumulate total distance for average calculation
	float averageDistance = 0.f; // Variable to hold average distance

	for (const auto& enemy : enemies)
	{
		b2Vec2 enemyPos = enemy->getBody()->GetPosition();

		enemyPos.x *= 30.f;
		enemyPos.y *= 30.f;

		float distance = b2Distance(birdPos, enemyPos);

		//std::cout << "Bird: " << birdPos.x << ", " << birdPos.y << " vs Enemy: " << enemyPos.x << ", " << enemyPos.y << " Distance: " << distance << std::endl;

		totalDistance += distance;
		averageDistance = totalDistance / enemies.size();



		EXPECT_GT(distance, 30.f);
		EXPECT_LT(distance, 1200.f);
	}

	//std::cout << std::endl << "Average Distance: " << averageDistance << std::endl;

	EXPECT_GT(totalDistance, 100.0f);
}

TEST_F(EnemyTests, TextureLoadedTest)
{
	for (const auto& enemy : enemies)
	{
		EXPECT_TRUE(enemy->isTextureLoaded());
		std::cout << "Enemy Texture Loaded: " << enemy->isTextureLoaded() << std::endl;
	}
}

INSTANTIATE_TEST_CASE_P(RelativeLocationTest, EnemyTests, ::testing::Values(b2Vec2(100,200), b2Vec2(400, 600), b2Vec2(900, 700), b2Vec2(1100,400)));



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

TEST_F(UnitTests, enemyCorrectlyInitialised)
{
	EXPECT_FALSE(enemy->checkIfPopped());
	EXPECT_EQ(enemy->getHealth(), initHP);
}

TEST_F(UnitTests, takeDamageReducesHealth)
{
	enemy->takeDamage(20);
	EXPECT_EQ(enemy->getHealth(), 30);
}

TEST_F(UnitTests, takeDamagePopsEnemy)
{
	enemy->takeDamage(50);
	EXPECT_TRUE(enemy->checkIfPopped());
	EXPECT_EQ(enemy->getHealth(), 0);
}

// > Slingshot Test

TEST_F(UnitTests, slingshotCorrectlyInitialised)
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