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
#include "Slingshot.h"
#include "UIElement.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Annoyed_Flocks");
    window.setFramerateLimit(60);

	// Constants for scaling between Box2D and SFML coordinates, and for physics calculations

    const float SCALE = 30.0f;
    const float PI = 3.1415927;

	// Flight and ability state tracking variables

    bool isAbilityPressed = false;
    bool birdInFlight = false;
    bool isDragging = false;

	// Slingshot origin point for dragging and launching birds

    sf::Vector2 slingshotOrigin(200.f, 600.f);

	// Maximum drag distance for the slingshot, effects launch strength and trajectory

    float maxDragDistX = 75.f;
    float maxDragDistY = 75.f;

    float launchStr = 0.6f;

	// Loading screen flag 

    bool loading = true;

	// Initialize Box2D world with gravity

    b2Vec2 b2_gravity(0.0f, 9.8f);
    b2World world(b2_gravity);

	// Load font for UI and create loading screen UI element

    sf::Font font;
    font.loadFromFile("../assets/fonts/angry-birds.ttf");

    UIElement ui("../assets/Ang_Birds/loading.jpg", font);

	// Set up contact listener for handling collisions and damage application

    ContactListener contactListener;
    world.SetContactListener(&contactListener);

    /*
	*<>----------------Object Creation-----------------<>
    */

	// Ground Creation

    b2BodyDef b2_groundBodyDef;
    b2_groundBodyDef.position.Set(600.0f / SCALE, 790.0f / SCALE);
    b2Body* b2_groundBody = world.CreateBody(&b2_groundBodyDef);


	// Create a box shape for the ground and attach it to the body

    b2PolygonShape b2_groundBox;
    b2_groundBox.SetAsBox(600.0f / SCALE, 10.0f / SCALE);
    b2_groundBody->CreateFixture(&b2_groundBox, 0.0f);

	// SFML visual representation of the ground, positioned and colored to match the physics body

    sf::RectangleShape sf_groundVisual(sf::Vector2f(1200.0f, 20.0f));
    sf_groundVisual.setOrigin(600.0f, 10.0f);
    sf_groundVisual.setFillColor(sf::Color(34, 139, 34)); 

	// Wall Creation (boundary to prevent birds from flying off-screen)

    b2BodyDef b2_wallDef;
    b2_wallDef.position.Set(1200.0f / SCALE, 400.0f / SCALE);
    b2Body* b2_wallBody = world.CreateBody(&b2_wallDef);

	// Create a box shape for the wall and attach it to the body

    b2PolygonShape b2_wallBox;
    b2_wallBox.SetAsBox(10.0f / SCALE, 800.0f / SCALE);
    b2_wallBody->CreateFixture(&b2_wallBox, 0.0f);

	// SFML visual representation of the wall, positioned and colored to match the physics body

    sf::RectangleShape sf_wallVisual(sf::Vector2f(20.0f, 800.0f));
    sf_wallVisual.setOrigin(10.0f, 400.0f);
    sf_wallVisual.setFillColor(sf::Color::Red);

	// Vectors to hold game objects

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bird>> birds;
    std::vector<std::unique_ptr<Structure>> structures;
    std::vector<std::unique_ptr<Slingshot>> slingshots;

	// Static Slingshot Creation

    slingshots.push_back(std::make_unique<Slingshot>("../assets/Ang_Birds/slingshot.png", 150.f, 750.f, 0.8f));

	// Enemies, Birds, and Structures Creation

    enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Small, 830, 660));
    enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Medium, 1100, 640));
    enemies.push_back(std::make_unique<Enemy>(&world, EnemySize::Big, 585, 510));

    birds.push_back(std::make_unique<Bird>(&world, BirdType::Red, 100, 750));
    birds.push_back(std::make_unique<Bird>(&world, BirdType::Yellow, 100, 750));
    birds.push_back(std::make_unique<Bird>(&world, BirdType::Black, 50, 750));

    // Stone Structure Creation

    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 760, 750, -45));
    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 850, 750, 45));
    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 745, 750, 90));
    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 770, 695, 0));

    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 802, 750, 90));
    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 807, 750, 90));
    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 805, 690, 90));

    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 865, 750, 90));
    structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Stone, 840, 695, 0));

    // Wood Structure Creation

	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Wood, 950, 750, 90));
	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Wood, 1005, 750, 90));
	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Wood, 1060, 750, 90));

	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Wood, 975, 690, 0));
	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Wood, 1035, 690, 0));


	// Ice Structure Creation

	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Ice, 525, 750, 90));
	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Ice, 645, 750, 90));

	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Ice, 525, 715, 0));
	structures.push_back(std::make_unique<Structure>(&world, StructMaterial::Ice, 645, 715, 0));
	



    // Sets first bird in the vector to kinematic and places it at the set slingshot origin points.

    if (!birds.empty())
    {
        b2Body* body = birds.front().get()->getBody();

        body->SetTransform(b2Vec2(slingshotOrigin.x / SCALE, slingshotOrigin.y / SCALE), 0);
        body->SetType(b2_kinematicBody);
    }

	// Main Game Loop

    while (window.isOpen()) 
    {
        sf::Event event;

        while (window.pollEvent(event)) 
        {

			// Handle Window Close Event

            if (event.type == sf::Event::Closed)
                window.close();

			// Handle Mouse Input for Slingshot Dragging and Launching

            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
            {
                std::cout << "Left MB Pressed\n";
                if (!birds.empty() && !birdInFlight)
                {
                    isDragging = true;
                    birds.front()->setDragging(true);
                }
                
            }

			// Handle Mouse Release for Launching the Bird

            if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) 
            {
                std::cout << "Left MB Released\n";

                if (!birds.empty() && !birdInFlight) {

					// Calculate launch vector based on drag distance and direction, then apply impulse to the bird's body

                    Bird* bird = birds.front().get();
                    b2Body* body = bird->getBody();

                    sf::Vector2f birdPos(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);

                    sf::Vector2f launchVec = slingshotOrigin - birdPos;
                    
					// Set back to dynamic to be affected by physics and apply impulse based on drag distance

                    body->SetType(b2_dynamicBody);
                    body->ApplyLinearImpulseToCenter(b2Vec2(launchVec.x * launchStr, launchVec.y * launchStr), true);

					// Reset dragging state and mark bird as in flight

                    bird->setDragging(false);
                    isDragging = false;

					// Set bird as fired and activate it to start tracking its flight and enable abilities

                    birdInFlight = true;
                    bird->setFired(true);
                    bird->activate();
                }
                
            }

			// Handle Right Mouse Button Press for Activating Bird Abilities

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isAbilityPressed == false && birdInFlight && !birds.empty())
            {
				// Of statement checks for whether or not ability can be used, if it can, it is used and it sets a flag to prevent multi activation

                  birds.front().get()->activateAbility();
                  isAbilityPressed = true;
            }
        }

		// Safety Check to make sure there is a bird

        if (!birds.empty())
        {

            // Get current bird

            Bird* bird = birds.front().get();

			// Check if the bird has expired (lifetime exceeded)

            if (birdInFlight && bird->isExpired())
            {

				// Reset bird state and remove it from the world and vector, then prepare the next bird if available

                birdInFlight = false;
                isAbilityPressed = false;

                birds.erase(birds.begin());


                if (!birds.empty())
                {
                    Bird* nextBird = birds.front().get();
                    b2Body* body = nextBird->getBody();

                    body->SetType(b2_kinematicBody);
                    body->SetTransform( b2Vec2(slingshotOrigin.x / SCALE, slingshotOrigin.y / SCALE), 0);

                    body->SetLinearVelocity(b2Vec2(0, 0));
                    body->SetAngularVelocity(0);
                    body->SetAwake(true);
                }
            }
        }

		// Handle dragging the bird with the mouse while the left button is held down

        if (isDragging && !birds.empty())
        {
            b2Body* body = birds.front()->getBody();

			// Get mouse position in world coordinates and calculate drag vector from slingshot origin, then clamp it to max drag distance

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            sf::Vector2f mouseWorld(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            sf::Vector2f dragVector = mouseWorld - slingshotOrigin;

            dragVector.x = std::clamp(dragVector.x, -maxDragDistX, maxDragDistX);
            dragVector.y = std::clamp(dragVector.y, -maxDragDistY, maxDragDistY);

			// Set the bird's position to follow the mouse while dragging, converting from pixel coordinates to Box2D world coordinates

            sf::Vector2f newPosition = slingshotOrigin + dragVector;

            body->SetTransform(b2Vec2(newPosition.x / SCALE, newPosition.y / SCALE), 0);
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

		// Update Game Objects (enemies, birds, structures) and handle loading screen update

		if (loading) 
        {
			ui.Update();
            if (ui.isFinished()) { loading = false; }
		}
        else
        {
            for (auto& enemy : enemies) { enemy->Update(); }
            for (auto& bird : birds) { bird->Update(); }
            for (auto& structure : structures) { structure->Update(); }
        }

       

        for (const auto& hit : contactListener.hitEvents)
        {
            if (Enemy* enemy = dynamic_cast<Enemy*>(hit.target)) { enemy->takeDamage(hit.damage); }
            if (Structure* structure = dynamic_cast<Structure*>(hit.target)) { structure->takeDamage(hit.damage); }
        }

		// Enemy and Structure Removal Logic

        for (auto it = enemies.begin();
            it != enemies.end();)
        {
            if ((*it)->isDead())
            {
                world.DestroyBody((*it)->getBody());
                (*it)->invalidateBody();
                it = enemies.erase(it);
            }
            else { ++it; }
        }

        for (auto it = structures.begin();
            it != structures.end();)
        {
            if ((*it)->isDestroyed())
            {
                world.DestroyBody((*it)->getBody());
                (*it)->invalidateBody();
                it = structures.erase(it);
            }
            else { ++it; }
        }

		// Clear hit events after processing to prepare for the next frame's collisions

        contactListener.clear();

        sf_groundVisual.setPosition(b2_groundBody->GetPosition().x * SCALE, b2_groundBody->GetPosition().y * SCALE);
        sf_wallVisual.setPosition(b2_wallBody->GetPosition().x * SCALE, b2_wallBody->GetPosition().y * SCALE);

        window.clear(sf::Color(135, 206, 235)); 

        window.draw(sf_groundVisual);
        window.draw(sf_wallVisual);

		// Render Game Objects and UI, if loading screen is active, render it instead of game objects

        if (loading) { ui.Render(window); }
        else
        {
            for (auto& slingshot : slingshots) { slingshot->Render(window); }
            for (auto& enemy : enemies) { enemy->Render(window); }
            for (auto& bird : birds) { bird->Render(window); }
            for (auto& structure : structures) { structure->Render(window); }
        }

		// Draw the slingshot line while dragging a bird, connecting the slingshot origin to the bird's current position

        if (isDragging && !birds.empty())
        {
            b2Body* body = birds.front().get()->getBody();

            sf::Vector2f birdPos(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE );

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

