#include "Collectible.h"


Collectible::Collectible(std::string texture) {	
	if (!collTexture.loadFromFile(texture)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << texture << "\"" << std::endl;
	}
	collSprite.setTexture(collTexture);
	collSprite.setOrigin(collWidth / 2, collHeight / 2);
	randomPosition();
}

void Collectible::setPosition(float t_X, float t_Y) {
	collSprite.setPosition(t_X, t_Y);
}

sf::Vector2f Collectible::getPosition() {
	return this->collSprite.getPosition();
}

void Collectible::randomPosition() {
	float randX = 40.f * float(rand() % 18) + collWidth/2;
	float randY = 40.f * float(rand() % 16 + 2) + collHeight/2;
	//std::cout << randX << std::endl << randY << std::endl;
	setPosition(randX, randY);
}

void Collectible::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->collSprite, state);
}