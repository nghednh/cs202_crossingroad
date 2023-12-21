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
	this->ob = new ObjectStable[nob];
	initOb(rock);
	this->character = nullptr;
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
	nob = rand() % 10 + 1;
	this->ob = new ObjectMoving[nob];
	initOb(car);
	this->character = nullptr;
}

void RoadLane::initOb(sf::Texture& rock) {

	int a = -1;
	//std::cout << nob;
	int b = -2;
	bool bef;
	for (int i = 0; i < nob; i++) {
		if (i == 0) {
			this->ob[i].setup(rock, 2.56, 2.56, 0, 0, 100, 100);
			//ob[i].randomx();
			b = ob[i].randomx();
			while (a == b) b = ob[i].randomx();
			a = b;
			ob[i].setPos(ob[i].returnx(), y);
			if (ob[i].rfleft()) ob[i].setScale(-2.56, 2.56);
			bef = ob[i].rfleft();
		}
		else {
			this->ob[i].setup(rock, 2.56, 2.56, 0, 0, 100, 100);
			ob[i].randomxx(bef);
			b = ob[i].randomxx(bef);
			while (a == b) b = ob[i].randomxx(bef);
			a = b;
			ob[i].setPos(ob[i].returnx(), y);
			if (ob[i].rfleft()) ob[i].setScale(-2.56, 2.56);
		}

	}

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
	this->car[0].loadFromFile("resource/object/vehicle/left0.png");
	this->car[1].loadFromFile("resource/object/vehicle/left1.png");
	this->car[2].loadFromFile("resource/object/vehicle/left21.png");
	this->car[3].loadFromFile("resource/object/vehicle/left7.png");
	this->car[4].loadFromFile("resource/object/vehicle/left4.png");
	this->car[5].loadFromFile("resource/object/vehicle/left5.png");
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
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, rock, car[rand()%3], train, index));
	else if (random < 40)
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, rock, car[rand()%3], train, index));
	else if (random < 60)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[2], y, rock, car[0], train, index));
	else if (random < 80)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[3], y, rock, car[0], train, index));
	else if (random < 90)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[4], y, rock, car[0], train, index));
	else
		this->lanes.insert(lanes.begin(), new RailLane(this->texture[0], y, rock, car[0], train, index));
	std::cout << "added lane: " << index << std::endl;
	index++;
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