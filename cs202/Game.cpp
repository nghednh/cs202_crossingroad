#include "Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Cross The Road", sf::Style::Close),
playButton("play", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
tutorialButton(" tutorial ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
creditButton("  credit  ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
exitButton("   exit   ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
selectArrow(">        <", { 500, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font)
{
	this->state = MENU;
	loadTexture();
	loadSound();
	font.loadFromFile("resource/fibberish.ttf");
	playButton.setPosition((int)((1600 - playButton.getSize().x) / 2), 350 + 10);
	tutorialButton.setPosition((int)((1600 - exitButton.getSize().x) / 2), 450);
	creditButton.setPosition((int)((1600 - tutorialButton.getSize().x) / 2), 550);
	exitButton.setPosition((int)((1600 - tutorialButton.getSize().x) / 2), 650);
	selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 350 - 5);
}

void Game::loadSound()
{
	if (!music.openFromFile("resource/background.wav"))
		std::cout << "Error" << std::endl;
	music.play();
	music.setLoop(true);
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
	_click.loadFromFile("resource/clickSprite.png");
	clickGif.load(_click, 0, 0, 100, 100, 30, 0.1);
	clickGif.setScale(2, 2);
	//clickGif.setSpeed(0.1);
	_backButton0.loadFromFile("resource/backButton0.png");
	_backButton1.loadFromFile("resource/backButton1.png");
	backButton.setTexture(_backButton0);
	backButton.setPosition(10, 10);
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
		if (state == MENU)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				clickGif.update();
				clickSound.play();
				clickGif.setPosition(sf::Mouse::getPosition(window).x - clickGif.getScaleX() * clickGif.getWidth() / 2, sf::Mouse::getPosition(window).y - clickGif.getScaleY() * clickGif.getHeight() / 2);
				if (playButton.isMouseOver(window)) {
					this->state = PLAY;
				}
				if (exitButton.isMouseOver(window)) {
					window.close();
				}
				if (creditButton.isMouseOver(window)) {
					this->state = CREDIT;
				}
				if (tutorialButton.isMouseOver(window)) {
					this->state = TUTORIAL;
				}
			}
		}
		else if (state == PLAY)
		{
			if (event.type == sf::Event::MouseButtonReleased) {
				clickSound.play();
				state = MENU;
			}
		}
	}
}

void Game::update()
{
	if (state == MENU) {
		playButton.updateHalfTransparent(window);
		tutorialButton.updateHalfTransparent(window);
		creditButton.updateHalfTransparent(window);
		exitButton.updateHalfTransparent(window);
		selectArrow.updateHalfTransparent(window);
		if (playButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 350 - 5);
		if (tutorialButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 450 - 5);
		if (creditButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 550 - 5);
		if (exitButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 650 - 5);
		if (playButton.isMouseOver(window) || tutorialButton.isMouseOver(window) || creditButton.isMouseOver(window) || exitButton.isMouseOver(window))
			selectArrow.setTextColor(darkBeige);
		else
			selectArrow.setTextColor(sf::Color::Transparent);
		if (clickGif.needUpdate())
			clickGif.update();
	}
	else if (state == PLAY) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->state = MENU;
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);
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
		creditButton.drawTo(window);
		selectArrow.drawTo(window);
		if (clickGif.needUpdate())
			clickGif.drawTo(window);
	}
	else if (this->state == PLAY)
	{
		window.draw(backgroundPlay);
		window.draw(backButton);
	}
	window.display();
}
