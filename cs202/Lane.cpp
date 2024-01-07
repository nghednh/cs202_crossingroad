#include "Lane.h"
#include <cstdlib>
#include <iostream>

GrassLane::GrassLane(sf::Texture& texture, int y, sf::Texture& plant, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index, int nGL)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	this->nGL = nGL;
	if (index <= 4) {
		nob = 0;
		this->ob = nullptr;
	}
	else {
		nob = rand() % 6 + 1;
		this->ob = new ObjectStable[nob];
		initOb(plant, rock);
	}
	this->character = nullptr;
	this->type = GRASS;
}

GrassLane::GrassLane(sf::Texture& texture, string tmp, sf::Texture& plant, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index, int nGL, string& charInfo, int& indexChar, int& setIndex)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->nGL = nGL;
	
	istringstream iss(tmp);
	string cut;
	iss >> cut;		// grasslane
	iss >> cut;		// numgrasslane
	iss >> y;
	iss >> nob;
	ob = new ObjectStable[nob];
//	this->sprite.setPosition(0, this->y);
	string rockType;
	string xPos, yPos;
	for (int i = 0; i < this->nob; i++)
	{
		iss >> rockType;
		if (rockType == "rock1") ob[i].setup(rock, 2, 2, 195, -9, 64, 70, "rock1");
		else if (rockType == "rock2") ob[i].setup(rock, 2, 2, 384, 194, 64, 64, "rock2");
		else if (rockType == "rock3") ob[i].setup(plant, 2, 2, 216, 185, 47, 42, "rock3");
		iss >> xPos; 
		iss >> yPos;
		ob[i].setPosSprite(stoi(xPos), stoi(yPos));
	}
	string idx;
	iss >> idx;
	this->index = stoi(idx);
	this->character = nullptr;
	this->type = GRASS;
	if (setIndex < this->index + 1) setIndex = this->index + 1;
}

std::string GrassLane::info()
{
	std::string res = "GrassLane";
	res += " ";
	res += to_string(nGL);
	res += " ";
	res += to_string(y);
	res += " "; res += to_string(nob);
	for (int i = 0; i < nob; i++)
	{
		res += " ";
		res += ob[i].info();
	}
	res += " ";
	res += to_string(index);
	return res;
}

void GrassLane::initOb(sf::Texture& plant, sf::Texture& rock) {
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
			this->ob[i].setup(rock, 2, 2, 195, -9, 64, 70, "rock1");
		}
		else if (rand() % 3 == 2) {
			this->ob[i].setup(rock, 2, 2, 384, 194, 64, 64, "rock2");
			tmp = 1;
		}
		else {
			this->ob[i].setup(plant, 2, 2, 216, 185, 47, 42, "rock3");
			tmp = 2;
		}
		b = ob[i].randomx(idx, 13);
		while (a == b) b = ob[i].randomx(idx, 13);
		a = b;
		if (tmp == 1) {
			ob[i].setPos(ob[i].returnx(), y + 30);
		}
		else if (tmp == 2) {
			ob[i].setPos(ob[i].returnx(), y + 50);
		}
		else ob[i].setPos(ob[i].returnx(), y);
	}
	delete[] idx;
}

void GrassLane::drawTo(sf::RenderWindow& window, sf::Font& font)
{
	this->sprite.setPosition(0, y);

	//window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window, font);
	}
	if (this->character != nullptr)
		this->character->draw(window);
}

void GrassLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.01) {
		y += 1;
		this->sprite.setPosition(0, y);
		moveobx(3, 1);
		clock.restart();
	}
}

void GrassLane::processUp(Character* character) {
	for (int i = 0; i < nob; i++) {
		if (character->position == ob[i].returnx()) {
			//std::cout << "BLOCKED UP GRASS" << std::endl;
			return;
		}
	}
	character->up();
}

void GrassLane::processDown(Character* character)
{
	for (int i = 0; i < nob; i++) {
		if (character->position == ob[i].returnx()) {
			//std::cout << "BLOCKED DOWN GRASS" << std::endl;
			return;
		}
	}
	character->down();
}

void GrassLane::processLeft(Character* character)
{
	for (int i = 0; i < nob; i++) {
		if (character->position - 1 == ob[i].returnx()) {
			//std::cout << "BLOCKED LEFT GRASS" << std::endl;
			return;
		}
	}
	character->left();
}

void GrassLane::processRight(Character* character)
{
	for (int i = 0; i < nob; i++) {
		if (character->position + 1 == ob[i].returnx()) {
			//std::cout << "BLOCKED RIGHT GRASS" << std::endl;
			return;
		}
	}
	character->right();
}

void GrassLane::checkCollision(sf::Font& font)
{
	return;
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

RoadLane::RoadLane(sf::Texture& texture, std::string tmp, sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5, int index, std::string& charInfo, int& indexChar, int& setIndex)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->index = index;

	istringstream iss(tmp);
	string cut;
	iss >> cut;		// grasslane
	iss >> y;
	iss >> nob;
	ob = new ObjectMoving[nob];
//	this->sprite.setPosition(0, this->y);
	string carType;
	string xPos, yPos, fleft;
	for (int i = 0; i < nob; i++)
	{
		iss >> carType;
		if (carType == "car1") this->ob[i].setup(car1, 2.56, 2.56, 5, 0, 82, 72, "car1");
		else if (carType == "car2") this->ob[i].setup(car2, 2.56, 2.56, 5, 0, 82, 72, "car2");
		else if (carType == "car3") this->ob[i].setup(car3, 2.56, 2.56, 12, 0, 74, 66, "car3");
		else if (carType == "car4")	this->ob[i].setup(car4, 2.56, 2.56, 8, 0, 83, 72, "car4");
		else if (carType == "car5") this->ob[i].setup(car5, 2.56, 2.56, 12, 0, 74, 66, "car5");
				
		iss >> xPos;
		iss >> yPos;
		iss >> fleft;
		ob[i].setFleft(stoi(fleft));
		if (this->ob[i].rfleft())  this->ob[i].setScale(-2.56, 2.56);
		ob[i].setPosSprite(stoi(xPos), stoi(yPos));
	}
	string idx;
	iss >> idx;
	this->index = stoi(idx);
	this->character = nullptr;
	this->type = ROAD;
	if (setIndex < this->index + 1) setIndex = this->index + 1;
}

std::string RoadLane::info()
{
	std::string res = "RoadLane";
	res += " ";
	res += to_string(y);
	res += " "; res += to_string(nob);
	for (int i = 0; i < nob; i++)
	{
		res += " ";
		res += ob[i].info();
	}
	res += " ";
	res += to_string(index);
	return res;
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
		case 0:
		{
			this->ob[i].setup(car1, 2.56, 2.56, 5, 0, 82, 72, "car1");
			break;
		}
		case 1:
		{
			this->ob[i].setup(car2, 2.56, 2.56, 5, 0, 82, 72, "car2");
			break;
		}
		case 2:
		{
			this->ob[i].setup(car3, 2.56, 2.56, 12, 0, 74, 66, "car3");
			break;
		}
		case 3:
		{
			this->ob[i].setup(car4, 2.56, 2.56, 8, 0, 83, 72, "car4");
			break;
		}
		case 4:
		{
			this->ob[i].setup(car5, 2.56, 2.56, 12, 0, 74, 66, "car5");
			break;
		}
		}
		if (i == 0) {
			//ob[i].randomx();
			b = ob[i].randomx(idx);
			while (a == b) b = ob[i].randomx(idx);
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

void RoadLane::checkCollision(sf::Font& font)
{
	if (character == nullptr)
		return;
	for (int i = 0; i < nob; i++)
	{
		int objectX = ob[i].spriteX();
		double objectScale = ob[i].spriteScaleX();
		double objectWidth = ob[i].spriteWidth() * objectScale;
		int characterX = character->position * 128;
		if (ob[i].rfleft()) {
			if (characterX + 21 >= objectX || characterX + 72 - 12 <= objectX + objectWidth) {

				//std::cout << "Left\n";
				continue;
			}
			else {
				std::cout << "COLLISION: " << characterX << " " << objectX << std::endl;
				character->die();
				return;
			}
		}
		else {
			if (characterX + 72 - 12 <= objectX || characterX + 21 >= objectX + objectWidth) {
				//std::cout << "Right\n";
				continue;
			}
			else {
				std::cout << "COLLISION: " << characterX << " " << objectX << std::endl;
				character->die();
				return;
			}
		}
	}
}

void RoadLane::drawTo(sf::RenderWindow& window, sf::Font& font)
{
	this->sprite.setPosition(0, y);

	//window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window, font);
	}
	if (this->character != nullptr)
		this->character->draw(window);
}

void RoadLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.01) {
		y += 1;
		this->sprite.setPosition(0, y);
		moveobx(3, 1);
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

RailLane::RailLane(sf::Texture& texture, int y, sf::Texture& Light , sf::Texture& train, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	randomInitLight();
	this->train = new TrainObject;
	initOb(train);
	light1.setup(Light, 2.6, 2.6, 57, 49, 18, 73, "ligh1");
	light2.setup(Light, 2.6, 2.6, 91, 49, 18, 73, "light2");
	this->character = nullptr;
	this->type = RAIL;
}

RailLane::RailLane(sf::Texture& texture, std::string tmp, sf::Texture& Light, sf::Texture& train, int index, std::string& charInfo, int& indexChar, int& setIndex)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->index = index;

	istringstream iss(tmp);
	string cut;
	iss >> cut;		// grasslane
	iss >> y;
	this->train = new TrainObject;
	randomInitLight();
	light1.setup(Light, 2.6, 2.6, 57, 49, 18, 73, "ligh1");
	light2.setup(Light, 2.6, 2.6, 91, 49, 18, 73, "light2");
	string carType;
	string xPos, yPos, fleft;
	
	iss >> cut;
	if (cut != "train") xPos = cut;
	else iss >> xPos;
	iss >> yPos;
	iss >> fleft;
	this->train->setFleft(stoi(fleft));
//	this->sprite.setPosition(0, this->y);
	this->train->setup(train, "train");
	string idx;
	iss >> idx;
	this->index = stoi(idx);
	this->character = nullptr;
	this->type = RAIL;
	if (this->train->rfleft())  this->train->setScale(-4, 4);
	if (setIndex < this->index + 1) setIndex = this->index + 1;
	this->train->setPosSprite(stoi(xPos), stoi(yPos));
}

std::string RailLane::info()
{
	std::string res = "RailLane";
	res += " ";
	res += to_string(y);
	res += " ";
	res += train->info();
	res += " ";
	res += to_string(index);
	return res;
}

void RailLane::initOb(sf::Texture& rock) {
	bool* dummy = new bool[1];
	this->train->setup(rock, "train");
	this->train->randomx(dummy);
	this->train->setPos(train->returnx(), y);
	if (this->train->rfleft())  this->train->setScale(-4, 4);
	delete[] dummy;
}

void RailLane::drawTo(sf::RenderWindow& window, sf::Font& font)
{
	this->sprite.setPosition(0, y + 30);
	//window.draw(this->sprite);
	this->train->drawTo(window, font);
	if (!this->train->rfleft()) {
		if (this->redLight == true) {
			this->light2.drawTo(window, font);
			this->light2.setPos(12, y + 30);
		}
		else {
			this->light1.drawTo(window, font);
			this->light1.setPos(12, y + 30);
		}
	}
	else {
		if (this->redLight == true) {
			this->light2.drawTo(window, font);
			this->light2.setPos(1, y + 30);
		}
		else {
			this->light1.drawTo(window, font);
			this->light1.setPos(1, y + 30);
		}
	}
	if (this->character != nullptr)
		this->character->draw(window);
}

void RailLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.01) {
		y += 1;
		this->sprite.setPosition(0, y);
		if (this->greenLight()) moveobx(10, 1);
		else moveobx(0, 1);
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

void RailLane::checkCollision(sf::Font& font)
{
	if (character == nullptr)
		return;
	int objectX = train->spriteX();
	double objectScale = train->spriteScaleX();
	double objectWidth = train->spriteWidth() * objectScale;
	int characterX = character->position * 128;
	if (train->rfleft()) {
		if (characterX + 21 >= objectX || characterX + 72 - 12 <= objectX + objectWidth) {

			//std::cout << "Left\n";
			return;
		}
		else {
			std::cout << "COLLISION: " << characterX << " " << objectX << std::endl;
			character->die();
			return;
		}
	}
	else {
		if (characterX + 72 - 12 <= objectX || characterX + 21 >= objectX + objectWidth) {
			//std::cout << "Right\n";
			return;
		}
		else {
			std::cout << "COLLISION: " << characterX << " " << objectX << std::endl;
			character->die();
			return;
		}
	}
}

LaneManager::LaneManager()
{
	this->difficulty = 0;
	this->width = 1600;
	this->height = 128;
	this->index = 1;
	this->texture[0].loadFromFile("resource/tiles/train1.png");
	this->texture[1].loadFromFile("resource/tiles/road1.png");
	this->texture[2].loadFromFile("resource/tiles/grass0.png");
	this->texture[3].loadFromFile("resource/tiles/grass1.png");
	this->texture[4].loadFromFile("resource/tiles/grass2.png");
	this->texture[5].loadFromFile("resource/tiles/grass3.png");
	this->rock.loadFromFile("resource/object/object.png");
	this->plant.loadFromFile("resource/object/plant.png");
	this->car[0].loadFromFile("resource/object/vehicle/left0.png");
	this->car[1].loadFromFile("resource/object/vehicle/left1.png");
	this->car[2].loadFromFile("resource/object/vehicle/left21.png");
	this->car[3].loadFromFile("resource/object/vehicle/left9.png");
	this->car[4].loadFromFile("resource/object/vehicle/left31.png");
	this->animal[0].loadFromFile("resource/object/animal1/cow.png");
	this->animal[1].loadFromFile("resource/object/animal1/sheep.png");
	this->animal[2].loadFromFile("resource/object/animal1/goat1.png");
	this->animal[3].loadFromFile("resource/object/animal/dog.png");
	this->animal[4].loadFromFile("resource/object/animal/pig.png");
	this->train.loadFromFile("resource/object/trainLeft.png");
	this->Light.loadFromFile("resource/object/TrafficLight.png");
	this->character = nullptr;
	this->isShielded = false;
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
	int random = rand() % 100;
	if (index <= 4)
		this->lanes.insert(lanes.begin(), new GrassLane(this->texture[3], y, plant, rock, car[0], train, index, 3));
	else if (index == 10)
		this->lanes.insert(lanes.begin(), new RailLane(this->texture[0], y, Light, train, index));
	else if (index == 9)
		this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, car[0], car[1], car[2], car[3], car[4], index));
	else {
		if (random < 12)
			this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, car[0], car[1], car[2], car[3], car[4], index));
		else if (random < 24)
			this->lanes.insert(lanes.begin(), new RoadLane(this->texture[1], y, car[0], car[1], car[2], car[3], car[4], index));
		else if (random < 36)
			this->lanes.insert(lanes.begin(), new GrassLane(this->texture[2], y, plant, rock, car[0], train, index, 2));
		else if (random < 48)
			this->lanes.insert(lanes.begin(), new GrassLane(this->texture[3], y, plant, rock, car[0], train, index, 3));
		else if (random < 60)
			this->lanes.insert(lanes.begin(), new GrassLane(this->texture[4], y, plant, rock, car[0], train, index, 4));
		else if (random < 72)
			this->lanes.insert(lanes.begin(), new RailLane(this->texture[0], y, Light, train, index));
		else if (random < 84)
			this->lanes.insert(lanes.begin(), new AnimalLane(this->texture[5], y, animal[0], animal[1], animal[2], animal[3], animal[4], index));
		else
			this->lanes.insert(lanes.begin(), new AnimalLane(this->texture[5], y, animal[0], animal[1], animal[2], animal[3], animal[4], index));
	}
	std::cout << "added lane: " << index << std::endl;
	index++;
}

void LaneManager::processUp()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index && !character->isAnimating())
		{
			if (lanes[i]->getCharacter())
				lanes[i - 1]->processUp(lanes[i]->getCharacter());
			break;
		}
	}
}

void LaneManager::processDown()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index && !character->isAnimating())
		{
			if (lanes[i]->getCharacter())
				lanes[i + 1]->processDown(lanes[i]->getCharacter());
			break;
		}
	}
}

void LaneManager::processLeft()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		if (lanes[i]->getIndex() == character->index && !character->isAnimating())
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
		if (lanes[i]->getIndex() == character->index && !character->isAnimating())
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
		lanes[i]->checkCollision(font);
	}
	for (int i = 0; i < this->lanes.size(); i++)
	{
		lanes[i]->move(shouldGoFaster);
	}
	if (lanes.size() != 0)
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
		lanes[i]->drawTo(window, font);
		text.setFont(font);
		text.setString(std::to_string(lanes[i]->getIndex()));
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setPosition(0, lanes[i]->getY());
		window.draw(text);
		if (lanes[i]->getCharacter()) {
			text.setCharacterSize(12);
			text.setString(std::to_string(character->getX() + 21));
			text.setPosition(character->getX() + 21, character->getY());
			window.draw(text);
			text.setString(std::to_string(character->getX() + 72 - 12));
			text.setPosition(character->getX() + 72 - 12, character->getY());
			window.draw(text);
		}
	}
}

void LaneManager::reset()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		delete lanes[i];
	}
	this->lanes.clear();
	this->index = 1;
	this->character = nullptr;
	for (int i = 0; i < 9; i++)
		this->addLane(900 - i * 128);
}

void LaneManager::createShield() {
	int nearestGrass = index;
	for (int i = 0; i < lanes.size(); i++) {
		if ((lanes[i]->getType() == GRASS || lanes[i]->getType() == ANIMAL) && lanes[i]->getIndex() < nearestGrass && lanes[i]->getIndex() > character->index) {
			nearestGrass = lanes[i]->getIndex();
		}
	}
	std::cout << "Nearest grass: " << nearestGrass << std::endl;
	if (nearestGrass != index) {
		int nob = lanes[nearestGrass]->returnnob();
		for (int i = 0; i < nob; i++) {
		}
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

AnimalLane::~AnimalLane()
{
	delete[] ob;
}

AnimalLane::AnimalLane(sf::Texture& texture, int y, sf::Texture& animal1, sf::Texture& animal2, sf::Texture& animal3, sf::Texture& animal4, sf::Texture& animal5, int index)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->index = index;
	nob = rand() % 7 + 1;
	this->ob = new ObjectStable[nob];
	initOb(animal1, animal2, animal3, animal4, animal5);
	this->character = nullptr;
	this->type = ANIMAL;
}

AnimalLane::AnimalLane(sf::Texture& texture, std::string tmp, sf::Texture& animal1, sf::Texture& animal2, sf::Texture& animal3, sf::Texture& animal4, sf::Texture& animal5, int index, std::string& charInfo, int& indexChar, int& setIndex)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->index = index;

	istringstream iss(tmp);
	string cut;
	iss >> cut;		// grasslane
	iss >> y;
	iss >> nob;
	ob = new ObjectStable[nob];
	string animalType;
	string xPos, yPos;
	for (int i = 0; i < nob; i++)
	{
		iss >> animalType;
		if (animalType == "animal1") this->ob[i].setup(animal1, 3, 3, 0, 0, 32, 32, "animal1");
		else if (animalType == "animal2") ob[i].setup(animal2, 3, 3, 0, 0, 32, 32, "animal2");
		else if (animalType == "animal3") ob[i].setup(animal3, 3, 3, 0, 0, 32, 32, "animal3");
		iss >> xPos;
		iss >> yPos;
		ob[i].setPosSprite(stoi(xPos), stoi(yPos));
	}
	string idx;
	iss >> idx;
	this->index = stoi(idx);
	this->character = nullptr;
	this->type = ANIMAL;
	if (setIndex < this->index + 1) setIndex = this->index + 1;
}

void AnimalLane::drawTo(sf::RenderWindow& window, sf::Font& font)
{
	this->sprite.setPosition(0, y);

	//window.draw(this->sprite);
	for (int i = 0; i < nob; i++)
	{
		ob[i].drawTo(window, font);
	}
	if (this->character != nullptr)
		this->character->draw(window);
}

void AnimalLane::move(bool& shouldGoFaster)
{
	double time = clock.getElapsedTime().asSeconds();
	if (time >= 0.01) {
		y += 1;
		this->sprite.setPosition(0, y);
		moveobx(0, 1); // animals don't move
		clock.restart();
	}
}

void AnimalLane::processUp(Character* character)
{
	character->up();
}

void AnimalLane::processDown(Character* character)
{
	character->down();
}

void AnimalLane::processLeft(Character* character)
{
	character->left();
}

void AnimalLane::processRight(Character* character)
{
	character->right();
}

void AnimalLane::initOb(sf::Texture& animal1, sf::Texture& animal2, sf::Texture& animal3, sf::Texture& animal4, sf::Texture& animal5)
{
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
			this->ob[i].setup(animal1, 3, 3, 0, 0, 32, 32, "animal1");
		}
		else if (rand() % 3 == 2) {
			this->ob[i].setup(animal2, 3, 3, 0, 0, 32, 32, "animal2");
			tmp = 1;
		}
		else {
			this->ob[i].setup(animal3, 3, 3, 0, 0, 32, 32, "animal3");
			tmp = 2;
		}
		b = ob[i].randomx(idx, 13);
		while (a == b) b = ob[i].randomx(idx, 13);
		a = b;/*
		if (tmp == 1) {
			ob[i].setPos(ob[i].returnx(), y + 30);
		}
		else if (tmp == 2) {
			ob[i].setPos(ob[i].returnx(), y + 50);
		}
		else */ob[i].setPos(ob[i].returnx(), y + 50);
	}
	delete[] idx;
}

std::string AnimalLane::info()
{
	std::string res = "AnimalLane";
	res += " ";
	res += to_string(y);
	res += " "; res += to_string(nob);
	for (int i = 0; i < nob; i++)
	{
		res += " ";
		res += ob[i].info();
	}
	res += " ";
	res += to_string(index);
	return res;
}

void AnimalLane::moveobx(int a, int b)
{
	for (int i = 0; i < nob; i++) {
		this->ob[i].move(0, b);
	}
}

void AnimalLane::checkCollision(sf::Font& font)
{
	if (character == nullptr)
		return;
	for (int i = 0; i < nob; i++) {
		if (character->position == ob[i].returnx()) {
			character->die();
			return;
		}
	}
}

void LaneManager::saveToFile()
{
	ofstream out("Save.txt");
	for (int i = lanes.size() - 1; i >= 0; i--)
	{
		std::string tmp = lanes[i]->info();
		out << tmp << endl;
	}
	out.close();
}

void LaneManager::processEach(std::string tmp, std::string& charInfo, int& indexChar) {
	std::string type;
	std::string tGL;
	istringstream iss(tmp);
	iss >> type;
	if (type == "GrassLane")
	{
		iss >> tGL;
		
		if (tGL == "2") lanes.insert(lanes.begin(), new GrassLane(texture[2], tmp, plant, rock, car[0], train, index, 2, charInfo, indexChar, this->index));
		else if (tGL == "3") lanes.insert(lanes.begin(), new GrassLane(texture[3], tmp, plant, rock, car[0], train, index, 3, charInfo, indexChar, this->index));
		else if (tGL == "4") lanes.insert(lanes.begin(), new GrassLane(texture[4], tmp, plant, rock, car[0], train, index, 4, charInfo, indexChar, this->index));
	}
	else if (type == "RailLane")
		lanes.insert(lanes.begin(), new RailLane(texture[0], tmp, Light, train, index, charInfo, indexChar, this->index));
	else if (type == "RoadLane")
		lanes.insert(lanes.begin(), new RoadLane(texture[1], tmp, car[0], car[1], car[2], car[3], car[4], index, charInfo, indexChar, this->index));
	else if (type == "AnimalLane")
		lanes.insert(lanes.begin(), new AnimalLane(texture[5], tmp, animal[0], animal[1], animal[2], animal[3], animal[4], index, charInfo, indexChar, this->index));
}

void LaneManager::setIndex()
{
	index = 9;
}
