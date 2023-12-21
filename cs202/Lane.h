#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "Object.h"
#include "Character.h"

class Lane
{
protected:
	sf::Sprite sprite;
	int index;
	int y;
	Character* character;
public:
	virtual ~Lane() {}
	virtual bool isOutOfScreen(int& height) const = 0;
	virtual void drawTo(sf::RenderWindow& window) = 0;
	virtual void move(bool& shouldGoFaster) = 0;
	virtual int getY() const = 0;
	int getIndex() const { return index; }
	void setCharacter(Character* character) { this->character = character; }
	Character* getCharacter() const { return character; }
	void drawCharacterTo(sf::RenderWindow& window) {if (character) character->draw(window); }
	void drawBackgroundTo(sf::RenderWindow& window) { this->sprite.setPosition(0, y); window.draw(sprite); }
};

class GrassLane : public Lane
{
private:
	sf::Clock clock;
	int nob;
	ObjectStable* ob;

public:
	~GrassLane();
	GrassLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window);
	void move(bool& shouldGoFaster);
	int getY() const { return y; }
	void initOb(sf::Texture& rock);
	void moveobx(int a, int b);
	int returnnob() { return nob; }
};

class RoadLane : public Lane
{
private:
	sf::Clock clock;
	int nob;
	ObjectMoving* ob;
public:
	~RoadLane();
	RoadLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture &train, int index);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window);
	void move(bool& shouldGoFaster);
	int getY() const { return y; }
	void moveobx(int a, int b);
	int returnnob() { return nob; }
	void initOb(sf::Texture& rock);
};

class RailLane : public Lane
{
private:
	sf::Clock clock;
	TrainObject *train;
	bool redLight=false;
public:
	~RailLane();
	RailLane(sf::Texture& texture, int y, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window);
	void move(bool& shouldGoFaster);
	int getY() const { return y; }
	void initOb(sf::Texture& rock);
	void moveobx(int a, int b);
	bool greenLight() { return !redLight; };
};

class LaneManager
{
private:
	std::vector<Lane*> lanes;
	sf::Texture texture[6];
	sf::Texture rock;
	sf::Texture car[6];
	sf::Texture train;
	int width;
	int height;
	int difficulty;
	int index;
	Character* character;
	sf::Font font;
	sf::Text text;
public:
	LaneManager();
	~LaneManager();
	void initCharacter(Character* character);
	void addLane(int y);
	void popLane() { lanes.pop_back(); }
	void update(bool& shouldGoFaster);
	void drawTo(sf::RenderWindow& window);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDifficulty() const { return difficulty; }
	void setDifficulty(int difficulty) { this->difficulty = difficulty; }
};