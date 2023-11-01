#include "Gif.h"

void Gif::load(const sf::Texture& texture, int x, int y, int width, int height, int totalFrame)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->totalFrame = totalFrame;
	this->currentFrame = 0;
	this->cycle = 1;
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(x, y, width, height));
	frameSpeed = cycle / totalFrame;
}

void Gif::update()
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > frameSpeed) {
		this->currentFrame++;
		clock.restart();
	}
	if (this->currentFrame >= this->totalFrame) {
		this->currentFrame = 0;
	}
	this->sprite.setTextureRect(sf::IntRect(this->x + this->currentFrame * this->width, this->y, this->width, this->height));
}

void Gif::drawTo(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void Gif::setPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
}

void Gif::setScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

void Gif::setSpeed(double speed)
{
	this->cycle = speed;
}
