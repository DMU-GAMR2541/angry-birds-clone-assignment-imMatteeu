#include "StaticObject.h"
#include <iostream>

// StaticObject Constructor

StaticObject::StaticObject(const std::string& texturePath, float posX, float posY, float width, float height, float rotationDeg, float worldScale)
    : textureLoc(texturePath)
{
    if (!objTexture.loadFromFile(texturePath) && texturePath != "")
    {
        std::cerr << "Static Failed to load texture: " << texturePath << std::endl;
        return;
    }

    objSprite.setTexture(objTexture);

    // Transformations

    objSprite.setScale(worldScale, worldScale);
    objSprite.setPosition(posX, posY);
    objSprite.setRotation(rotationDeg);
}


void StaticObject::Update() {}

void StaticObject::Render(sf::RenderWindow& window)
{
    window.draw(objSprite);
}