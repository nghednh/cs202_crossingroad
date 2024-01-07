#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "Object.h"
#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace sf;

enum LaneType
{
	GRASS,
	ROAD,
	RAIL,
	ANIMAL
};

class Lane
{
protected:
	sf::Sprite sprite;
	int index;
	int y;
	Character* character;		
	LaneType type;			// grass, road, rail or animal
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
	virtual void checkCollision(sf::Font& font) = 0;
	virtual std::string info() { return ""; }
	virtual int returnnob() { return 0; }
	int getIndex() const { return index; }
	void setCharacter(Character* character) { this->character = character; }
	Character* getCharacter() const { return character; }
	void drawCharacterTo(sf::RenderWindow& window) {if (character) character->draw(window); }
	void drawBackgroundTo(sf::RenderWindow& window) { this->sprite.setPosition(0, y); window.draw(sprite); }
	void setCharacterPosition(int y) { if (character) character->setY(y); }
	LaneType getType() const { return type; }
};

class GrassLane : public Lane
{
private:
	sf::Clock clock;
	int nob;
	ObjectStable* ob;
	int nGL;
public:
	~GrassLane();
	GrassLane(sf::Texture& texture, int y, sf::Texture& plant, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index, int nGL);
	GrassLane(sf::Texture& texture, std::string tmp, sf::Texture& plant, sf::Texture& rock, sf::Texture& car, sf::Texture& train, int index, int nGL, std::string& charInfo, int& indexChar, int& setIndex);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	void checkCollision(sf::Font& font);
	virtual std::string info();
	int getY() const { return y; }
	void initOb(sf::Texture& plant, sf::Texture& rock);
	//void loadOb(sf::Texture& plant, sf::Texture& rock);
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
	RoadLane(sf::Texture& texture, std::string tmp, sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5, int index, std::string& charInfo, int& indexChar, int& setIndex);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	virtual std::string info();
	int getY() const { return y; }
	void moveobx(int a, int b);
	int returnnob() { return nob; }
	void initOb(sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5);
	//void loadOb(sf::Texture& car1, sf::Texture& car2, sf::Texture& car3, sf::Texture& car4, sf::Texture& car5);
	void checkCollision(sf::Font& font);
};

class RailLane : public Lane
{
private:
	sf::Clock clock;
	TrainObject *train;
	bool redLight;
	ObjectStable light1;
	ObjectStable light2;
public:
	~RailLane();
	RailLane(sf::Texture& texture, int y, sf::Texture& Light, sf::Texture& train, int index);
	RailLane(sf::Texture& texture, std::string tmp, sf::Texture& Light, sf::Texture& train, int index, std::string& charInfo, int& indexChar, int& setIndex);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	int getY() const { return y; }
	void initOb(sf::Texture& rock);
	virtual std::string info();
	int returnnob() { return 0; }
	void moveobx(int a, int b);
	void randomInitLight() { redLight = rand() % 2; }
	bool greenLight() { return !redLight; };
	void checkCollision(sf::Font& font);
};

//this lane works like road lane but the texture is grass and the object does not move, but you can jump to them and get hit
class AnimalLane : public Lane
{
private:
	sf::Clock clock;
	int nob;
	ObjectStable* ob;
public:
	~AnimalLane();
	AnimalLane(sf::Texture& texture, int y, sf::Texture& animal1, sf::Texture& animal2, sf::Texture& animal3, sf::Texture& animal4, sf::Texture& animal5, int index);
	AnimalLane(sf::Texture& texture, std::string tmp, sf::Texture& animal1, sf::Texture& animal2, sf::Texture& animal3, sf::Texture& animal4, sf::Texture& animal5, int index, std::string& charInfo, int& indexChar, int& setIndex);
	bool isOutOfScreen(int& height) const { return this->sprite.getPosition().y + 128 > height; }
	void drawTo(sf::RenderWindow& window, sf::Font& font);
	void move(bool& shouldGoFaster);
	void processUp(Character* character);
	void processDown(Character* character);
	void processLeft(Character* character);
	void processRight(Character* character);
	int getY() const { return y; }
	void initOb(sf::Texture& animal1, sf::Texture& animal2, sf::Texture& animal3, sf::Texture& animal4, sf::Texture& animal5);
	void moveobx(int a, int b);
	virtual std::string info();
	int returnnob() { return nob; }
	void checkCollision(sf::Font& font);
};

class LaneManager
{
private:
	std::vector<Lane*> lanes;
	sf::Texture texture[6];
	sf::Texture rock;
	sf::Texture plant;
	sf::Texture car[5];
	sf::Texture animal[5];
	sf::Texture train;
	sf::Texture Light;
	sf::Texture rain[3];
	sf::Sprite rainSprite[25];
	int width;
	int height;
	int difficulty;
	int index;
	Character* character;
	sf::Font font;
	sf::Text text;
	bool isRaining;
	sf::Clock clock;
	sf::Clock rainClock;
	sf::Clock rainAnimationClock;
	sf::Texture rainFilter_;
	sf::Sprite rainFilter;
public:
	LaneManager();
	~LaneManager();
	void setIndex();
	void initCharacter(Character* character);
	void addLane(int y);
	void popLane() { lanes.pop_back(); }
	void processUp();
	void processDown();
	void processLeft();
	void processRight();
	void update(bool& shouldGoFaster);
	void drawTo(sf::RenderWindow& window);
	void drawRainTo(sf::RenderWindow& window);
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDifficulty() const { return difficulty; }
	void setDifficulty(int difficulty) { this->difficulty = difficulty; }
	void createShield();
	void reset();
	void saveToFile();
	void processEach(std::string tmp, std::string& charInfo, int& indexChar);
};
