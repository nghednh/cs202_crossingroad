#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Button.h"
#include "Gif.h"

class Game {
private:
	enum State {
		MENU,
		PLAY,
		PAUSE,
		TUTORIAL,
		CREDIT
	};
	State state;
	sf::RenderWindow window;
private:
	sf::Texture _backgroundMenu;
	sf::Sprite backgroundMenu;
	sf::Texture _backgroundPlay;
	sf::Sprite backgroundPlay;
	sf::Texture _object;
	Gif fireGif;

	sf::Sound backgroundMusic;
	sf::SoundBuffer backgroundBuffer;
	sf::Sound clickSound;
	sf::SoundBuffer clickBuffer;
	sf::Music music;

	sf::Font font;
	Button playButton;
	Button tutorialButton;
	Button creditButton;
	Button exitButton;
	Button selectArrow;
public:
	Game();
	void loadSound();
	void loadTexture();
	void run();
	void handleEvent();
	void update();
	void draw();
};