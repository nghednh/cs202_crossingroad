#include "Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Cross The Road", sf::Style::Close),
playButton("play", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
tutorialButton(" tutorial ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
creditButton("  credit  ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
exitButton("   exit   ", { 230, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
selectArrow(">        <", { 500, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font)
{
	window.setFramerateLimit(60);
	this->state = MENU;
	loadTexture();
	loadSound();
	font.loadFromFile("resource/fibberish.ttf");
	playButton.setPosition((int)((1600 - playButton.getSize().x) / 2), 350 + 10);
	tutorialButton.setPosition((int)((1600 - exitButton.getSize().x) / 2), 450);
	creditButton.setPosition((int)((1600 - tutorialButton.getSize().x) / 2), 550);
	exitButton.setPosition((int)((1600 - tutorialButton.getSize().x) / 2), 650);
	selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 350 - 5);
	for (int i = 0; i < 9; i++)			
		laneManager.addLane(900 - i * 128);
	shouldGoFaster = false;
	laneManager.initCharacter(&character);
}

void Game::loadSound()
{
	if (!musicMenu.openFromFile("resource/sound/background.wav"))
		std::cout << "Error" << std::endl;
	if (!clickBuffer.loadFromFile("resource/sound/click.wav"))
		std::cout << "Error" << std::endl;
	if (!musicInGame.openFromFile("resource/sound/musicInGame.wav"))
		std::cout << "Error" << std::endl;
	musicMenu.play();
	musicMenu.setLoop(true);
	clickSound.setBuffer(clickBuffer);
	musicInGame.setLoop(true);
}

void Game::loadTexture()
{
	_backgroundMenu.loadFromFile("resource/background/menu.jpg");
	backgroundMenu.setTexture(_backgroundMenu);

	_backgroundPlay.loadFromFile("resource/background/play.jpg");
	backgroundPlay.setTexture(_backgroundPlay);

	_backgroundCredit.loadFromFile("resource/background/credit.jpg");
	backgroundCredit.setTexture(_backgroundCredit);

	_object.loadFromFile("resource/object/object.png");

	_filter.loadFromFile("resource/filter.png");
	filter.setTexture(_filter);

	clickGif.load("resource/clickSprite.png", 0, 0, 100, 100, 30, 0.2, 2, 2);

	_backButton0.loadFromFile("resource/backButton0.png");
	_backButton1.loadFromFile("resource/backButton1.png");
	backButton.setTexture(_backButton0);
	backButton.setPosition(50, 20);
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
				clickSound.play();
				clickGif.addGif(sf::Mouse::getPosition(window).x - clickGif.getScaleX() * clickGif.getWidth() / 2, sf::Mouse::getPosition(window).y - clickGif.getScaleY() * clickGif.getHeight() / 2);
				if (playButton.isMouseOver(window)) {
					this->state = PLAY;
					clickGif.popGif();
					musicMenu.stop();
					musicInGame.play();
				}
				if (exitButton.isMouseOver(window)) {
					window.close();
				}
				if (creditButton.isMouseOver(window)) {
					this->state = CREDIT;
					clickGif.popGif();
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
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
					musicInGame.stop();
					musicMenu.play();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				laneManager.processUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				laneManager.processDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				laneManager.processLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				laneManager.processRight();
			}
		}
		else if (state == CREDIT) {
			if (event.type == sf::Event::MouseButtonReleased) {
				clickSound.play();
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
				}
			}
		}
		else if (state == TUTORIAL) {
			if (event.type == sf::Event::MouseButtonReleased) {
				clickSound.play();
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
				}
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
		clickGif.update();
	}
	else if (state == PLAY) {
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);
		//shouldGoFaster = character.shouldGoFaster();
		laneManager.update(shouldGoFaster);
		character.update();
	}
	else if (state == CREDIT) {
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);
	}
	else if (state == TUTORIAL) {
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
	if (state == MENU)
	{
		window.draw(backgroundMenu);
		playButton.drawTo(window);
		exitButton.drawTo(window);
		tutorialButton.drawTo(window);
		creditButton.drawTo(window);
		selectArrow.drawTo(window);
		clickGif.drawTo(window);
	}
	else if (state == PLAY)
	{
		//window.draw(backgroundPlay);
		window.draw(backgroundPlay);
		laneManager.drawTo(window);
		window.draw(filter);
		window.draw(backButton);
		//character.draw(window);
	}
	else if (state == CREDIT) {
		window.draw(backgroundCredit);
		window.draw(backButton);
	}
	else if (state == TUTORIAL) {
		window.draw(backButton);
	}
	window.display();
}
