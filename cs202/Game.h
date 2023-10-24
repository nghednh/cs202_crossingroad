#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include "Button.h"

class Game {
private:
	enum State {
		MENU,
		PLAY,
		PAUSE,
		TUTORIAL
	};
	State state;
	sf::RenderWindow window;
private:
	sf::Texture _backgroundMenu;
	sf::Sprite backgroundMenu;
	sf::Texture _backgroundPlay;
	sf::Sprite backgroundPlay;

	sf::Font font;
	Button playButton;
	Button exitButton;
	Button tutorialButton;
public:
	Game();
	void loadTexture();
	void run();
	void handleEvent();
	void update();
	void draw();
};