#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player: public sf::Drawable
{
public:
	Player(float t_X, float t_Y);
	void update();
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	float playerSpeed{ 0.6 };
	float playerWidth{ 64.f };
	float playerHeight{ 64.f };
	float playerScale{ 0.5 };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

