#pragma once

#include "box2d/box2d.h"
#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Bird.h"
#include "Enemy.h"
#include "Structure.h"

class ContactListener : public b2ContactListener
{
public:

    struct HitEvent
    {
        GameObject* target = nullptr;
        float damage = 0.0f;
    };

    std::vector<HitEvent> hitEvents;

    void BeginContact(b2Contact* contact) override
    {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        GameObject* objA =
            reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);

        GameObject* objB =
            reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

        if (!objA || !objB)
            return;

        Bird* bird = nullptr;
        GameObject* target = nullptr;

        // --- Case 1: A is bird, B is target ---
        if ((bird = dynamic_cast<Bird*>(objA)))
        {
            target = objB;

            if (target)
            {
                hitEvents.push_back({ target, 50.0f });
                std::cout << "Bird hit object\n";
            }

            return;
        }

        // --- Case 2: B is bird, A is target ---
        if ((bird = dynamic_cast<Bird*>(objB)))
        {
            target = objA;

            if (target)
            {
                hitEvents.push_back({ target, 50.0f });
                std::cout << "Bird hit object\n";
            }

            return;
        }
    }

    void EndContact(b2Contact* contact) override
    {
        // not needed for now
    }

    void clear()
    {
        hitEvents.clear();
    }
};