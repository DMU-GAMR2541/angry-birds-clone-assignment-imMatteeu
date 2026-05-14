#pragma once
#include "StaticObject.h"

class Slingshot : public StaticObject
{
public:
    Slingshot(const std::string& texturePath, float posX, float posY, float worldScale);
};