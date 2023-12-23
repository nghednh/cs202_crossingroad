#include "Lane.h"
#include <cstdlib>
#include <iostream>

GrassLane::GrassLane(sf::Texture& texture, int y, sf::Texture& plant, sf::Texture& rock1, sf::Texture& rock2, sf::Texture& car, sf::Texture& train, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	nob = rand() % 9 + 1;
	this->ob = new ObjectStable[nob];
	initOb(plant, rock1, rock2);
	this->character = nullptr;
	this->type = GRASS;
}

void GrassLane::initOb(sf::Texture& plant, sf::Texture& rock1, sf::Texture& rock2) {
	int a = -1;
	//std::cout << nob;
	int b = -2;
	bool* idx = new bool[13];
	for (int i = 0; i < 13; i++) {
		idx[i] = 0;
	}
	for (int i = 0; i < nob; i++) {
		int tmp = 0;
		if (rand() % 3 == 0) {
			this->ob[i].setup(rock1, 2, 2, 195, -9, 64, 70);
		}
		else if (rand() % 3 == 2) {
			this->ob[i].setup(rock2, 2, 2, 384, 194, 64, 64);
			tmp = 1;
		}
		else {
			this->ob[i].setup(plant, 2, 2, 216, 185, 47, 42);
			tmp = 2;
		}
		b = ob[i].randomx(idx, 13);
		while (a == b) b = ob[i].randomx(idx, 13);
		a = b;
		if (tmp == 1) {
			ob[i].setPos(ob[i].returnx(), y+30);
		}
		else if (tmp == 2) {
			ob[i].setPos(ob[i].returnx(), y+50);
		}
		else ob[i].setPos(ob[i].returnx(), y);
	}
	delete[] idx;
}

void GrassLane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	//window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window);
	}
	if (this->character != nullptr)
		this->character->draw(window);
}

void GrassLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.05) {
		y += 5;
		this->sprite.setPosition(0, y);
		moveobx(15, 5);
		clock.restart();
	}
}

void GrassLane::processUp(Character* character) {
	for (int i = 0; i < nob; i++) {
		if (character->position == ob[i].returnx()) {
			std::cout << "BLOCKED UP GRASS" << std::endl;
			return;
		}
	}
	character->up();
}

void GrassLane::processDown(Character* character)
{
	for (int i = 0; i < nob; i++) {
		if (character->position == ob[i].returnx()) {
			std::cout << "BLOCKED DOWN GRASS" << std::endl;
			return;
		}
	}
	character->down();
}

void GrassLane::processLeft(Character* character)
{
	for (int i = 0; i < nob; i++) {
		if (character->position - 1 == ob[i].returnx()) {
			std::cout << "BLOCKED LEFT GRASS" << std::endl;
			return;
		}
	}
	character->left();
}

void GrassLane::processRight(Character* character)
{
	for (int i = 0; i < nob; i++) {
		if (character->position + 1 == ob[i].returnx()) {
			std::cout << "BLOCKED RIGHT GRASS" << std::endl;
			return;
		}
	}
	character->right();
}

void GrassLane::moveobx(int a, int b) {
	for (int i = 0; i < nob; i++) {
		this->ob[i].move(0, b);
	}
}

RoadLane::RoadLane(sf::Texture& texture, int y, sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	nob = rand() % 10 + 1;
	this->ob = new ObjectMoving[nob];
	initOb(car1, car2, car3, car4, car5);
	this->character = nullptr;
	this->type = ROAD;
}

void RoadLane::initOb(sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5) {

	int a = -1;
	//std::cout << nob;
	int b = -2;
	bool bef;
	bool* idx = new bool[13];
	for (int i = 0; i < 13; i++) {
		idx[i] = 0;
	}
	for (int i = 0; i < nob; i++) {
		int rdm = rand() % 5;
		switch (rdm) {
			case 1:
			{
				this->ob[i].setup(car1, 2.56, 2.56, 0, 0, 100, 100);
				break;
			}
			case 2:
			{
				this->ob[i].setup(car2, 2.56, 2.56, 0, 0, 100, 100);
				break;
			}
			case 3:
			{
				this->ob[i].setup(car3, 2.56, 2.56, 0, 0, 100, 100);
				break;
			}
			case 4:
			{
				this->ob[i].setup(car4, 2.56, 2.56, 0, 0, 100, 100);
				break;
			}
			case 5:
			{
				this->ob[i].setup(car5, 2.56, 2.56, 0, 0, 100, 100);
				break;
			}
		}
		if (i == 0) {
			//ob[i].randomx();
			b = ob[i].randomx();
			while (a == b) b = ob[i].randomx();
			a = b;
			ob[i].setPos(ob[i].returnx(), y);
			if (ob[i].rfleft()) ob[i].setScale(-2.56, 2.56);
			bef = ob[i].rfleft();
		}
		else {
			//ob[i].randomxx(bef, idx);
			b = ob[i].randomxx(bef, idx);
			while (a == b) b = ob[i].randomxx(bef, idx);
			a = b;
			ob[i].setPos(ob[i].returnx(), y);
			if (ob[i].rfleft()) ob[i].setScale(-2.56, 2.56);
		}
	}
	delete[] idx;
}

void RoadLane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	//window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window);
	}
	if (this->character != nullptr)
		this->character->draw(window);
}

void RoadLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.05) {
		y += 5;
		this->sprite.setPosition(0, y);
		moveobx(15, 5);
		clock.restart();
	}
}

void RoadLane::processUp(Character* character)
{
	character->up();
}

void RoadLane::processDown(Character* character)
{
	character->down();
}

void RoadLane::processLeft(Character* character)
{
	character->left();
}

void RoadLane::processRight(Character* character)
{
	character->right();
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
	this->character = nullptr;
	this->type = RAIL;
}

void RailLane::initOb(sf::Texture& rock) {
	this->train->setup(rock);
	this->train->randomx();
	this->train->setPos(train->returnx(), y);
	if (this->train->rfleft())  this->train->setScale(-4, 4);
}

void RailLane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);

	//window.draw(this->sprite);
	this->train->drawTo(window);
	if (this->character != nullptr)
		this->character->draw(window);
}

void RailLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.05) {
		y += 5;
		this->sprite.setPosition(0, y);
		if (this->greenLight()) moveobx(50, 5);
		else moveobx(0, 5);
		clock.restart();
	}
}

void RailLane::processUp(Character* character)
{
	character->up();
}

void RailLane::processDown(Character* character)
{
	character->down();
}

void RailLane::processLeft(Character* character)
{
	character->left();
}

void RailLane::processRight(Character* character)
{
	character->right();
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
	this->rock[0].loadFromFile("resource/object/object.png");
	this->rock[1].loadFromFile("resource/object/object.png");
	this->plant.loadFromFile("resource/object/plant.png");
	this->car[0].loadFromFile("resource/object/vehicle/left0.png");
	this->car[1].loadFromFile("resource/object/vehicle/left1.png");
	this->car[2].loadFromFile("resource/object/vehicle/left21.png");
	this->car[3].loadFromFile("resource/object/vehicle/left9.png");
	this->car[4].loadFromFile("resource/object/vehicle/left31.png");
	this->train.loadFromFile("resource/object/trainLeft.png");
	this->character = nullptr;
	font.loadFromFile("resource/fibberish.ttf");
}

LaneManager::~LaneManager()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		delete lanes[i];
	}
}

void LaneManager::initCharacter(Character* character)
{
	this->character = character;
}

void LaneManager::addLane(int y)
{
	int n = 3;
	int random = rand() % 100;
	if (random < 20)
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, car[0], car[1], car[2], car[3], car[4], index));
	else if (random < 40)
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, car[0], car[1], car[2], car[3], car[4], index));
	else if (random < 60)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[2], y, plant, rock[0], rock[1], car[0], train, index));
	else if (random < 80)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[3], y, plant, rock[0], rock[1], car[0], train, index));
	else if (random < 90)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[4], y, plant, rock[0], rock[1], car[0], train, index));
	else
		this->lanes.insert(lanes.begin(), new RailLane(this->texture[0], y, rock[0], car[0], train, index));
	std::cout << "added lane: " << index << std::endl;
	index++;
}

void LaneManager::processUp()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index)
		{
			if (lanes[i]->getCharacter())
				lanes[i-1]->processUp(lanes[i]->getCharacter());
			break;
		}
	}
}

void LaneManager::processDown()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index)
		{
			if (lanes[i]->getCharacter())
				lanes[i+1]->processDown(lanes[i]->getCharacter());
			break;
		}
	}
}

void LaneManager::processLeft()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index)
		{
			if (lanes[i]->getCharacter())
				lanes[i]->processLeft(lanes[i]->getCharacter());
			break;
		}
	}
}

void LaneManager::processRight()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index)
		{
			if (lanes[i]->getCharacter())
				lanes[i]->processRight(lanes[i]->getCharacter());
			break;
		}
	}
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
		for (int i = 0; i < this->lanes.size(); i++)
		{
			std::cout << lanes[i]->getIndex() << (lanes[i]->getCharacter() ? "x " : " ");
		}
		std::cout << std::endl << character->index << std::endl;
	}
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index)
		{
			lanes[i]->setCharacter(character);
			lanes[i]->setCharacterPosition(lanes[i]->getY());
		}
		else
		{
			lanes[i]->setCharacter(nullptr);
		}
	}
}

void LaneManager::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		lanes[i]->drawBackgroundTo(window);
	}
	for (int i = 0; i < this->lanes.size(); i++)
	{
		lanes[i]->drawTo(window);
		text.setFont(font);
		text.setString(std::to_string(lanes[i]->getIndex()));
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setPosition(0, lanes[i]->getY());
		window.draw(text);
	}
}

GrassLane::~GrassLane() {
	delete[] ob;
}
RoadLane::~RoadLane() {
	delete[] ob;
}
RailLane::~RailLane() {
	delete train;
}