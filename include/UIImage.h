#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <string>

class UIImage : public UIElement
{
public:
	UIImage(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size);

	virtual ~UIImage() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	void setPosition(const sf::Vector2f& pos);
	void setVisible(bool vis);

protected:

	bool loaded = false;

private:

	sf::Texture texture;
	sf::Sprite sprite;

};
