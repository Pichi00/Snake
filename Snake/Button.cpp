#include "Button.h"
sf::Color mainColor(60, 167, 58);
sf::Color hoverColor(50, 157, 48);

Button::Button(float t_X, float t_Y) {
	this->hoverCursor.loadFromSystem(sf::Cursor::Hand);
	this->defaultCursor.loadFromSystem(sf::Cursor::Arrow);	
	shape.setOrigin({ buttonWidth / 2, buttonHeight / 2 });
	shape.setPosition(t_X, t_Y);
	shape.setSize({ buttonWidth, buttonHeight });
	shape.setFillColor(mainColor);

	textSprite.setOrigin({ buttonWidth / 2, buttonHeight / 2 });
	textSprite.setPosition(t_X, t_Y);
	/*shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color::White);*/
}

float Button::left() {
	return shape.getPosition().x - buttonWidth / 2;
}
float Button::right() {
	return shape.getPosition().x + buttonWidth / 2;
}
float Button::top() {
	return shape.getPosition().y - buttonHeight / 2;
}
float Button::bottom() {
	return shape.getPosition().y + buttonHeight / 2;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(shape);
	target.draw(textSprite);
}

bool Button::isPressed(sf::RenderWindow& w) {
	if (isHovered(w) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return true;
	}
	else {
		return false;
	}

}
bool Button::isHovered(sf::RenderWindow& w) {
	if (sf::Mouse::getPosition(w).x > left() &&
		sf::Mouse::getPosition(w).x < right() &&
		sf::Mouse::getPosition(w).y > top() &&
		sf::Mouse::getPosition(w).y < bottom()) {

		shape.setFillColor(hoverColor);
		return true;
	}

	else {
		shape.setFillColor(mainColor);
		return false;
	}
}

void Button::setTextTexture(std::string texture_path) {
	textTexture.loadFromFile(texture_path);
	textSprite.setTexture(textTexture);
}

void Button::setScale(sf::Vector2f scale) {
	shape.setScale(scale);
	textSprite.setScale(scale);
}