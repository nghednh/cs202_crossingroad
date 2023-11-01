#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Gif {
private:
	sf::Clock clock;
	int x;
	int y;
	int width;
	int height;
	int currentFrame;
	int totalFrame;
	int frameCount;
	double frameSpeed;
	sf::Sprite sprite;
public:
	void load(const sf::Texture& texture, int x, int y, int width, int height, int totalFrame);
	void update();
	void drawTo(sf::RenderWindow& window);
	void setPosition(int x, int y);
	void setScale(float x, float y);
	void setSpeed(double speed);
};