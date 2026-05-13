#include "Bird.h"
#include "BirdProfiles.h"

Bird::Bird(b2World& world, BirdType type, float posX, float posY, float rotationDeg)
	: DynamicObject(world, getBirdProfile(type), posX, posY, rotationDeg), b_type(type), b_ability(getAbility(type))
{}

void Bird::Update()
{
	DynamicObject::Update();

	if (active)
	{
		lifeTime += 1.0f / 60.0f;
	}

}

void Bird::Render(sf::RenderWindow& window)
{
	DynamicObject::Render(window);
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

void Bird::setFired(bool value)
{
	fired = value;
}

bool Bird::hasFired() const
{
	return fired;
}

bool Bird::canUseAbility() const
{
	return fired && !b_abilityUsed;
}

void Bird::activateAbility()
{

	if (!canUseAbility()) { return; }

	b_abilityUsed = true;

	switch (b_ability)
	{
	case BirdAbility::Dash:
		getBody()->ApplyLinearImpulseToCenter(b2Vec2(20.0f, 0.0f), true);
		break;

	case BirdAbility::Explode:
		break;

	case BirdAbility::None:
	default:
		break;
	}
}

void Bird::activate() {
	fired = true;
	active = true;
	b_abilityUsed = false;
	lifeTime = 0.0f;
}

bool Bird::isExpired() const {
	return lifeTime >= maxLifeTime;
}

void Bird::invalidateBody()
{
	b2Body* body = getBody();
	if (body)
	{
		body = nullptr;
	}

}

void Bird::setDragging(bool value)
{
	beingDragged = value;
}

bool Bird::isDragging() const
{
	return beingDragged;
}