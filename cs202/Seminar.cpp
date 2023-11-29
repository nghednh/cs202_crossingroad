#include "Seminar.h"

Particle::Particle(double x, double y, int textNum)
{
	sprite.setTexture(SetTexture::getTexture(textNum));
	sprite.setPosition(x, y);
}

MovingParticle::MovingParticle(int x, int y, double desX, double desY, double speed) 
: Particle(x, y, 0), directionX(desX), directionY(desY), speed(speed) {}

bool MovingParticle::update()
{
	Vector2f tmp = Particle::getPos();

	double x = tmp.x + sin(atan((directionX - tmp.x) / (directionY - tmp.y))) * speed;
	double y = tmp.y + cos(atan((directionX - tmp.x) / (directionY - tmp.y))) * speed;

	x /= 60;	y /= 60;

	if (x > 1600 && y > 900) return false;
	else
	{
		Particle::update(x, y);
		return true;
	}
}

void Particle::update(double x, double y)
{
	sprite.setPosition(x, y);
}

Vector2f Particle::getPos()
{
	return sprite.getPosition();
}

Game::Game() : window(sf::VideoMode(1600, 900), "Game", sf::Style::Close) {};

Sprite& Particle::getSprite()
{
	return sprite;
}

Sprite& MovingParticle::getSprite()
{
	return Particle::getSprite();
}

void Game::render()
{
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}
		window.clear();
		updateAndDraw();
		window.display();
	}
}

void Game::updateAndDraw()
{
	for (int i = 0; i < mps.size(); i++)
		if (mps[i].update())
			window.draw(mps[i].getSprite());
		else
		{
			mps.erase(mps.begin() + i);
			i--;
		}
	for (int i = 0; i < particles.size(); i++)
		window.draw(particles[i].getSprite());
}

void Game::addMovingParticle(Unit& src, Unit& des, double speed)
{
	MovingParticle tmp(src.x, src.y, des.x, des.y, speed);
	mps.push_back(tmp);
}

void Game::addParticle(double x, double y)
{
	Particle tmp(x, y, 1);
	particles.push_back(tmp);
}

void Unit::fireAt(Unit& target)
{
	Game::addMovingParticle(*this, target, 100);
}

void Unit::placeGun()
{
	Game::addParticle(x, y);
}

/*

void Player::addParticle(double desX, double desY, double speed)
{
	Bullet tmp(*this, desX, desY, speed);
	bullets.push_back(tmp);
}
*/

Unit::Unit(int x, int y) : Game()
{
	this->x = x;
	this->y = y;
}