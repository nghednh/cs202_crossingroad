#include "Seminar.h"

Texture& bulletText = BulletTexture::Instance().getBulletTexture();

bool Bullet::update()
{
	x += sin(atan((directionX - x) / (directionY - y))) * speed;
	y += cos(atan((directionX - x) / (directionY - y))) * speed;

	x /= 60;
	y /= 60;

	if (x > 1600 && y > 900) return false;
	else 
	{
		texture.setPosition(x, y);
		return true;
	}
}

Sprite& Bullet::getTexture()
{
	return texture;
}

Bullet::Bullet(Player& src, double desX, double desY, double speed) :
	x(src.x), y(src.y), directionX(desX), directionY(desY), speed(speed) 
{
	texture.setTexture(bulletText);
}

void Player::render(RenderWindow& window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].update())
			window.draw(bullets[i].getTexture());
		else
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void Player::addParticle(double desX, double desY, double speed)
{
	Bullet tmp(*this, desX, desY, speed);
	bullets.push_back(tmp);
}

Game::Game() : window(sf::VideoMode(1600, 900), "Game", sf::Style::Close) {};

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

			for (int i = 0; i < player.size(); i++)
				player[i].Player::render(window);
		}
		render();
	}
}