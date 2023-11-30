#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "Object.h"

class Lane
{
private:
	bool isGrass;
	sf::Sprite sprite;
	int y;
	sf::Clock clock;
	int nob;
	Object *ob;

public:
	Lane(sf::Texture& texture, int y, bool isGrass, sf::Texture &rock, sf::Texture &car);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y+128 > height; }
	void drawTo(sf::RenderWindow& window);
	void move(bool& shouldGoFaster);
	int getY() const { return y; }
	bool isGras() { return isGrass; }
	void initOb(sf::Texture& rock);
	void moveobx(int a,int b);
	int returnnob() { return nob; }
};

class LaneManager
{
private:
	std::vector<Lane> lanes;
	sf::Texture texture[6];
	sf::Texture rock;
	sf::Texture car;
	int width;
	int height;
	int difficulty;
public:
	LaneManager();
	void addLane(int y);
	void popLane() { lanes.pop_back(); }
	void update(bool& shouldGoFaster);
	void drawTo(sf::RenderWindow& window);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDifficulty() const { return difficulty; }
	void setDifficulty(int difficulty) { this->difficulty = difficulty; }
};