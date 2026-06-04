#include "UIText.h"

UIText::UIText(const sf::Font& font,
    const std::string& initialText,
    unsigned int characterSize,
    float x, float y)
    : UIElement("")
{
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White);
    text.setString(initialText);

    ReCenter();

    posX = x;
    posY = y;
}

void UIText::Update()
{
    if (!visible || state == UIState::Finished)
        return;
}

void UIText::Render(sf::RenderWindow& window)
{
    if (!visible || state == UIState::Finished)
        return;

    window.draw(text);
}

void UIText::setText(const std::string& newText)
{
    text.setString(newText);
    ReCenter();
}

void UIText::setColour(const sf::Color& colour)
{
    text.setFillColor(colour);
}

void UIText::setPosition(const sf::Vector2f& pos)
{
    text.setPosition(pos);
}

void UIText::ReCenter()
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    text.setPosition(posX, posY);
}