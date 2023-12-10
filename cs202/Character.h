#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Gif.h"

class Character
{
private:
	Gif gif;
	sf::Texture jumping;
	sf::Texture dying;
	sf::Clock clock;
	int x;
	int y;
	int width;
	int height;
	double speed;
	bool dead;
	bool isOutOfScreen;
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	int counter; //use for animation
public:
	bool blocked;
	Character();
	void update();
	void up();
	void down();
	void left();
	void right();
	void draw(sf::RenderWindow& window);
	bool isDead();
	bool shouldGoFaster();
};

