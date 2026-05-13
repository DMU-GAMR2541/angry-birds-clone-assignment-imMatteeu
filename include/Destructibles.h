#pragma once

#include "GameObject.h"

class Destructibles : public GameObject
{
public:

	virtual void takeDamage(float damage)
	{
		health -= damage;

		if (health <= 0)
		{
			toBeDestroyed = true;
		}
	}

	bool canDestroy() const { return toBeDestroyed; }

protected:

	float health = 100.f;

	bool toBeDestroyed = false;
};