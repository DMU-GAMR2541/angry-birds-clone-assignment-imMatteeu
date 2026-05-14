#include "Slingshot.h"

Slingshot::Slingshot(const std::string& texturePath, float posX, float posY, float worldScale)
    : StaticObject(texturePath, posX, posY, 0.f, 0.f, 0.f, worldScale)
{
    objSprite.setOrigin(
        objSprite.getGlobalBounds().width / 2.f,
        objSprite.getGlobalBounds().height
    );

    objSprite.setPosition(posX, posY);
}