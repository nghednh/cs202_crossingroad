#include "Character.h"

Character::Character()
{
	this->jumping.loadFromFile("resource/character/jumping.png");
	this->gif.load(this->jumping, 0, 0, 32, 32, 8, 1);
	this->gif.setScale(3, 3);
	this->x = 7*128;
	this->y = 900 - 128*2;
	this->gif.setPosition(this->x, this->y);
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
	this->index = 3;
	this->position = 7;
	this->laneXOffset = 0;
	this->laneYOffset = 0;
}

void Character::update()
{
	double time = clock.getElapsedTime().asMilliseconds();
	if (time >= 50) {
		this->gif.move(0, 5);
		this->y += 5;
		clock.restart();
		if (upPressed) {
			this->y -= 64;
			this->gif.setPosition(x, y);
			if (counter == 1)
				index++;
			counter++;
		}
		if (downPressed) {
			this->y += 64;
			this->gif.setPosition(x, y);
			if (counter == 1)
				index--;
			counter++;
		}
		if (leftPressed) {
			this->x -= 64;
			this->gif.setPosition(x, y);
			if (counter == 1)
				position--;
			counter++;
		}
		if (rightPressed) {
			this->x += 64;
			this->gif.setPosition(x, y);
			if (counter == 1)
				position++;
			counter++;
		}
		if (counter == 2) {
			upPressed = false;
			downPressed = false;
			leftPressed = false;
			rightPressed = false;
			counter = 0;
			std::cout << this->x << " " << this->y << " index: " << this->index << std::endl;
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
	upPressed = true;
	std::cout << this->x << " " << this->y << std::endl;
}

void Character::down()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->y + 128 >= 900)
		return;
	downPressed = true;
	std::cout << this->x << " " << this->y << std::endl;
}

void Character::left()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->x - 128 <= 0)
		return;
	leftPressed = true;
	std::cout << this->x << " " << this->y << std::endl;
}

void Character::right()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->x + 128 >= 1600)
		return;
	rightPressed = true;
	std::cout << this->x << " " << this->y << std::endl;
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