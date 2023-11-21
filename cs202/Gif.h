#pragma once
#include <vector>
#include <string>
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
	double speed; //how many seconds will it take for the gif to finish
	double frameTime; //how many seconds will it take for each frame to change
	sf::Sprite sprite;
	bool loop;
public:
	void load(const sf::Texture& texture, int x, int y, int width, int height, int totalFrame, double speed);
	void update();
	void drawTo(sf::RenderWindow& window);
	void setPosition(int x, int y);
	void setScale(float x, float y);
	void setSpeed(double speed);
	bool needUpdate();
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	double getScaleX() const { return sprite.getScale().x; }
	double getScaleY() const { return sprite.getScale().y; }
};

class GifManager {
private:
	sf::Texture texture;
	std::vector<Gif> gifs;
	double width;
	double height;
	int totalFrame;
	double speed;
	double scaleX;
	double scaleY;
public:
	void addGif(int x, int y);
	void popGif() { gifs.pop_back();  }
	void load(std::string filename, int x, int y, int width, int height, int totalFrame, double speed, double scaleX, double scaleY);
	void update();
	void drawTo(sf::RenderWindow& window);
	double getWidth() const { return width; }
	double getHeight() const { return height; }
	double getScaleX() const { return scaleX; }
	double getScaleY() const { return scaleY; }
};