#include "UIImage.h"
#include <iostream>

UIImage::UIImage(const std::string& texturePath,
    const sf::Vector2f& position,
    const sf::Vector2f& size)
    : UIElement("")
{
    if (texturePath == "") {
        std::cout << "Empty File Path" << std::endl;

    }
    else if (!texture.loadFromFile(texturePath) && texturePath != "")
    {
        std::cout << "Failed to load UI image: " << texturePath << std::endl;
        loaded = false;
        return;
    }

    loaded = true;

    sprite.setTexture(texture);
    sprite.setPosition(position);

    sf::Vector2u texSize = texture.getSize();

    sprite.setScale(
        size.x / texSize.x,
        size.y / texSize.y
    );

    visible = true;
    state = UIState::Loading;
}

void UIImage::Update()
{
    if (!visible || state == UIState::Finished || !loaded)
        return;
}

void UIImage::Render(sf::RenderWindow& window)
{
    if (!visible || state == UIState::Finished || !loaded)
        return;

    window.draw(sprite);
}