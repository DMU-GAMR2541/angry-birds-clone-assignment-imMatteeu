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
	UIElement(const std::string& backdropPath,
		const sf::Font& font);

	void Update() override;

	void Render(sf::RenderWindow& window) override;
	void onFinished();
	bool isFinished();

private:

	void UpdateLoading();

	UIState state = UIState::Loading;
	float progress = 0.f;

	sf::Text text;
};