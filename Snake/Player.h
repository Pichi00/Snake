#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player: public sf::Drawable
{
public:
	Player(float t_X, float t_Y);
	void update(char dir);
	void setPosition(float t_X, float t_Y);
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	float playerSpeed{ 2.f };
	float playerWidth{ 40.f };
	float playerHeight{ 40.f };
	float playerScale{ 1.f };
	sf::Vector2f playerVelocity{1,0};

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

