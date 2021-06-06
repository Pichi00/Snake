#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Button : public sf::Drawable
{
public:
	Button(float t_X, float t_Y);
	Button() = default;
	~Button() = default;
	float left();
	float right();
	float top();
	float bottom();
	bool isPressed(sf::RenderWindow& w);
	bool isHovered(sf::RenderWindow& w);
	void setTextTexture(std::string texture_path);
	void setScale(sf::Vector2f);

private:
	/*bool pressed = false;
	bool hovered = false;*/
	float buttonWidth = 300.0f;
	float buttonHeight = 50.0f;
	sf::RectangleShape shape;
	sf::Sprite textSprite;
	sf::Texture textTexture;
	sf::Cursor hoverCursor;
	sf::Cursor defaultCursor;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};