#include "Bird.h"

Bird::Bird(b2World& world, BirdType type, float posX, float posY)
	: DynamicObject(
		"Bird",
		world,
		getTexturePath(type),
		getScale(type),
		getMass(type),
		posX,
		posY
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

std::string Bird::getTexturePath(BirdType type) const
{
	switch (type)
	{
	case BirdType::Red: return "assets/Ang_Birds/redbird.png";
	case BirdType::Yellow: return "assets/Ang_Birds/yellowbird.png";
	case BirdType::Black: return "assets/Ang_Birds/blackbird.png";
	}

	return "";
}

float Bird::getMass(BirdType type) const
{
	switch (type)
	{
	case BirdType::Red: return 1;
	case BirdType::Yellow: return 1.5;
	case BirdType::Black: return 2;
	}

	return 1;
}

int Bird::getScale(BirdType type) const
{
	switch (type)
	{
	case BirdType::Red: return 50;
	case BirdType::Yellow: return 50;
	case BirdType::Black: return 60;
	}

	return 50;
}

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
