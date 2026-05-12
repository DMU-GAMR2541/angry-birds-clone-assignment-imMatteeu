#include "Enemy.h"
#include "EnemyProfiles.h"

Enemy::Enemy(b2World& world, EnemySize size, float posX, float posY, float rotationDeg)
    : DynamicObject(
        world,
		getEnemyProfile(size),
        posX,
        posY,
        rotationDeg
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