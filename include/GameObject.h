#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "box2d/box2d.h"
#include <iostream>

class GameObject {

	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

};

