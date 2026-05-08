#pragma once

#include <string>
#include "DynamicObject.h"

enum class EnemySize { Small, Medium, Big };

class Enemy : public DynamicObject {

public:
    Enemy(b2World& world, EnemySize size);

	virtual ~Enemy() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	void takeDamage(int damage);
	bool toBeDestroyed() const;

	int getHealth() const;
    EnemySize getSize() const;

private:

    std::string getTexturePath(EnemySize size) const;
	int getMass(EnemySize size) const;
	int getScale(EnemySize size) const;
	int getInitialHealth(EnemySize size) const;

	int i_health;
	EnemySize e_size;
};