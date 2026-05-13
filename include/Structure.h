#pragma once

#include <string>
#include "DynamicObject.h"

enum class StructMaterial { Wood, Stone, Ice };


class Structure : public DynamicObject {

public:
	Structure(b2World& world, StructMaterial material, float posX, float posY, float rotationDeg);

	virtual ~Structure() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;


	void takeDamage(int damage);
	bool isDestroyed() const;

	StructMaterial getMaterial() const;

private:

	int getInitialHealth(StructMaterial material) const;

	StructMaterial s_material;
	int i_health;
	bool b_destroyed = false;
};