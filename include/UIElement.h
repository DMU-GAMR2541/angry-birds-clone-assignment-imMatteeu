#pragma once

#include "StaticObject.h"
#include "DynamicObject.h"

#include <SFML/Graphics.hpp>
#include <string>

enum class UIState
{
	Loading,
	Finished
};

class UIElement : public StaticObject, public DynamicObject
{
public:
	UIElement(const std::string& backdropPath);

	virtual ~UIElement() = default;

	void Update() override;
	void Render(sf::RenderWindow& window) override;

	void SetVisible(bool visible);
	void SetState(UIState state);

protected:

	bool visible = true;
	UIState state = UIState::Loading;
};