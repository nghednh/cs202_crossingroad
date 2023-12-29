#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
class Object {
protected:
	sf::Sprite sprite;
	int x;
public:
	Object() = default;
	Object(sf::Texture& ob) {
		sprite.setTexture(ob);
	}
	void setTexture(sf::Texture& tex) {
		sprite.setTexture(tex);
	}
	virtual void drawTo(sf::RenderWindow& win, sf::Font& font) {
		win.draw(sprite);
		sf::Text text;
		text.setString(std::to_string(x));
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setFont(font);
		text.setPosition(sprite.getPosition().x, sprite.getPosition().y);
		win.draw(text);
	}
	virtual void setPos(int x, int y) {
		sprite.setPosition(x * 64 * 2 - 20, y - 26);
	}
	void setScale(int x, int y) {
		sprite.setScale(x, y);
	}

	void setTextureRect(int a, int b, int c, int d) {
		sprite.setTextureRect(sf::IntRect(a, b, c, d));
	}
	void move(int x, int y) {
		sprite.move(x, y);
	}
	void setX(int x) {
		this->x = x;
	}
	virtual int randomx() {
		x = rand() % 13;
		return x;
	}
	virtual int returnx() {
		return this->x;
	}
	virtual void setup(sf::Texture& tex) {
		setTexture(tex);
		setTextureRect(0, 0, 64, 64);
		setScale(2.56, 2.56);
	}
	virtual bool rfleft() {
		return true;
	}
	virtual int randomxx(bool l) {
		return 0;
	}
	double spriteX() {
		return sprite.getPosition().x;
	}
	double spriteY() {
		return sprite.getPosition().y;
	}
	int spriteWidth() {
		return sprite.getTextureRect().width;
	}
	int spriteHeight() {
		return sprite.getTextureRect().height;
	}
	double spriteScaleX() {
		return sprite.getScale().x;
	}
	double spriteScaleY() {
		return sprite.getScale().y;
	}
};
class ObjectStable : public Object {
private:
public:
	int returnx() {
		return this->x;
	}
	virtual void setup(sf::Texture& tex, float scaleX, float scaleY, int xTopLeft, int yTopLeft, int width, int height) {
		setTexture(tex);
		setTextureRect(xTopLeft, yTopLeft, width, height);
		setScale(scaleX, scaleY);
	}
	virtual int randomx(bool*& idx, int n) {
		for (int i = 0; i > -1; i++) {
			int tmp = rand() % 13;
			if (idx[tmp] == 0) {
				x = tmp;
				idx[tmp] = 1;
				break;
			}
		}
		return x;
	}
};
class ObjectMoving : public Object {
private:
	bool fleft;
public:
	virtual void setup(sf::Texture& tex, float scaleX, float scaleY, int xTopLeft, int yTopLeft, int width, int height) {
		setTexture(tex);
		setTextureRect(xTopLeft, yTopLeft, width, height);
		setScale(scaleX, scaleY);
	}
	int returnx() {
		return this->x;
	}
	virtual int randomx(bool *& idx) {
		if (rand()%2!=0) {
			for (int i = 0; i > -1; i++) {
				int tmp = rand() % 13;
				if (idx[tmp] == 0) {
					x = tmp;
					idx[tmp] = 1;
					break;
				}
			}
			fleft = false;
		}
		else {
			for (int i = 0; i > -1; i++) {
				int tmp = rand() % 13;
				if (idx[tmp] == 0) {
					x = tmp;
					idx[tmp] = 1;
					break;
				}
			}
			fleft = true;
		}
		return x;
	}
	virtual bool rfleft() {
		return fleft;
	}
	int randomxx(bool l, bool*& idx) {
		if (!l) {
			for (int i = 0; i > -1; i++) {
				int tmp = rand() % 13;
				if (idx[tmp] == 0) {
					x = tmp;
					idx[tmp] = 1;
					break;
				}
			}
			fleft = false;
		}
		else {
			for (int i = 0; i > -1; i++) {
				int tmp = rand() % 13;
				if (idx[tmp] == 0) {
					x = tmp;
					idx[tmp] = 1;
					break;
				}
			}
			fleft = true;
		}
		return x;
	}
	void setPos(int x, int y) {
		if (!rfleft()) sprite.setPosition(x * 200, y - 30);
		else sprite.setPosition(x*200-1000, y - 30);
	}
	void drawTo(sf::RenderWindow& win, sf::Font& font) {
		win.draw(sprite);
		sf::Text text;
		text.setString(std::to_string(x));
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setFont(font);
		text.setPosition(sprite.getPosition().x, sprite.getPosition().y);
		win.draw(text);
		text.setString("width: " + std::to_string(spriteWidth() * spriteScaleX()));
		text.setPosition(sprite.getPosition().x + this->spriteWidth() * spriteScaleX(), sprite.getPosition().y);
		//if (rfleft()) text.setPosition(sprite.getPosition().x - this->spriteWidth() * spriteScaleX(), sprite.getPosition().y);
		win.draw(text);
	}
};
class TrainObject : public ObjectMoving {
public:
	
	virtual void setup(sf::Texture& tex) {
		setTexture(tex);
		setTextureRect(0, 0, 512, 64);
		setScale(4, 4);
	}
	virtual void setPos(int x, int y) {
		if (!rfleft()) sprite.setPosition(x * 64*2+2000, y - 120);
		else sprite.setPosition(x * 64 * 2-2000, y - 120);
	}
};