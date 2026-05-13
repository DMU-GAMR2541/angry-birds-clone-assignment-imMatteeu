#pragma once

#include <string>
#include "DynamicObject.h"

enum class EnemySize { Small, Medium, Big };

class Enemy : public DynamicObject {

public:
    Enemy(b2World& world, EnemySize size, float posX, float posY, float rotationDeg = 0.0f);

	virtual ~Enemy() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	void takeDamage(int damage);
	bool isDead() const;

	int getHealth() const;
    EnemySize getSize() const;

private:

	int getInitialHealth(EnemySize size) const;

	int i_health;
	EnemySize e_size;

	bool destroyed = false;
};