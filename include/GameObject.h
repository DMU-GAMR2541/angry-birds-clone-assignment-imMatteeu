#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "box2d/box2d.h"
#include <iostream>

class GameObject {

	GameObject() = default;
	~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

};

