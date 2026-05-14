#pragma once
#include <string>
#include "GameObject.h"

class StaticObject : virtual public GameObject {

public:

	StaticObject(const std::string& texturePath, float posX, float posY, float width, float height, float rotationDeg = 0.0f, float worldScale = 1.f);

	virtual ~StaticObject() = default;

	virtual void Update() override;
	virtual void Render(sf::RenderWindow& window) override;

protected:
	sf::Texture objTexture;
	sf::Sprite objSprite;

	std::string textureLoc;
};
