#include "Collectible.h"

const std::string collTexturePath = "Graphics/collectible.png";

Collectible::Collectible() {
	srand(time(NULL));
	if (!collTexture.loadFromFile(collTexturePath)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << collTexturePath << "\"" << std::endl;
	}
	collSprite.setTexture(collTexture);
	collSprite.setColor(sf::Color::Red);
	randomPosition();
}

void Collectible::setPosition(float t_X, float t_Y) {
	collSprite.setPosition(t_X, t_Y);
}

sf::Vector2f Collectible::getPosition() {
	return this->collSprite.getPosition();
}

void Collectible::randomPosition() {
	srand(time(NULL));
	float randX = 40.f * float(rand() % 18);
	float randY = 40.f * float(rand() % 18);
	std::cout << randX << std::endl << randY << std::endl;
	setPosition(randX, randY);
}

void Collectible::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->collSprite, state);
}