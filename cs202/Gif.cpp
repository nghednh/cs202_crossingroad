#include "Gif.h"

void Gif::load(const sf::Texture& texture, int x, int y, int width, int height, int totalFrame, double speed)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->totalFrame = totalFrame;
	this->currentFrame = 0;
	this->speed = speed;
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(x, y, width, height));
	frameTime = speed / totalFrame;
	loop = false;
}

void Gif::update()
{
	//while (currentFrame < totalFrame) {
		double time = clock.getElapsedTime().asSeconds();
		if (time > frameTime) {
			this->currentFrame++;
			clock.restart();
		}
		if (this->currentFrame >= this->totalFrame) {
			//if (loop)
				this->currentFrame = 0;
			//else
				//this->currentFrame = this->totalFrame;
		}
		this->sprite.setTextureRect(sf::IntRect(this->x + this->currentFrame * this->width, this->y, this->width, this->height));
	//}
}

void Gif::drawTo(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void Gif::setPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
}

void Gif::setScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

void Gif::setSpeed(double speed)
{
	this->speed = speed;
}

bool Gif::needUpdate()
{
	if (this->currentFrame + 1 >= this->totalFrame && loop == false)
		return false;
	return true;
}

void GifManager::addGif(int x, int y)
{
	Gif gif;
	gif.load(this->texture, 0, 0, this->width, this->height, this->totalFrame, this->speed);
	gif.setScale(this->scaleX, this->scaleY);
	gif.setPosition(x, y);
	gifs.push_back(gif);
}

void GifManager::load(std::string filename, int x, int y, int width, int height, int totalFrame, double speed, double scaleX, double scaleY)
{
	this->texture.loadFromFile(filename);
	this->width = width;
	this->height = height;
	this->totalFrame = totalFrame;
	this->speed = speed;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

void GifManager::update()
{
	for (int i = 0; i < gifs.size(); i++) {
		if (gifs[i].needUpdate())
			gifs[i].update();
		else
			gifs.erase(gifs.begin() + i);
	}
}

void GifManager::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < gifs.size(); i++) {
		gifs[i].drawTo(window);
	}
}