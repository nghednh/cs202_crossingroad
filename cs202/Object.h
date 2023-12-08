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
	Object(sf::Texture &ob) {
		sprite.setTexture(ob);
	}
	void setTexture(sf::Texture &tex) {
		sprite.setTexture(tex);
	}
	void drawTo(sf::RenderWindow &win) {
		win.draw(sprite);
	}
	void setPos(int x, int y) {
		sprite.setPosition(x*64*2, y);
	}
	void setScale(int x, int y) {
		sprite.setScale(x, y);
	}

	void setTextureRect(int a, int b, int c, int d) {
		sprite.setTextureRect(sf::IntRect(a,b,c,d));
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
	virtual void setup(sf::Texture & tex) {
		setTexture(tex);
		setTextureRect(0, 0, 64, 64);
		setScale(2, 2);
	}
	virtual bool rfleft() {
		return true;
	}
};
class ObjectStable : public Object {
public:
	int returnx() {
		return this->x;
	}
	virtual void setup(sf::Texture& tex) {
		setTexture(tex);
		setTextureRect(0, 0, 64, 64);
		setScale(2, 2);
	}
};
class ObjectMoving : public Object {
private:
	bool fleft;
public:
	void setup(sf::Texture& tex) {
		setTexture(tex);
		setTextureRect(0, 0, 100, 100);
		setScale(1.28,1.28);
	}
	int returnx(){
		return x;
	}
	int randomx() {
		if (rand()%2==0) {
			x = 13;
			fleft = false;
		}
		else {
			x = 0;
			fleft = true;
		}
		return x;
	}
	bool rfleft() {
		return fleft;
	}
};