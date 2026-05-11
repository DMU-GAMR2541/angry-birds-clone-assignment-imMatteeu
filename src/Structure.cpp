#pragma once

#include "Structure.h"

Structure::Structure(b2World& world, StructMaterial material, float posX, float posY)
	: DynamicObject(
		"Structure",
		world,
		getTexturePath(material),
		getScale(),
		getMass(material),
		posX,
		posY
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
	case StructMaterial::Wood:
		break;
	case StructMaterial::Stone:
		break;
	case StructMaterial::Ice:
		break;
	default:
		break;
	}
}

int getScale() { return 30; }