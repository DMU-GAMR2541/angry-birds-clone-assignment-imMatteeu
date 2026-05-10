#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

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

	DynamicObject(std::string objConstructor, b2World& world, const std::string& texturePath, int sprScale, int objMass, float posX, float posY);

	~DynamicObject();
	
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	void UpdateSprite();

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
};