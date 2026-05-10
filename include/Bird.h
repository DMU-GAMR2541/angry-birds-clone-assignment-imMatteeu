#pragma once
#include <string>
#include "DynamicObject.h"

enum class BirdType { Red, Yellow, Black };

class Bird : public DynamicObject {

public:
	Bird(b2World& world, BirdType type, float posX, float posY);

	virtual ~Bird() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	void toBeDestroyed() const;

	BirdType getType() const;

private:
	std::string getTexturePath(BirdType type) const;
	int getMass(BirdType type) const;
	int getScale(BirdType type) const;
	int getAbility(BirdType type) const;

	BirdType b_Type;
};
