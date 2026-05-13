#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include <iostream>

#include <vector>
#include <memory>
#include <algorithm>

#include "Enemy.h"
#include "Bird.h"
#include "Structure.h"
#include "ContactListener.h"

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

    ContactListener contactListener;
    world.SetContactListener(&contactListener);

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
    b2_wallDef.position.Set(1200.0f / SCALE, 400.0f / SCALE);
    b2Body* b2_wallBody = world.CreateBody(&b2_wallDef);


    b2PolygonShape b2_wallBox;
    b2_wallBox.SetAsBox(10.0f / SCALE, 800.0f / SCALE);
    b2_wallBody->CreateFixture(&b2_wallBox, 0.0f);

    sf::RectangleShape sf_wallVisual(sf::Vector2f(20.0f, 800.0f));
    sf_wallVisual.setOrigin(10.0f, 400.0f);
    sf_wallVisual.setFillColor(sf::Color::Red);

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bird>> birds;
    std::vector<std::unique_ptr<Structure>> structures;

    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Small, 875, 750));
    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Medium, 650, 300));
    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Big, 897, 540));

    birds.push_back(std::make_unique<Bird>(world, BirdType::Red, 100, 750));
    birds.push_back(std::make_unique<Bird>(world, BirdType::Yellow, 100, 750));
    birds.push_back(std::make_unique<Bird>(world, BirdType::Black, 300, 750));

	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 845, 750, 90));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 895, 750, 90));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 950, 750, 90));	
    
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 845, 680, 90));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 895, 680, 90));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 950, 680, 90));

    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 867, 610, 90));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 927, 610, 90));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 897, 570, 0));

	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 867, 710, 0));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 927, 710, 0));	
    
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 867, 640, 0));
	structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 927, 640, 0));

    

    int activeBirdIndex = 0;

    bool birdInFlight = false;
    bool isDragging = false;

    sf::Vector2 slingshotOrigin(200.f, 600.f);

    float maxDragDistX = 75.f;
    float maxDragDistY = 75.f;

    float launchStr = 0.6f;

    Bird* tempBird;
    tempBird = birds[0].get();
    b2Body* tempBody = tempBird->getBody();
    
    tempBody->SetTransform(b2Vec2(200.0f / SCALE, 600.0f / SCALE), 0);
    tempBody->SetType(b2_kinematicBody);

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "Left MB Pressed\n";
                    if (activeBirdIndex < birds.size() && !birdInFlight)
                    {
                        Bird* currentBird = birds.front().get();

                        isDragging = true;
                        currentBird->setDragging(true);
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Left MB Released\n";
                    if (activeBirdIndex < birds.size() && !birdInFlight) {
                        
                        Bird* currentBird = birds[activeBirdIndex].get();

                        b2Body* body = currentBird->getBody();

                        sf::Vector2f birdPos(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);

                        sf::Vector2f launchVec = slingshotOrigin - birdPos;

                        body->SetType(b2_dynamicBody);

                        body->ApplyLinearImpulseToCenter(b2Vec2(launchVec.x * launchStr, launchVec.y * launchStr), true);

                        currentBird->setDragging(false);
                        isDragging = false;
                        birdInFlight = true;

                        currentBird->setFired(true);
                        currentBird->activate();
                    }
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isAbilityPressed == false && birdInFlight)
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
        if (activeBirdIndex < birds.size())
        {
            Bird* currentBird = birds[activeBirdIndex].get();

            if (birdInFlight && currentBird->isExpired())
            {
                birdInFlight = false;
                isAbilityPressed = false;


                activeBirdIndex++;

                if (activeBirdIndex < birds.size())
                {
                    Bird* nextBird = birds[activeBirdIndex].get();
                    b2Body* body = nextBird->getBody();

                    body->SetType(b2_kinematicBody);
                    body->SetTransform(
                        b2Vec2(200.0f / SCALE, 600.0f / SCALE),
                        0
                    );

                    body->SetLinearVelocity(b2Vec2(0, 0));
                    body->SetAngularVelocity(0);
                    body->SetAwake(true);
                }
            }
        }

        if (isDragging && activeBirdIndex < birds.size())
        {
            b2Body* body = birds[activeBirdIndex].get()->getBody();

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            sf::Vector2f mouseWorld(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            sf::Vector2f dragVector = mouseWorld - slingshotOrigin;

            float sq_dragVecX = dragVector.x * dragVector.x;
            float sq_dragVecY = dragVector.y * dragVector.y;

            float length = std::sqrt(sq_dragVecX * sq_dragVecY);

            dragVector.x = std::clamp(dragVector.x, -maxDragDistX, maxDragDistX);
            dragVector.y = std::clamp(dragVector.y, -maxDragDistY, maxDragDistY);

            sf::Vector2f newPosition = slingshotOrigin + dragVector;

            body->SetTransform(b2Vec2(newPosition.x / SCALE, newPosition.y / SCALE), 0);
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

        if (isDragging && activeBirdIndex < birds.size())
        {
            b2Body* body = birds[activeBirdIndex].get()->getBody();

            sf::Vector2f birdPos(
                body->GetPosition().x * SCALE,
                body->GetPosition().y * SCALE
            );

            sf::Vertex slingLine[] =
            {
                sf::Vertex(slingshotOrigin, sf::Color::Black),
                sf::Vertex(birdPos, sf::Color::Black)
            };

            window.draw(slingLine, 2, sf::Lines);
        }

        window.display();

    }



    return 0;
}