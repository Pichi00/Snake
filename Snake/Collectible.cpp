#include "Collectible.h"

const std::string collTexturePath = "Graphics/collectible.png";

Collectible::Collectible() {
	if (!collTexture.loadFromFile(collTexturePath)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << collTexturePath << "\"" << std::endl;
	}
	collSprite.setTexture(collTexture);
	collSprite.setColor(sf::Color::Red);

}

void Collectible::setPosition(float t_X, float t_Y) {
	collSprite.setPosition(t_X, t_Y);
}

void Collectible::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->collSprite, state);
}