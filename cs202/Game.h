#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Button.h"
#include "Gif.h"
#include "Lane.h"
#include "Character.h"

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
	sf::Texture _backgroundCredit;
	sf::Sprite backgroundCredit;
	sf::Texture _object;
	GifManager clickGif;
	LaneManager laneManager;
	Character character;
	bool shouldGoFaster;

	sf::Sound backgroundMusic;
	sf::SoundBuffer backgroundBuffer;
	sf::Sound clickSound;
	sf::SoundBuffer clickBuffer;
	sf::Music musicMenu;
	sf::Music musicInGame;

	sf::Font font;
	Button playButton;
	Button tutorialButton;
	Button creditButton;
	Button exitButton;
	Button selectArrow;

	sf::Texture _backButton0;
	sf::Texture _backButton1;
	sf::Sprite backButton;
public:
	Game();
	void loadSound();
	void loadTexture();
	void run();
	void handleEvent();
	void update();
	void draw();
};