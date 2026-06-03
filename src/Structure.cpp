#pragma once

#include "Structure.h"
#include "StructureProfiles.h"

// Structure Constructor

Structure::Structure(b2World* world, StructMaterial material, float posX, float posY, float rotationDeg, bool physicsEnabled)
	: DynamicObject(world, getStructureProfile(material), posX,	posY, rotationDeg, physicsEnabled ),
	s_material(material), i_health(getInitialHealth(material)) {}

void Structure::Update()
{
	DynamicObject::Update();
}

void Structure::Render(sf::RenderWindow& window)
{
	DynamicObject::Render(window);
}

// Initial health values based on material type, can be adjusted for game balance

int Structure::getInitialHealth(StructMaterial material) const
{
	switch (material)
	{
	case StructMaterial::Wood: return 150;
	case StructMaterial::Stone: return 200;
	case StructMaterial::Ice: return 50;
	}
	return 150;
}

// Damage application function, reduces health by damage amount and clamps to zero to prevent negative health values

void Structure::takeDamage(int damage)
{
	i_health -= damage;
	if (i_health < 0.0f) { i_health = 0.0f; }
}

bool Structure::isDestroyed() const
{
    return i_health <= 0.0f;
}
