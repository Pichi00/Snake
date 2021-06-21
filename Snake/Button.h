#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Button : public sf::Drawable
{
public:
	Button(float t_X, float t_Y);	//Konstruktor parametryczny
	Button() = default;				//Konstruktor domy�lny
	~Button() = default;			//Destruktor
	float left();	//Zwraca wsp�rz�dn� x lewej kraw�dzi
	float right();	//Zwraca wsp�rz�dn� x prawej kraw�dzi
	float top();	//Zwraca wsp�rz�dn� y g�rnej kraw�dzi
	float bottom();	//Zwraca wsp�rz�dn� y dolnej kraw�dzi
	bool isPressed(sf::RenderWindow& w);	//zwraca true je�li wci�niemy przycisk
	bool isHovered(sf::RenderWindow& w);	//zwraca true je�li najedziemy kursorem na przycisk
	void setTextTexture(std::string texture_path);	//ustawia teksture przycisku
	void setScale(sf::Vector2f);					//ustawia skal� przycisku

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