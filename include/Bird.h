#pragma once
#include <string>
#include "DynamicObject.h"

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
	BirdAbility getAbility(BirdType type) const;

	void activateAbility();

private:

	BirdType b_type;
	BirdAbility b_ability;

	bool b_abilityUsed = false;
};
