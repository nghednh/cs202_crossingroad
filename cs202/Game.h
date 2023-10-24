#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game {
private:
	enum State {
		MENU,
		PLAY,
		PAUSE
	};
	State state;
	sf::RenderWindow window;
private:
	sf::Texture _backgroundMenu;
	sf::Sprite backgroundMenu;
	sf::Texture _backgroundPlay;
	sf::Sprite backgroundPlay;

	sf::Font font;
public:
	Game();
	void loadTexture();
	void run();
	void update();
	void draw();
};