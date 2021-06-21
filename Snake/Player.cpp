#include "Player.h"

const std::string playerTexturePath = "Graphics/player.png";
const std::string playerHeadTexturePath = "Graphics/player-head.png";
const std::string playerBodyTexturePath = "Graphics/player-body.png";
const std::string playerTailTexturePath = "Graphics/player-tail.png";

Player::Player(float t_X, float t_Y) {
	playerSprite.setPosition(0, 0);
	playerSprite.setOrigin(playerWidth / 2, playerHeight / 2);
	playerSprite.setPosition(playerWidth / 2, playerHeight / 2);
	if (!playerTexture.loadFromFile(playerTexturePath)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerTexturePath << "\"" << std::endl;
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(playerScale, playerScale);
}


void Player::setPosition(float t_X, float t_Y) {
	playerSprite.setPosition(t_X, t_Y);
}

void Player::setColor(sf::Color c) {
	playerSprite.setColor(c);
}

void Player::setTexture(int x, char rot, int size) {
	if (x == 0) {
		if (!playerTexture.loadFromFile(playerHeadTexturePath)) {
			std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerHeadTexturePath << "\"" << std::endl;
		}
		playerSprite.setRotation(90 * rot);
	}
	else if (x == size) {
		if (!playerTexture.loadFromFile(playerTailTexturePath)) {
			std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerTailTexturePath << "\"" << std::endl;
		}
		playerSprite.setRotation(90 * rot);
	}
	else {
		if (!playerTexture.loadFromFile(playerBodyTexturePath)) {
			std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerBodyTexturePath << "\"" << std::endl;
		}
	}

	playerSprite.setTexture(playerTexture);
	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->playerSprite, state);
}
