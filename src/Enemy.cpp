#include "Enemy.h"
#include "EnemyProfiles.h"

Enemy::Enemy(b2World* world, EnemySize size, float posX, float posY, float rotationDeg, bool physicsEnabled)
    : DynamicObject(
        world,
		getEnemyProfile(size),
        posX,
        posY,
        rotationDeg,
        physicsEnabled
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
    case EnemySize::Big: return 150;
    }

    return 50;
}

void Enemy::takeDamage(int damage)
{
    i_health -= damage;

    if (i_health < 0.0f)
        i_health = 0.0f;

    std::cout << "Enemy HP: " << i_health << "\n";
}

bool Enemy::isDead() const
{
    return i_health <= 0.0f;
}