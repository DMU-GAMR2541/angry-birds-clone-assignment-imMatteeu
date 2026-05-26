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

	// Struct to hold hit event data

    struct HitEvent
    {
        GameObject* target = nullptr;
        float damage = 0.0f;
    };

	// Vector to store hit events that occur during the physics step. Holds until after the physics step to process effects and damage at a suitable time.

    std::vector<HitEvent> hitEvents;

    // Called on Contact between 2 unique fixtures.

    void BeginContact(b2Contact* contact) override
    {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

		// Retrieve the GameObject pointers from the bodies user data. Assuming that each body has a pointer to its respective GameObject stored in user data.

        GameObject* objA =
            reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);

        GameObject* objB =
            reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

        // If either object is null, fail processing the contact.

        if (!objA || !objB)
            return;

        // Figure out which object is a bird and which is the target. The only targets with meaningful impact are those with the bird.

        Bird* bird = nullptr;
        GameObject* target = nullptr;

        // Case 1: A is bird, B is target
        if ((bird = dynamic_cast<Bird*>(objA)))
        {
            target = objB;

            if (target)
            {
                hitEvents.push_back({ target, 50.0f });
            }

            return;
        }

        // Case 2: B is bird, A is target
        if ((bird = dynamic_cast<Bird*>(objB)))
        {
            target = objA;

            if (target)
            {
                hitEvents.push_back({ target, 50.0f });
            }

            return;
        }
    }

    void EndContact(b2Contact* contact) override {}


	// Clear hit events after processing to avoid multiple damage ticks from one contact.
    void clear() { hitEvents.clear(); }
};