#include "Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Cross The Road", sf::Style::Close),
playButton("Play", { 230, 90 }, 40, beige, darkBeige, font),
exitButton("Exit", { 230, 90 }, 40, beige, darkBeige, font),
tutorialButton("Tutorial", { 230, 90 }, 40, beige, darkBeige, font)
{
	this->state = MENU;
	loadTexture();
	playButton.setPosition((int)((1600 - playButton.getSize().x) / 2), 350);
	exitButton.setPosition((int)((1600 - exitButton.getSize().x) / 2), 500);
	tutorialButton.setPosition((int)((1600 - tutorialButton.getSize().x) / 2), 650);
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
		handleEvent();
		update();
		draw();
	}
}

void Game::handleEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::MouseButtonReleased) {
			if (playButton.isMouseOver(window)) {
				this->state = PLAY;
			}
			if (exitButton.isMouseOver(window)) {
				window.close();
			}
			if (tutorialButton.isMouseOver(window)) {
				this->state = TUTORIAL;
			}
		}
	}
}

void Game::update()
{
	if (state == MENU) {
		playButton.update(window);
		exitButton.update(window);
		tutorialButton.update(window);
	}
	else if (state == PLAY) {
	}
}

void Game::draw()
{
	window.clear();
	if (this->state == MENU)
	{
		window.draw(backgroundMenu);
		playButton.drawTo(window);
		exitButton.drawTo(window);
		tutorialButton.drawTo(window);
	}
	else if (this->state == PLAY)
	{
		window.draw(backgroundPlay);
	}
	window.display();
}
