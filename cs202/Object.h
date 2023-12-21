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
	void drawTo(sf::RenderWindow& win) {
		win.draw(sprite);
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
	virtual int randomx() {
		if (rand()%2!=0) {
			x = rand()%13;
			fleft = false;
		}
		else {
			x = rand()%13;
			fleft = true;
		}
		return x;
	}
	virtual bool rfleft() {
		return fleft;
	}
	int randomxx(bool l) {
		if (!l) {
			x = rand()%13;
			fleft = false;
		}
		else {
			x = rand()%13;
			fleft = true;
		}
		return x;
	}
	void setPos(int x, int y) {
		if (!rfleft()) sprite.setPosition(x * 200, y - 30);
		else sprite.setPosition(x*200-1000, y - 30);
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