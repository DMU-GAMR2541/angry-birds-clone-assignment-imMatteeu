#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <string>

class UIText : public UIElement
{
public:
	UIText(const sf::Font& font, const std::string& initText = "", unsigned int charSize = 48, float posX = 0, float posY = 0);

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	void setText(const std::string& newText);
	void setColour(const sf::Color& colour);
	void setPosition(const sf::Vector2f& pos);

private:

	sf::Text text;

	float posX;
	float posY;

	void ReCenter();
};
