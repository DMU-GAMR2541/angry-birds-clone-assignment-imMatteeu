#include "StaticObject.h"
#include <iostream>

StaticObject::StaticObject(const std::string& texturePath,
    float posX,
    float posY,
    float width,
    float height,
    float rotationDeg,
    float worldScale
    )
    : textureLoc(texturePath)
{
    if (!objTexture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return;
    }

    objSprite.setTexture(objTexture);

    objSprite.setScale(worldScale, worldScale);



    objSprite.setPosition(posX, posY);

    // Rotation (around default origin unless modified later)
    objSprite.setRotation(rotationDeg);
}


void StaticObject::Update() {}

void StaticObject::Render(sf::RenderWindow& window)
{
    window.draw(objSprite);
}