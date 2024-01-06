#include "Character.h"

Character::Character()
{
	this->jumping.loadFromFile("resource/character/jumping.png");
	this->flash.loadFromFile("resource/character/die2.png");
	this->speed = 1;
	this->gif.load(this->flash, 0, 0, 32, 32, 7, 0.35 * speed);
	this->gif.setScale(3, 3);
	this->x = 7 * 128;
	this->y = 900 - 128 * 2;
	this->gif.setPosition(this->x, this->y);
	this->normal.setTexture(this->jumping);
	this->normal.setScale(3, 3);
	this->normal.setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->width = 32;
	this->height = 32;
	this->dead = false;
	this->crashed = false;
	this->isOutOfScreen = false;
	this->upPressed = false;
	this->downPressed = false;
	this->leftPressed = false;
	this->rightPressed = false;
	this->counter = 0;
	this->blocked = false;
	this->index = 3;
	this->position = 7;
}

void Character::update()
{
	if (this->y > 900)
		this->dead = true;
	double time = clock.getElapsedTime().asMilliseconds();
	if (time >= 50 * speed) {
		clock.restart();
		if (upPressed) {
			//this->y -= 64;
			if (counter == 2)
			{
				index++;
				this->x = position * 128;
				this->gif.setPosition(x, y);
			}
			counter++;
		}
		if (downPressed) {
			//this->y += 64;
			if (counter == 2)
			{
				index--;
				this->x = position * 128;
				this->gif.setPosition(x, y);
			}
			counter++;
		}
		if (leftPressed) {
			//this->x -= 64;
			if (counter == 2)
			{
				position--;
				this->x = position * 128;
				this->gif.setPosition(x, y);
			}
			counter++;
		}
		if (rightPressed) {
			//this->x += 64;
			if (counter == 2)
			{
				position++;
				this->x = position * 128;
				this->gif.setPosition(x, y);
			}
			counter++;
		}
		if (counter == 5) {
			upPressed = false;
			downPressed = false;
			leftPressed = false;
			rightPressed = false;
			counter = 0;
			//std::cout << this->x << " " << this->y << " index: " << this->index << " pos: " << this->position << std::endl;

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
	if (this->y - 128 < 0)
		return;
	upPressed = true;
	gif.setFrame(0);
	//std::cout << this->x << " " << this->y << std::endl;
}

void Character::down()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->y + 128 >= 900)
		return;
	downPressed = true;
	gif.setFrame(0);
	//std::cout << this->x << " " << this->y << std::endl;
}

void Character::left()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->x - 128 < 0)
		return;
	leftPressed = true;
	gif.setFrame(0);
	//std::cout << this->x << " " << this->y << std::endl;
}

void Character::right()
{
	if (upPressed || downPressed || leftPressed || rightPressed)
		return;
	if (this->x + 128 > 1600)
		return;
	rightPressed = true;
	gif.setFrame(0);
	//std::cout << this->x << " " << this->y << std::endl;
}

void Character::draw(sf::RenderWindow& window)
{
	if (!dead && !crashed)
		if (upPressed || downPressed || leftPressed || rightPressed)
			this->gif.drawTo(window);
		else {

			normal.setPosition(this->x, this->y);
			window.draw(normal);
		}
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

void Character::die()
{
	this->dead = true;
	this->crashed = true;
}

void Character::reset()
{
	this->dead = false;
	this->crashed = false;
	this->isOutOfScreen = false;
	this->upPressed = false;
	this->downPressed = false;
	this->leftPressed = false;
	this->rightPressed = false;
	this->counter = 0;
	this->blocked = false;
	this->index = 3;
	this->position = 7;
	this->x = 7 * 128;
	this->y = 900 - 128 * 2;
	this->gif.setPosition(this->x, this->y);
}

string Character::info()
{
	string res = "";
	res += to_string(x);
	res += " ";
	res += to_string(y);
	res += " ";
	res += to_string(speed);
	if (dead) res += " 1";
	else res += " 0";
	res += " ";
	res += to_string(position);
	res += " ";
	res += to_string(index);
	return res;
}

void Character::setInfoFromFile(string charInfo)
{
	istringstream iss(charInfo);
	string xChar, yChar, posChar, indChar, speedChar, deadChar;
	iss >> xChar;
	iss >> yChar;
	iss >> speedChar;
	iss >> deadChar;
	iss >> posChar;
	iss >> indChar;

	this->x = stoi(xChar);
	this->y = stoi(yChar);
	this->speed = stod(speedChar);
	this->dead = stoi(deadChar);
	this->position = stoi(speedChar);
	this->index = stoi(indChar) - 1;
}

