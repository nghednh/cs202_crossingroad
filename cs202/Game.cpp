#include "Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Cross The Road", sf::Style::Close),
playButton("  Play  ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
exitButton("  Exit  ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
tutorialButton("Tutorial", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
selectArrow(">        <", {500, 90}, 60, sf::Color::Transparent, darkBeige, font)
{
	this->state = MENU;
	loadTexture();
	loadSound();
	font.loadFromFile("resource/fibberish.ttf");
	playButton.setPosition((int)((1600 - playButton.getSize().x) / 2), 350);
	tutorialButton.setPosition((int)((1600 - exitButton.getSize().x) / 2), 500);
	exitButton.setPosition((int)((1600 - tutorialButton.getSize().x) / 2), 650);
	selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 350-20);
}

void Game::loadSound()
{
	if (!music.openFromFile("resource/background.wav"))
		std::cout << "Error" << std::endl;
	music.play();
	music.setLoop(true);
	/*if (!backgroundBuffer.loadFromFile("resource/background.wav"))
	{
		std::cout << "Error" << std::endl;
	}
	backgroundMusic.setBuffer(backgroundBuffer);
	backgroundMusic.play();
	backgroundMusic.setLoop(true);*/
	if (!clickBuffer.loadFromFile("resource/click.wav"))
	{
		std::cout << "Error" << std::endl;
	}
	clickSound.setBuffer(clickBuffer);
}

void Game::loadTexture()
{
	_backgroundMenu.loadFromFile("resource/menu.jpg");
	backgroundMenu.setTexture(_backgroundMenu);
	_backgroundPlay.loadFromFile("resource/backgroundPlay.png");
	backgroundPlay.setTexture(_backgroundPlay);
	_object.loadFromFile("resource/object.png");
	fireGif.load(_object, 96, 125, 16, 16, 5);
	fireGif.setScale(4, 4);
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
			clickSound.play();
			fireGif.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
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
		playButton.updateTransparent(window);
		if (playButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 350 - 20);
		tutorialButton.updateTransparent(window);
		if (tutorialButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 500 - 20);
		exitButton.updateTransparent(window);
		if (exitButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 650 - 20);
		fireGif.update();
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
		selectArrow.drawTo(window);
		fireGif.drawTo(window);
	}
	else if (this->state == PLAY)
	{
		window.draw(backgroundPlay);
	}
	window.display();
}
