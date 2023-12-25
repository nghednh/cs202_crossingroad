#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "Object.h"
#include "Character.h"

enum LaneType
{
	GRASS,
	ROAD,
	RAIL
};

class Lane
{
protected:
	sf::Sprite sprite;
	int index;
	int y;
	Character* character;
	LaneType type;
public:
	virtual ~Lane() {}
	virtual bool isOutOfScreen(int& height) const = 0;
	virtual void drawTo(sf::RenderWindow& window, sf::Font& font) = 0;
	virtual void move(bool& shouldGoFaster) = 0;
	virtual int getY() const = 0;
	virtual void processUp(Character* character) = 0;
	virtual void processDown(Character* character) = 0;
	virtual void processLeft(Character* character) = 0;
	virtual void processRight(Character* character) = 0;
	virtual void checkCollision() = 0;
	int getIndex() const { return index; }
	void setCharacter(Character* character) { this->character = character; }
	Character* getCharacter() const { return character; }
	void drawCharacterTo(sf::RenderWindow& window) {if (character) character->draw(window); }
	void drawBackgroundTo(sf::RenderWindow& window) { this->sprite.setPosition(0, y); window.draw(sprite); }
	void setCharacterPosition(int y) { if (character) character->setY(y); }
};

class GrassLane : public Lane
{
private:
	sf::Clock clock;
	int nob;
	ObjectStable* ob;

public:
	~GrassLane();
	GrassLane(sf::Texture& texture, int y, sf::Texture& plant, sf::Texture& rock1, sf::Texture& rock2, sf::Texture& car, sf::Texture& train, int index);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	void checkCollision();
	int getY() const { return y; }
	void initOb(sf::Texture& plant, sf::Texture& rock1, sf::Texture& rock2);
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
	RoadLane(sf::Texture& texture, int y, sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture &car4, sf::Texture& car5, int index);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	int getY() const { return y; }
	void moveobx(int a, int b);
	int returnnob() { return nob; }
	void initOb(sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5);
	void checkCollision();
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
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	int getY() const { return y; }
	void initOb(sf::Texture& rock);
	void moveobx(int a, int b);
	bool greenLight() { return !redLight; };
	void checkCollision();
};

class LaneManager
{
private:
	std::vector<Lane*> lanes;
	sf::Texture texture[6];
	sf::Texture rock[2];
	sf::Texture plant;
	sf::Texture car[5];
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
	void processUp();
	void processDown();
	void processLeft();
	void processRight();
	void update(bool& shouldGoFaster);
	void drawTo(sf::RenderWindow& window);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDifficulty() const { return difficulty; }
	void setDifficulty(int difficulty) { this->difficulty = difficulty; }
};