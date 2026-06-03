#include "UIElement.h"
#include <SFML/Graphics.hpp >
#include <iostream>

// UIElement Constructor

UIElement::UIElement(
    const std::string& backdropPath
)
    : StaticObject(backdropPath, 0.f, 0.f, 1920.f, 1080.f),
    DynamicObject(nullptr, EntityData{}, 0.f, 0.f, 0.f, false)
{
    visible = true;
    state = UIState::Loading;
}

void UIElement::Update()
{
    if (!visible || state == UIState::Finished) return;


    StaticObject::Update();
}

void UIElement::Render(sf::RenderWindow& window)
{
    if (!visible || state == UIState::Finished) return;
    
    StaticObject::Render(window);             
}

void UIElement::SetVisible(bool vis) 
{
    visible = vis;
}

void UIElement::SetState(UIState newState)
{
    state = newState;
}