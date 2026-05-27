#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "box2d/box2d.h"
#include <iostream>

#include "TestConfig.h"
#include "TestDestructorLog.h"

class GameObject 
{
public:
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual ~GameObject() = 0;
};

inline GameObject::~GameObject()
{
#ifdef UNIT_TESTING
	TestDestructorLog::log("GameObject");
#endif
}

