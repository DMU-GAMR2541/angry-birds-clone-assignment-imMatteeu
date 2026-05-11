#pragma once

#include "Structure.h"

Structure::Structure(b2World& world, StructMaterial material, float posX, float posY, ColliderShape shape)
	: DynamicObject(
		"Structure",
		world,
		getTexturePath(material),
		125.0f,
		25.0f,
		getMass(material),
		posX,
		posY,
		shape
	),
	s_material(material),
	i_health(getInitialHealth(material))
{}

void Structure::Update()
{
	DynamicObject::Update();
}

void Structure::Render(sf::RenderWindow& window)
{
	DynamicObject::Render(window);
}

std::string Structure::getTexturePath(StructMaterial material) const
{
	switch (material)
	{
	case StructMaterial::Wood: return "assets/Ang_Birds/woodenwall.png";
	case StructMaterial::Stone: return "assets/Ang_Birds/stonewall.png";
	case StructMaterial::Ice: return "assets/Ang_Birds/icewall.png";
	}

	return "";
}

int Structure::getInitialHealth(StructMaterial material) const
{
	switch (material)
	{
	case StructMaterial::Wood: return 100;
	case StructMaterial::Stone: return 200;
	case StructMaterial::Ice: return 50;
	}
	return 100;
}

float Structure::getMass(StructMaterial material) const
{
	switch (material)
	{
	case StructMaterial::Wood: return 2;
	case StructMaterial::Stone: return 3;
	case StructMaterial::Ice: return 1;
	}
	return 5;
}	



int Structure::getScale() const { return 100; }