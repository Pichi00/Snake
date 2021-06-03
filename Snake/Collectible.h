#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Collectible: public sf::Drawable
{

public:
	void setPosition(float t_X, float t_Y);
	Collectible();
private:
	sf::Sprite collSprite;
	sf::Texture collTexture;
	float collScale;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

