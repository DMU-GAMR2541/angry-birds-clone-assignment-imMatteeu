#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "DynamicObject.h"
#include <cmath>

DynamicObject::DynamicObject(
    b2World* world,
	const EntityData& data,
    float posX,
    float posY,
	float rotationDeg,
	bool physicsEnabled
)
    : textureLoc(data.texturePath), i_mass(data.mass), b_physics(physicsEnabled)
{
    // Load texture
    if (!objTexture.loadFromFile(textureLoc))
    {
        std::cout << "Failed to load texture: " << textureLoc << std::endl;
    }

    objSprite.setTexture(objTexture);

    objSprite.setScale(
        data.width / objSprite.getLocalBounds().width,
        data.height / objSprite.getLocalBounds().height
    );

    objSprite.setOrigin(
        objSprite.getLocalBounds().width / 2.0f,
        objSprite.getLocalBounds().height / 2.0f
    );

	if (!physicsEnabled)
		return;

    b2_BodyDef.type = b2_dynamicBody;
    b2_BodyDef.position.Set(posX / 30, posY / 30);
    b2_BodyDef.angle = rotationDeg * 3.1415927f / 180.0f;

    b2_Body = world->CreateBody(&b2_BodyDef);

    b2_Body->GetUserData().pointer =
        reinterpret_cast<uintptr_t>(static_cast<GameObject*>(this));


    if (data.isCircle)
    {
        b2_dynamCircle.m_radius =
            (data.width * 0.5f) / 30.0f;

        b2_FixtureDef.shape = &b2_dynamCircle;
    }
    else
    {
        float halfWidth =
            (data.width * 0.5f) / 30.0f;

        float halfHeight =
            (data.height * 0.5f) / 30.0f;

		b2_dynamRect.SetAsBox(halfWidth, halfHeight);

        b2_FixtureDef.shape = &b2_dynamRect;
    }

    b2_FixtureDef.density = data.mass;
	b2_FixtureDef.friction = data.friction;
	b2_FixtureDef.restitution = data.restitution;

    b2_Body->CreateFixture(&b2_FixtureDef);

}

void DynamicObject::Render(sf::RenderWindow& window)
{
    window.draw(objSprite);
}

void DynamicObject::Update()
{
    const float SCALE = 30.0f;
    const float RAD_TO_DEG = 180.0f / 3.1415927f;

    if (!b_physics || !b2_Body)
        return;

    // Get Box2D position
    b2Vec2 position =
        b2_Body->GetPosition();


    // Sync sprite position
    objSprite.setPosition(
        position.x * SCALE,
        position.y * SCALE
    );

    // Sync sprite rotation
    objSprite.setRotation(
        b2_Body->GetAngle() * RAD_TO_DEG
    );
}

void DynamicObject::UpdateSprite()
{
    Update();
}

DynamicObject::~DynamicObject()
{
    if (b_physics && b2_Body)
    {
        b2_Body->GetWorld()->DestroyBody(b2_Body);
        b2_Body = nullptr;
    }
}

void clearBody()
{
    b2Body* b2_Body = nullptr;
}

