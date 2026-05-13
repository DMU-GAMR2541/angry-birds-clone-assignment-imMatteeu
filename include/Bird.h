#pragma once
#include <string>
#include "DynamicObject.h"
#include <box2d/box2d.h>

enum class BirdType { Red, Yellow, Black };

enum class BirdAbility { None, Dash, Explode };

class Bird : public DynamicObject {

public:
	Bird(b2World& world, BirdType type, float posX, float posY, float rotationDeg = 0.0f);

	virtual ~Bird() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	bool toBeDestroyed() const;

	BirdType getType() const;

	void activateAbility();
	bool canUseAbility() const;

	void setFired(bool value);
	bool hasFired() const;

	void activate();
	bool isExpired() const;
	void invalidateBody();

	float lifeTime = 0.0f;
	float maxLifeTime = 5.0f;
	bool active = false;

	void setDragging(bool value);
	bool isDragging() const;

	b2Fixture* explosionFixture = nullptr;
	float explosionTimer = 0.0f;

private:

	BirdType b_type;
	BirdAbility b_ability;

	bool fired = false;
	bool b_abilityUsed = false;

	bool beingDragged = false;

	BirdAbility getAbility(BirdType type) const;
};
