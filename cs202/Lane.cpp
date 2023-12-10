#include "Lane.h"
#include <cstdlib>
#include <iostream>

GrassLane::GrassLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	nob = rand() % 5 + 1;
	this->ob = new ObjectStable[nob];
	initOb(rock);
}

void GrassLane::initOb(sf::Texture& rock) {
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

void GrassLane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window);
	}

}

void GrassLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->sprite.move(0, 2);
		moveobx(15, 2);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 3);
			moveobx(0, 3);
			y += 3;
		}
		y += 2;
		clock.restart();
	}
}

void GrassLane::moveobx(int a, int b) {
	for (int i = 0; i < nob; i++) {
		this->ob[i].move(0, b);
	}
}

RoadLane::RoadLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	nob = 1;
	this->ob = new ObjectMoving[nob];
	initOb(car);
}

void RoadLane::initOb(sf::Texture& rock) {

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
		if (ob[i].rfleft()) ob[i].setScale(-1, 1);
	}
}

void RoadLane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window);
	}
}

void RoadLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->sprite.move(0, 2);
		moveobx(15, 2);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 3);
			moveobx(0, 3);
			y += 3;
		}
		y += 2;
		clock.restart();
	}
}

void RoadLane::moveobx(int a, int b) {
	for (int i = 0; i < nob; i++) {
		if (ob[i].rfleft()) this->ob[i].move(a, b);
		else this->ob[i].move(-a, b);
	}
}

RailLane::RailLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	this->train = new ObjectMoving;
	initOb(train);
}

void RailLane::initOb(sf::Texture& rock) {
	this->train->setup(rock);
	this->train->setPos(0, y);
}

void RailLane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	window.draw(this->sprite);
	this->train->drawTo(window);
}

void RailLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->sprite.move(0, 2);
		moveobx(15, 2);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 3);
			moveobx(0, 3);
			y += 3;
		}
		y += 2;
		clock.restart();
	}
}

void RailLane::moveobx(int a, int b) {
	if (train->rfleft()) this->train->move(a, b);
	else train->move(-a, b);
}

LaneManager::LaneManager()
{
	this->difficulty = 0;
	this->width = 1600;
	this->height = 128;
	this->index = 1;
	this->texture[0].loadFromFile("resource/tiles/train1.png");
	this->texture[1].loadFromFile("resource/tiles/road.png");
	this->texture[2].loadFromFile("resource/tiles/grass0.png");
	this->texture[3].loadFromFile("resource/tiles/grass1.png");
	this->texture[4].loadFromFile("resource/tiles/grass2.png");
	this->texture[5].loadFromFile("resource/tiles/grass3.png");
	this->rock.loadFromFile("resource/object/object.png");
	this->car.loadFromFile("resource/object/vehicle/left0.png");
	this->train.loadFromFile("resource/object/trainRight.png");
}

LaneManager::~LaneManager()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		delete lanes[i];
	}
}

void LaneManager::addLane(int y)
{
	int random = rand() % 100;
	if (random < 20)
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, rock, car, train, index));
	else if (random < 40)
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, rock, car, train, index));
	else if (random < 60)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[2], y, rock, car, train, index));
	else if (random < 80)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[3], y, rock, car, train, index));
	else if (random < 90)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[4], y, rock, car, train, index));
	else
		this->lanes.insert(lanes.begin(), new RailLane(this->texture[0], y, rock, car, train, index));
	index++;
	std::cout << "added lane with index: " << index << std::endl;
}

void LaneManager::update(bool& shouldGoFaster)
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		lanes[i]->move(shouldGoFaster);
	}
	if (lanes[0]->isOutOfScreen(this->height))
	{
		delete lanes.back();
		lanes.pop_back();
		addLane(lanes[0]->getY() - 128);
	}
}

void LaneManager::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < this->lanes.size(); i++)
		lanes[i]->drawTo(window);
}
