#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Gif {
private:
	sf::Clock clock;
	int x; //x and y of the first frame
	int y; //x and y of the first frame
	int width; //width and height of each frame
	int height; //width and height of each frame
	int currentFrame; //which frame is the gif currently on
	int totalFrame; //how many frames are there in the gif
	double cycle; //how many seconds will it take for the gif to finish
	double frameSpeed; //how many seconds will it take for each frame to change
	sf::Sprite sprite;
public:
	void load(const sf::Texture& texture, int x, int y, int width, int height, int totalFrame);
	void update();
	void drawTo(sf::RenderWindow& window);
	void setPosition(int x, int y);
	void setScale(float x, float y);
	void setSpeed(double speed);
};