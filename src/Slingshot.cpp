#include "Slingshot.h"

// Slingshot Constructor

Slingshot::Slingshot(const std::string& texturePath, float posX, float posY, float worldScale)
    : StaticObject(texturePath, posX, posY, 0.f, 0.f, 0.f, worldScale)
{
	// Set origin to bottom center for proper positioning on the ground
    
    objSprite.setOrigin( objSprite.getGlobalBounds().width / 2.f, objSprite.getGlobalBounds().height);
    objSprite.setPosition(posX, posY);
}