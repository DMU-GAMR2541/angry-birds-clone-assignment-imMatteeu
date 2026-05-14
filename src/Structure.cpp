#pragma once

#include "Structure.h"
#include "StructureProfiles.h"

Structure::Structure(b2World* world, StructMaterial material, float posX, float posY, float rotationDeg, bool physicsEnabled)
	: DynamicObject(
		world,
		getStructureProfile(material),
		posX,
		posY,
		rotationDeg,
		physicsEnabled
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
	case StructMaterial::Stone: return 150;
	case StructMaterial::Ice: return 50;
	}
	return 100;
}

void Structure::takeDamage(int damage)
{
	i_health -= damage;

	if (i_health < 0.0f)
		i_health = 0.0f;

	std::cout << "Structure HP: " << i_health << "\n";
}

bool Structure::isDestroyed() const
{
    return i_health <= 0.0f;
}
