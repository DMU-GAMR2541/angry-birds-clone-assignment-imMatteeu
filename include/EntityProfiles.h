#pragma once

#include <string>

struct EntityData {
	std::string texturePath;

	float width;
	float height;

	float mass;
	float friction;
	float restitution;

	bool isCircle;
};

