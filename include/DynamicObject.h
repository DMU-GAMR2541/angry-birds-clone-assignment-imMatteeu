#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "GameObject.h"
#include "EntityProfiles.h"

enum class objType 
{
	Enemy,
	Bird,
	Catapult,
	Structure,
	UI
};

enum class ColliderShape
{
	Circle,
	Rectangle
};

class DynamicObject : public GameObject {

public:

	DynamicObject(b2World& world, const EntityData& data, float posX, float posY, float rotationDeg);

	~DynamicObject();
	
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	void UpdateSprite();

	b2Body* getBody() { return b2_Body; }

private:
	int i_mass;

	sf::Sprite objSprite;
	sf::Texture objTexture;

	std::string textureLoc;

	b2Vec2 b2_Pos;

	b2BodyDef b2_BodyDef;
	b2FixtureDef b2_FixtureDef;

	b2Body* b2_Body = nullptr;

	b2CircleShape b2_dynamCircle;
	b2PolygonShape b2_dynamRect;
};