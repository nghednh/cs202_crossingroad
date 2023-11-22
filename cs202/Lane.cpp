#include "Lane.h"

Lane::Lane(sf::Texture& texture, int y, bool isGrass)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(4, 4);
	this->y = y;
	this->isGrass = isGrass;
}

void Lane::drawTo(sf::RenderWindow& window)
{
	this->sprite.setPosition(0, y);
	window.draw(this->sprite);
}

void Lane::move()
{
	double time = clock.getElapsedTime().asSeconds();
	if (time > 0.05) {
		this->sprite.move(0, 1);
		y++;
		clock.restart();
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
}

void LaneManager::addLane(int y)
{
	int random = rand() % 100;
	if (random < 20)
		this->lanes.insert(lanes.begin(), Lane(this->texture[1], y, false));
	else if (random < 40)
		this->lanes.insert(lanes.begin(), Lane(this->texture[2], y, true));
	else if (random < 60)
		this->lanes.insert(lanes.begin(), Lane(this->texture[3], y, true));
	else if (random < 80)
		this->lanes.insert(lanes.begin(), Lane(this->texture[4], y, true));
	else
		this->lanes.insert(lanes.begin(), Lane(this->texture[5], y, true));
}

void LaneManager::update()
{
	for (int i = 0; i < this->lanes.size(); i++)
	{
		this->lanes[i].move();
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
