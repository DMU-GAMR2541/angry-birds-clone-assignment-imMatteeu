#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <iostream>

#include <vector>
#include <memory>
#include <algorithm>

#include "Enemy.h"
#include "Bird.h"
#include "Structure.h"

int main() {
    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;

    bool isAbilityPressed = false;

    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);

    //Setup ground for the circle to move / bounce on.
    //Needs to have a body definition and a body. We use a raw pointer for the b2Body as Box2d does the management itself.
    //A body can be defined as having a position, velocity, and mass. 
    b2BodyDef b2_groundBodyDef;
    b2_groundBodyDef.position.Set(600.0f / SCALE, 790.0f / SCALE);
    b2Body* b2_groundBody = world.CreateBody(&b2_groundBodyDef);

    //Define a fixture shape that relates to the collision for the ground.
    b2PolygonShape b2_groundBox;
    b2_groundBox.SetAsBox(600.0f / SCALE, 10.0f / SCALE);
    b2_groundBody->CreateFixture(&b2_groundBox, 0.0f);

    //Set up the ground visualisation.
    sf::RectangleShape sf_groundVisual(sf::Vector2f(1200.0f, 20.0f));
    sf_groundVisual.setOrigin(600.0f, 10.0f);
    sf_groundVisual.setFillColor(sf::Color(34, 139, 34)); // Forest Green

    //Setting up a wall for the ball to hit.
    b2BodyDef b2_wallDef;
    b2_wallDef.position.Set(1150.0f / SCALE, 700.0f / SCALE);
    b2Body* b2_wallBody = world.CreateBody(&b2_wallDef);


    b2PolygonShape b2_wallBox;
    b2_wallBox.SetAsBox(10.0f / SCALE, 80.0f / SCALE);
    b2_wallBody->CreateFixture(&b2_wallBox, 0.0f);

    sf::RectangleShape sf_wallVisual(sf::Vector2f(20.0f, 160.0f));
    sf_wallVisual.setOrigin(10.0f, 80.0f);
    sf_wallVisual.setFillColor(sf::Color::Red);

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bird>> birds;
    std::vector<std::unique_ptr<Structure>> structures;

    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Small, 875, 750));
    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Medium, 650, 300));
    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Big, 1000, 300));

    birds.push_back(std::make_unique<Bird>(world, BirdType::Red, 100, 200));
    birds.push_back(std::make_unique<Bird>(world, BirdType::Yellow, 200, 200));
    birds.push_back(std::make_unique<Bird>(world, BirdType::Black, 300, 200));

	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 850, 750, 90));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 900, 750, 90));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 875, 710, 0));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 500, 400, 0));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Ice, 500, 600, 0));

    

    int activeBirdIndex = 0;

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    
                    Bird* currentBird;

                    if (activeBirdIndex < birds.size()) {
                        currentBird  = birds[activeBirdIndex].get();


                        b2Body* body =
                            currentBird->getBody();

                        // Reset position of the ball so that it can be fired again from its original poisition.
                        body->SetTransform(b2Vec2(200.0f / SCALE, 575.0f / SCALE), 0);
                        body->SetLinearVelocity(b2Vec2(0, 0));
                        body->SetAngularVelocity(0);

                        // Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
                        body->ApplyLinearImpulse(b2Vec2(50.0f, -5.0f), body->GetWorldCenter(), true);

                        std::cout << "Firing" << std::endl;
                        activeBirdIndex++;
                    }

                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isAbilityPressed == false)
            {
                Bird* currentBird;

                if (activeBirdIndex < birds.size()) {
                  currentBird = birds[activeBirdIndex].get();

                  currentBird->activateAbility();

                  std::cout << "Ability Activated" << std::endl;

                  isAbilityPressed = true;
                }

            }
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        for (auto& enemy : enemies)
        {
            enemy->Update();
        }

        for (auto& bird : birds)
        {
            bird->Update();
        }
		for (auto& structure : structures)
		{
			structure->Update();
		}

        //Static objects usually don't move, but we set the position once.
        sf_groundVisual.setPosition(b2_groundBody->GetPosition().x * SCALE, b2_groundBody->GetPosition().y * SCALE);
        sf_wallVisual.setPosition(b2_wallBody->GetPosition().x * SCALE, b2_wallBody->GetPosition().y * SCALE);


        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        window.draw(sf_groundVisual);
        window.draw(sf_wallVisual);

        for (auto& enemy : enemies)
        {
            enemy->Render(window);
        }

        for (auto& bird : birds)
        {
            bird->Render(window);
        }

		for (auto& structure : structures)
		{
			structure->Render(window);
		}

        window.display();

    }

    return 0;
}