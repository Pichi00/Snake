#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Collectible: public sf::Drawable
{

public:
	Collectible();
	void setPosition(float t_X, float t_Y);
	sf::Vector2f getPosition();
	void randomPosition();
private:
	sf::Sprite collSprite;
	sf::Texture collTexture;
	float collScale{ 1.f };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

