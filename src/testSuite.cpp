#include "testSuite.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bird.h"
#include "Slingshot.h"
#include "Structure.h"

void testBirdMovement(b2World& world) 
{

}

void testStructurePlacement(b2World& world) 
{

}

void testRelativeEnemies(b2World& world) 
{

}

void testDestructorOrder(b2World& world) 
{

}

void runTest(b2World& world)
{
	std::cout << "<x> Running Tests <x>" << std::endl;

	testBirdMovement(world);
	testStructurePlacement(world);
	testRelativeEnemies(world);
	testDestructorOrder(world);

	std::cout << "<x> Tests Complete <x>" << std::endl;
}