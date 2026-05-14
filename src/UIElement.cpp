#include "UIElement.h"
#include <SFML/Graphics.hpp >
#include <iostream>

//--------------------------------------------------
// Constructor
//--------------------------------------------------

UIElement::UIElement(
    const std::string& backdropPath,
    const sf::Font& font
)
    : StaticObject(backdropPath, 0.f, 0.f, 1920.f, 1080.f),
    DynamicObject(nullptr, EntityData{}, 0.f, 0.f, 0.f, false)
{
    // ONLY UI-specific setup

    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
    text.setString("Loading: 0%");

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    text.setPosition(600.f, 700.f);

    state = UIState::Loading;
    progress = 0.f;
}

void UIElement::Update()
{
    switch (state)
    {
    case UIState::Loading:
        UpdateLoading();
        break;

    case UIState::Finished:
        return;
    }

    StaticObject::Update();
}

void UIElement::UpdateLoading()
{
    progress += 0.5f; // speed of loading

    if (progress > 100.f)
        progress = 100.f;

    text.setString("Loading: " + std::to_string((int)progress) + "%");

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    if (progress >= 100.f)
    {
        state = UIState::Finished;
        onFinished();
    }
}

void UIElement::Render(sf::RenderWindow& window)
{
    if (state == UIState::Loading)
    {
        StaticObject::Render(window); 
        window.draw(text);            
    }
}
void UIElement::onFinished()
{}

bool UIElement::isFinished()
{
    return state == UIState::Finished;
}