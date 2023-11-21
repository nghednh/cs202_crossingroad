#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

class Lane
{
private:
	sf::Sprite sprite;
	int y;
	sf::Clock clock;
public:
	Lane(sf::Texture& texture, int y);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y+128 > height; }
	void drawTo(sf::RenderWindow& window);
	void move();
	int getY() const { return y; }
};

class LaneManager
{
private:
	std::vector<Lane> lanes;
	sf::Texture texture[6];
	int width;
	int height;
	int difficulty;
public:
	LaneManager();
	void addLane(int y);
	void popLane() { lanes.pop_back(); }
	void update();
	void drawTo(sf::RenderWindow& window);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDifficulty() const { return difficulty; }
	void setDifficulty(int difficulty) { this->difficulty = difficulty; }
};

