#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Button : public sf::Drawable
{
public:
	Button(float t_X, float t_Y);	//Konstruktor parametryczny
	Button() = default;				//Konstruktor domyœlny
	~Button() = default;			//Destruktor
	float left();	//Zwraca wspó³rzêdn¹ x lewej krawêdzi
	float right();	//Zwraca wspó³rzêdn¹ x prawej krawêdzi
	float top();	//Zwraca wspó³rzêdn¹ y górnej krawêdzi
	float bottom();	//Zwraca wspó³rzêdn¹ y dolnej krawêdzi
	bool isPressed(sf::RenderWindow& w);	//zwraca true jeœli wciœniemy przycisk
	bool isHovered(sf::RenderWindow& w);	//zwraca true jeœli najedziemy kursorem na przycisk
	void setTextTexture(std::string texture_path);	//ustawia teksture przycisku
	void setScale(sf::Vector2f);					//ustawia skalê przycisku

private:
	float buttonWidth = 300.0f;
	float buttonHeight = 50.0f;
	sf::RectangleShape shape;	
	sf::Sprite textSprite;		
	sf::Texture textTexture;	
	sf::Cursor hoverCursor;		
	sf::Cursor defaultCursor;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;	 
};