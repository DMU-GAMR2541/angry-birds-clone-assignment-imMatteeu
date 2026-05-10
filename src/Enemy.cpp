#include "Enemy.h"

Enemy::Enemy(b2World& world, EnemySize size, float posX, float posY)
    : DynamicObject(
        "Enemy",
        world,
        getTexturePath(size),
        getScale(size),
        getMass(size),
        posX,
        posY
    ),
    e_size(size),
    i_health(getInitialHealth(size))
{
}

void Enemy::Update()
{
    DynamicObject::Update();
}

void Enemy::Render(sf::RenderWindow& window)
{
    DynamicObject::Render(window);
}

std::string Enemy::getTexturePath(EnemySize size) const
{
    switch (size)
    {
    case EnemySize::Small: return "assets/Ang_Birds/pig.png";
    case EnemySize::Medium: return "assets/Ang_Birds/pig.png";
    case EnemySize::Big: return "assets/Ang_Birds/pig.png";
    }

    return "";
}

int Enemy::getMass(EnemySize size) const
{
    switch (size)
    {
    case EnemySize::Small: return 1;
    case EnemySize::Medium: return 2;
    case EnemySize::Big: return 4;
    }

    return 1;
}

int Enemy::getScale(EnemySize size) const
{
    switch (size)
    {
    case EnemySize::Small: return 50;
    case EnemySize::Medium: return 75;
    case EnemySize::Big: return 100;
    }

    return 50;
}

int Enemy::getInitialHealth(EnemySize size) const
{
    switch (size)
    {
    case EnemySize::Small: return 50;
    case EnemySize::Medium: return 100;
    case EnemySize::Big: return 200;
    }

    return 50;
}