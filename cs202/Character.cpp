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
	this->upPressed = false;
	this->downPressed = false;
	this->leftPressed = false;
	this->rightPressed = false;
	this->counter = 0;
	this->blocked = false;
}

void Character::update()
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->gif.move(0, 10);
		if (this->shouldGoFaster()) {
			this->gif.move(0, 20);
			this->y += 20;
		}
		this->y += 10;
		clock.restart();
		if (upPressed) {
			this->gif.move(0, -16);
			this->y -= 16;
			counter++;
		}
		if (downPressed) {
			this->gif.move(0, 16);
			this->y += 16;
			counter++;
		}
		if (leftPressed) {
			this->gif.move(-16, 0);
			this->x -= 16;
			counter++;
		}
		if (rightPressed) {
			this->gif.move(16, 0);
			this->x += 16;
			counter++;
		}
		if (counter == 4) {
			upPressed = false;
			downPressed = false;
			leftPressed = false;
			rightPressed = false;
			counter = 0;
		}
	}
	else
		gif.update();
	if (this->y > 900) {
		this->dead = true;
	}
}

void Character::up()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	this->y -= 64;
	this->gif.move(0, -64);
	upPressed = true;
}

void Character::down()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->y + 64 >= 900)
		return;
	this->y += 64;
	this->gif.move(0, 64);
	downPressed = true;
}

void Character::left()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->x - 64 <= 0)
		return;
	this->x -= 64;
	this->gif.move(-64, 0);
	leftPressed = true;
}

void Character::right()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->x + 64 >= 1600)
		return;
	this->x += 64;
	this->gif.move(64, 0);
	rightPressed = true;
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