#pragma once

#include <string>
#include "DynamicObject.h"

enum class StructMaterial { Wood, Stone, Ice };


class Structure : public DynamicObject {

public:
	Structure(b2World& world, StructMaterial material, float posX, float posY, ColliderShape shape);

	virtual ~Structure() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	bool toBeDestroyed() const;

	StructMaterial getMaterial() const;

private:

	std::string getTexturePath(StructMaterial material) const;
	float getMass(StructMaterial material) const;
	int getScale() const;
	int getInitialHealth(StructMaterial material) const;

	StructMaterial s_material;
	int i_health;
};