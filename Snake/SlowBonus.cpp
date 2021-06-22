#include "SlowBonus.h"

SlowBonus::SlowBonus() {
	srand(time(NULL));
	if (!collTexture.loadFromFile("Graphics/slow.png")) {
		std::cout << "Error: Texture not found."<< std::endl;
	}
	collSprite.setTexture(collTexture);
	collSprite.setOrigin(collWidth / 2, collHeight / 2);
	setPosition(0, 0);
	std::cout << "XDD" << std::endl;
}

void SlowBonus::setPosition(float t_X, float t_Y) {
	collSprite.setPosition(t_X, t_Y);
}

sf::Vector2f SlowBonus::getPosition() {
	return this->collSprite.getPosition();
}

void SlowBonus::randomPosition() {
	srand(time(NULL));
	float randX = 40.f * float(rand() % 18) + collWidth / 2;
	float randY = 40.f * float(rand() % 16 + 2) + collHeight / 2;
	//std::cout << randX << std::endl << randY << std::endl;
	setPosition(randX, randY);
}

void SlowBonus::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->collSprite, state);
}
