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

class DynamicObject : virtual public GameObject {

public:

	DynamicObject(b2World* world, const EntityData& data, float posX, float posY, float rotationDeg, bool physicsEnabled);

	~DynamicObject();
	
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	void UpdateSprite();
	void clearBody();

	b2Body* getBody() { return b2_Body; }

	void invalidateBody()
	{
		b2_Body = nullptr;
	}

	sf::Vector2f getPosition() const;

protected:

b2Body* b2_Body = nullptr;

private:
	int i_mass;
	bool b_physics;

	sf::Sprite objSprite;
	sf::Texture objTexture;

	std::string textureLoc;

	b2Vec2 b2_Pos;

	b2BodyDef b2_BodyDef;
	b2FixtureDef b2_FixtureDef;

	b2CircleShape b2_dynamCircle;
	b2PolygonShape b2_dynamRect;
};