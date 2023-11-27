#include "Character.h"

Character::Character()
{
	this->jumping.loadFromFile("resource/character/jumping.png");
	this->gif.load(this->jumping, 0, 0, 32, 32, 8, 2);
	this->gif.setScale(3, 3);
	this->x = 0;
	this->y = 32;
	this->width = 32;
	this->height = 32;
	this->speed = 0.05;
	this->dead = false;
	this->isOutOfScreen = false;
}

void Character::update()
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->gif.move(0, 2);
		if (this->shouldGoFaster()) {
			this->gif.move(0, 3);
			this->y += 3;
		}
		this->y += 2;
		clock.restart();
	}
	if (this->y > 900) {
		this->dead = true;
	}
	gif.update();
}

void Character::up()
{
	this->y -= 64;
	this->gif.move(0, -64);
}

void Character::down()
{
	if (this->y + 64 >= 900)
		return;
	this->y += 64;
	this->gif.move(0, 64);
}

void Character::left()
{
	if (this->x - 64 <= 0)
		return;
	this->x -= 64;
	this->gif.move(-64, 0);
}

void Character::right()
{
	if (this->x + 64 >= 1600)
		return;
	this->x += 64;
	this->gif.move(64, 0);
}

void Character::draw(sf::RenderWindow& window)
{
	this->gif.drawTo(window);
}

bool Character::isDead()
{
	return this->dead;
}

bool Character::shouldGoFaster()
{
	if (this->y < 250)
		return true;
	return false;
}