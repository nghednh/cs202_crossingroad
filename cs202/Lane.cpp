#include "Lane.h"
#include <cstdlib>
#include <iostream>

Lane::Lane(sf::Texture& texture, int y, bool isGrass, sf::Texture& rock, sf::Texture& car)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->isGrass = isGrass;
	nob = rand() % 5 + 1;
	if (isGrass) {
		this->ob = new ObjectStable[nob];
		initOb(rock);
	}
	else {
		nob = 1;
		this->ob = new ObjectMoving[nob];
		initOb(car);
	}
}
void Lane::initOb(sf::Texture& rock) {

	int a = -1;
	//std::cout << nob;
	int b = -2;
	for (int i = 0; i < nob; i++) {
		this->ob[i].setup(rock);
		ob[i].randomx();
		b = ob[i].randomx();
		while (a == b) b = ob[i].randomx();
		a = b;
		ob[i].setPos(ob[i].returnx(), y);
	}
}
void Lane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	window.draw(this->sprite);
	for (int i=0; i<nob; i++)
	{
		ob[i].drawTo(window);
	}

}

void Lane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->sprite.move(0, 2);
		moveobx(15,2);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 3);
			moveobx(0,3);
			y += 3;
		}
		y += 2;
		clock.restart();
	}
}
void Lane::moveobx(int a,int b) {
	for (int i = 0; i < nob; i++) {
		if (isGras())this->ob[i].move(0, b);
		else if (ob[i].rfleft()) this->ob[i].move(a, b);
		else this->ob[i].move(-a, b);
	}
}

LaneManager::LaneManager()
{
	this->difficulty = 0;
	this->width = 1600;
	this->height = 128;
	this->texture[0].loadFromFile("resource/tiles/road.png");
	this->texture[1].loadFromFile("resource/tiles/road.png");
	this->texture[2].loadFromFile("resource/tiles/grass0.png");
	this->texture[3].loadFromFile("resource/tiles/grass1.png");
	this->texture[4].loadFromFile("resource/tiles/grass2.png");
	this->texture[5].loadFromFile("resource/tiles/grass3.png");
	this->rock.loadFromFile("resource/object/object.png");
	this->car.loadFromFile("resource/object/vehicle/left0.png");
}

void LaneManager::addLane(int y)
{
	int random = rand() % 100;
	if (random < 20)
		this->lanes.insert(lanes.begin(), Lane(this->texture[1], y, false,rock,car));
	else if (random < 40)
		this->lanes.insert(lanes.begin(), Lane(this->texture[2], y, true,rock,car));
	else if (random < 60)
		this->lanes.insert(lanes.begin(), Lane(this->texture[3], y, true,rock,car));
	else if (random < 80)
		this->lanes.insert(lanes.begin(), Lane(this->texture[4], y, true,rock,car));
	else
		this->lanes.insert(lanes.begin(), Lane(this->texture[5], y, true,rock,car));
}

void LaneManager::update(bool& shouldGoFaster)
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		this->lanes[i].move(shouldGoFaster);
	}
	if (this->lanes[0].isOutOfScreen(this->height))
	{
		lanes.pop_back();
		this->addLane(lanes[0].getY()-128);
	}
}

void LaneManager::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < this->lanes.size(); i++)
		this->lanes[i].drawTo(window);
}
