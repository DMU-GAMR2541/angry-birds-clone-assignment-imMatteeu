#pragma once

#include "Structure.h"
#include "StructureProfiles.h"

Structure::Structure(b2World& world, StructMaterial material, float posX, float posY, float rotationDeg)
	: DynamicObject(
		world,
		getStructureProfile(material),
		posX,
		posY,
		rotationDeg
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
