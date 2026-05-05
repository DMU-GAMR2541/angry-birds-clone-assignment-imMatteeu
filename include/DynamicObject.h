#pragma once
#include "GameObject.h"

class DynamicObject : public GameObject {

public:
	DynamicObject();
	~DynamicObject();

	DynamicObject(std::string objConstructor, b2World& world);
	
	void Update() override;
	void Render() override;
	void UpdateSprite();

private:

	sf::Sprite objSprite;
	sf::Sprite objTexture;
	sf::RenderWindow objWindow;

	std::string textureLoc;

	b2Vec2 b2_Pos;
	b2BodyDef b2_BodyDef;
	b2FixtureDef b2_FixtureDef;
	b2Body* b2_Body;
	b2CircleShape b2_dynamCircle;

};