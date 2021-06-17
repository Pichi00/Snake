#pragma once
#include "Collectible.h"
class SlowBonus : public sf::Drawable
{
public:
	SlowBonus();
	void setPosition(float t_X, float t_Y);
	sf::Vector2f getPosition();
	void randomPosition();
private:
	sf::Sprite collSprite;
	sf::Texture collTexture;
	float collWidth{ 40.f };
	float collHeight{ 40.f };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

