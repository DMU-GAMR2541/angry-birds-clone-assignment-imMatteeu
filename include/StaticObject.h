#pragma once
#include "GameObject.h"

class StaticObject : public GameObject {

	void Render(sf::RenderWindow& window) override;
};
