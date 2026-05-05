#pragma once
#include "GameObject.h"

enum class objType 
{
	Enemy,
	Bird,
	Catapult,
	Structure,
	UI
};


class DynamicObject : public GameObject {

public:
	DynamicObject();
	~DynamicObject();

	DynamicObject(std::string objConstructor, b2World& world, int sprScale, int objMass) {
		i_mass = objMass;
		b2FixtureDef b2;
		b2.density = objMass;
	};
	
	void Update() override;
	void Render() override;
	void UpdateSprite();

private:
	int i_mass;
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