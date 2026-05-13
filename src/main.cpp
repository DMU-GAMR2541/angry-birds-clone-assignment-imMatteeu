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

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    const float SCALE = 30.0f;
    const float PI = 3.1415927;

    bool isAbilityPressed = false;
    bool birdInFlight = false;
    bool isDragging = false;

    b2Vec2 b2_gravity(0.0f, 9.8f);
    b2World world(b2_gravity);

    ContactListener contactListener;
    world.SetContactListener(&contactListener);

    b2BodyDef b2_groundBodyDef;
    b2_groundBodyDef.position.Set(600.0f / SCALE, 790.0f / SCALE);
    b2Body* b2_groundBody = world.CreateBody(&b2_groundBodyDef);


    b2PolygonShape b2_groundBox;
    b2_groundBox.SetAsBox(600.0f / SCALE, 10.0f / SCALE);
    b2_groundBody->CreateFixture(&b2_groundBox, 0.0f);

    sf::RectangleShape sf_groundVisual(sf::Vector2f(1200.0f, 20.0f));
    sf_groundVisual.setOrigin(600.0f, 10.0f);
    sf_groundVisual.setFillColor(sf::Color(34, 139, 34)); 

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

    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Small, 830, 660));
    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Medium, 650, 300));
    enemies.push_back(std::make_unique<Enemy>(world, EnemySize::Big, 1000, 540));

    birds.push_back(std::make_unique<Bird>(world, BirdType::Red, 100, 750));
    birds.push_back(std::make_unique<Bird>(world, BirdType::Yellow, 100, 750));
    birds.push_back(std::make_unique<Bird>(world, BirdType::Black, 300, 750));

    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 760, 750, -45));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 850, 750, 45));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 745, 750, 90));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 770, 695, 0));

    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 802, 750, 90));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 807, 750, 90));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 805, 690, 90));

    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 865, 750, 90));
    structures.push_back(std::make_unique<Structure>(world, StructMaterial::Stone, 840, 695, 0));

    sf::Vector2 slingshotOrigin(200.f, 600.f);

    float maxDragDistX = 75.f;
    float maxDragDistY = 75.f;

    float launchStr = 0.6f;

    if (!birds.empty())
    {
        b2Body* body = birds.front().get()->getBody();

        body->SetTransform(b2Vec2(slingshotOrigin.x / SCALE, slingshotOrigin.y / SCALE), 0);
        body->SetType(b2_kinematicBody);
    }

    while (window.isOpen()) 
    {
        sf::Event event;

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
            {
                std::cout << "Left MB Pressed\n";
                if (!birds.empty() && !birdInFlight)
                {
                    isDragging = true;
                    birds.front()->setDragging(true);
                }
                
            }

            if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) 
            {
                std::cout << "Left MB Released\n";

                if (!birds.empty() && !birdInFlight) {

                    Bird* bird = birds.front().get();
                    b2Body* body = bird->getBody();

                    sf::Vector2f birdPos(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);

                    sf::Vector2f launchVec = slingshotOrigin - birdPos;

                    body->SetType(b2_dynamicBody);

                    body->ApplyLinearImpulseToCenter(b2Vec2(launchVec.x * launchStr, launchVec.y * launchStr), true);

                    bird->setDragging(false);
                    isDragging = false;

                    birdInFlight = true;
                    bird->setFired(true);
                    bird->activate();
                    }
                
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isAbilityPressed == false && birdInFlight && !birds.empty())
            {

                
                  birds.front().get()->activateAbility();
                  std::cout << "Ability Activated" << std::endl;
                  isAbilityPressed = true;
                

            }
        }
        if (!birds.empty())
        {
            Bird* bird = birds.front().get();

            if (birdInFlight && bird->isExpired())
            {
                birdInFlight = false;
                isAbilityPressed = false;

                birds.erase(birds.begin());


                if (!birds.empty())
                {
                    Bird* nextBird = birds.front().get();
                    b2Body* body = nextBird->getBody();

                    body->SetType(b2_kinematicBody);
                    body->SetTransform(
                        b2Vec2(slingshotOrigin.x / SCALE, slingshotOrigin.y / SCALE),
                        0
                    );

                    body->SetLinearVelocity(b2Vec2(0, 0));
                    body->SetAngularVelocity(0);
                    body->SetAwake(true);
                }
            }
        }

        if (isDragging && !birds.empty())
        {
            b2Body* body = birds.front()->getBody();

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            sf::Vector2f mouseWorld(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            sf::Vector2f dragVector = mouseWorld - slingshotOrigin;

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

        for (const auto& hit : contactListener.hitEvents)
        {
            // ---------- ENEMIES ----------
            if (Enemy* enemy =
                dynamic_cast<Enemy*>(hit.target))
            {
                enemy->takeDamage(hit.damage);

                std::cout << "Enemy took "
                    << hit.damage
                    << " damage\n";
            }

            // ---------- STRUCTURES ----------
            if (Structure* structure =
                dynamic_cast<Structure*>(hit.target))
            {
                structure->takeDamage(hit.damage);

                std::cout << "Structure took "
                    << hit.damage
                    << " damage\n";
            }
        }


        // =============================
        // REMOVE DEAD ENEMIES
        // =============================
        for (auto it = enemies.begin();
            it != enemies.end();)
        {
            if ((*it)->isDead())
            {
                std::cout << "Enemy Destroyed\n";

                world.DestroyBody(
                    (*it)->getBody()
                );

                (*it)->invalidateBody();

                it = enemies.erase(it);
            }
            else
            {
                ++it;
            }
        }


        // =============================
        // REMOVE DESTROYED STRUCTURES
        // =============================
        for (auto it = structures.begin();
            it != structures.end();)
        {
            if ((*it)->isDestroyed())
            {
                std::cout << "Structure Destroyed\n";

                world.DestroyBody(
                    (*it)->getBody()
                );

                (*it)->invalidateBody();

                it = structures.erase(it);
            }
            else
            {
                ++it;
            }
        }


        // =============================
        // CLEAR COLLISION EVENTS
        // =============================
        contactListener.clear();

        sf_groundVisual.setPosition(b2_groundBody->GetPosition().x * SCALE, b2_groundBody->GetPosition().y * SCALE);
        sf_wallVisual.setPosition(b2_wallBody->GetPosition().x * SCALE, b2_wallBody->GetPosition().y * SCALE);

        window.clear(sf::Color(135, 206, 235)); 

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

        if (isDragging && !birds.empty())
        {
            b2Body* body = birds.front().get()->getBody();

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

