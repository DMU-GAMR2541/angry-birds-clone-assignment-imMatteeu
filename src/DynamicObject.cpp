#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "DynamicObject.h"

DynamicObject::DynamicObject(
	std::string objConstructor,
	b2World& world,
	const std::string& texturePath,
	int sprScale,
	int objMass
)
	: textureLoc(texturePath), i_mass(objMass)
{}

void DynamicObject::Render(sf::RenderWindow& window)
{
	// TODO: your rendering logic here
}

void DynamicObject::Update()
{
	// TODO: your update logic here
}
