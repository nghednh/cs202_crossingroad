#include "Lane.h"
#include <cstdlib>
#include <iostream>

GrassLane::GrassLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	nob = rand() % 11 + 1;
	this->ob = new ObjectStable [nob];
	initOb(rock);
}

void GrassLane::initOb(sf::Texture& rock) {
	int a = -1;
	//std::cout << nob;
	int b = -2;
	for (int i = 0; i < nob; i++) {
		this->ob[i].setup(rock);
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
		this->sprite.move(0, 10);
		moveobx(15, 10);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 20);
			moveobx(0,  20);
			y += 20;
		}
		y += 10;
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
	nob = rand()%10+1;
	this->ob = new ObjectMoving[nob];
	initOb(car);

}

void RoadLane::initOb(sf::Texture& rock) {

	int a = -1;
	//std::cout << nob;
	int b = -2;
	bool bef;
	for (int i = 0; i < nob; i++) {
		if (i==0) {
			this->ob[i].setup(rock);
			//ob[i].randomx();
			b = ob[i].randomx();
			while (a == b) b = ob[i].randomx();
			a = b;
			ob[i].setPos(ob[i].returnx(), y);
			if (ob[i].rfleft()) ob[i].setScale(-1, 1);
			bef = ob[i].rfleft();
		}
		else {
			this->ob[i].setup(rock);
			ob[i].randomxx(bef);
			b = ob[i].randomxx(bef);
			while (a == b) b = ob[i].randomxx(bef);
			a = b;
			ob[i].setPos(ob[i].returnx(), y);
			if (ob[i].rfleft()) ob[i].setScale(-1, 1);
		}
		
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
		this->sprite.move(0, 10);
		moveobx(15, 10);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 20);
			moveobx(0, 20);
			y += 20;
		}
		y += 10;
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
	this->train = new TrainObject;
	initOb(train);
	
}

void RailLane::initOb(sf::Texture& rock) {
	this->train->setup(rock);
	this->train->randomx();
	this->train->setPos(train->returnx(), y);
	if (this->train->rfleft())  this->train->setScale(-1, 1);
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
		this->sprite.move(0, 10);
		if (this->greenLight()) moveobx(50, 10);
		else moveobx(0, 10);
		if (shouldGoFaster)
		{
			this->sprite.move(0, 20);
			moveobx(0, 20);
			y += 20;
		}
		y += 10;
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
	this->train.loadFromFile("resource/object/trainLeft.png");
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
Lane::~Lane() {}
GrassLane::~GrassLane() {
	delete [] ob;
}
RoadLane::~RoadLane() {
	delete [] ob;
}
RailLane::~RailLane() {
	delete train;
}