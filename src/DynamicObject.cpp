#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "DynamicObject.h"
#include <cmath>

DynamicObject::DynamicObject(
    std::string objConstructor,
    b2World& world,
    const std::string& texturePath,
    float width,
    float height,
    int objMass,
    float posX,
    float posY,
	ColliderShape shape
)
    : textureLoc(texturePath), i_mass(objMass)
{
    // Load texture
    if (!objTexture.loadFromFile(textureLoc))
    {
        std::cout << "Failed to load texture: " << textureLoc << std::endl;
    }

    objSprite.setTexture(objTexture);

    objSprite.setScale(
        width / objSprite.getLocalBounds().width,
        height / objSprite.getLocalBounds().height
    );

    b2_BodyDef.type = b2_dynamicBody;
    b2_BodyDef.position.Set(posX / 30, posY / 30);

    b2_Body = world.CreateBody(&b2_BodyDef);

    if (shape == ColliderShape::Circle)
    {
        b2_dynamCircle.m_radius =
            (width * 0.5f) / 30.0f;

        b2_FixtureDef.shape = &b2_dynamCircle;
    }
    else if (shape == ColliderShape::Rectangle)
    {
        float halfWidth =
            (width * 0.5f) / 30.0f;

        float halfHeight =
            (height * 0.5f) / 30.0f;

		b2_dynamRect.SetAsBox(halfWidth, halfHeight);

        b2_FixtureDef.shape = &b2_dynamRect;
    }

    b2_FixtureDef.density = static_cast<float>(objMass);
    b2_FixtureDef.friction = 0.3f;

    b2_Body->CreateFixture(&b2_FixtureDef);

    objSprite.setOrigin(
        objSprite.getLocalBounds().width / 2.0f,
        objSprite.getLocalBounds().height / 2.0f
    );
}

void DynamicObject::Render(sf::RenderWindow& window)
{
    window.draw(objSprite);
}

void DynamicObject::Update()
{
    const float SCALE = 30.0f;
    const float RAD_TO_DEG = 180.0f / 3.1415927f;

    if (b2_Body == nullptr)
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
    if (b2_Body)
    {
        b2_Body->GetWorld()->DestroyBody(b2_Body);
        b2_Body = nullptr;
    }
}

