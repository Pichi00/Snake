#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Collectible: public sf::Drawable
{

public:
	Collectible(std::string texture);			//Konstruktor parametryczny
	void setPosition(float t_X, float t_Y);		//setter pozycji
	sf::Vector2f getPosition();					//getter pozycji
	void randomPosition();						//metoda zwraca losowe wspó³rzêdne na planszy
private:
	sf::Sprite collSprite;	
	sf::Texture collTexture;
	float collWidth{ 40.f };
	float collHeight{ 40.f };

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

