#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <thread>
#include <chrono>


class Player: public sf::Drawable
{
public:
	Player(float t_X, float t_Y);				//Konstruktor parametryczny
	void setPosition(float t_X, float t_Y);		//setter pozycji
	void setColor(sf::Color c);					//setter koloru
	void setTexture(int x, char rot, int size);	//setter tekstury
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

