#include "Game.h"

Game::Game(): window(sf::VideoMode(1600, 900), "Cross The Road", sf::Style::Close)
{
	this->state = MENU;
	loadTexture();
}

void Game::loadTexture()
{
	_backgroundMenu.loadFromFile("menu.jpg");
	backgroundMenu.setTexture(_backgroundMenu);
	_backgroundPlay.loadFromFile("resource/backgroundPlay.png");
	backgroundPlay.setTexture(_backgroundPlay);
	font.loadFromFile("resource/fibberish.ttf");
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
		draw();
	}
}

void Game::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::MouseButtonReleased) {
		}
	}

}

void Game::draw()
{
	window.clear();
	if (this->state == MENU)
		window.draw(backgroundMenu);
	else if (this->state == PLAY)
		window.draw(backgroundPlay);
	window.display();
}
