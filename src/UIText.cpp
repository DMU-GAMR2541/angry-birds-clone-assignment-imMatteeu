#include "UIText.h"

//------------------------------------------------------------
// Constructor
//------------------------------------------------------------
UIText::UIText(const sf::Font& font,
    const std::string& initialText,
    unsigned int characterSize)
    : UIElement("")
{
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White);
    text.setString(initialText);

    ReCenter();
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
    text.setPosition(600.f, 750.f);
}