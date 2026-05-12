#include "Bird.h"
#include "BirdProfiles.h"

Bird::Bird(b2World& world, BirdType type, float posX, float posY, float rotationDeg)
	: DynamicObject(
		world,
		getBirdProfile(type),
		posX,
		posY,
		rotationDeg
	),
	b_type(type),
	b_ability(getAbility(type))
{
}

void Bird::Update()
{
	DynamicObject::Update();
}

void Bird::Render(sf::RenderWindow& window)
{
	DynamicObject::Render(window);
}

void Bird::activateAbility() {}

BirdAbility Bird::getAbility(BirdType type) const
{
	switch (type)
	{
	case BirdType::Red: return BirdAbility::None;
	case BirdType::Yellow: return BirdAbility::Dash;
	case BirdType::Black: return BirdAbility::Explode;
	}

	return BirdAbility::None;
}
