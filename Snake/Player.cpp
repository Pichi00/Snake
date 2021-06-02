#include "Player.h"

const std::string playerTexturePath = "Graphics/player.png";

Player::Player(float t_X, float t_Y) {
	playerSprite.setPosition(0, 0);
	//playerSprite.setOrigin(playerWidth / 2, playerHeight / 2);
	//playerSprite.setPosition(t_X, t_Y);
	if (!playerTexture.loadFromFile(playerTexturePath)) {
		std::cout << "Blad ladowania tekstury gracza. Upewnij sie, ze posiadasz plik \"" << playerTexturePath << "\"" << std::endl;
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(playerScale, playerScale);
}

void Player::update( char dir) {
	playerSprite.move(playerVelocity * playerSpeed);
}

void Player::setPosition(float t_X, float t_Y) {
	playerSprite.setPosition(t_X, t_Y);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->playerSprite, state);
}

