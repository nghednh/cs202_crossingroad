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
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Game {
private:
	enum State {
		MENU,
		PLAY,
		HIGHSCORE,
		SETTING,
		CREDIT
	};
	State state;
	sf::RenderWindow window;
private:
	sf::Texture _backgroundMenu;
	sf::Sprite backgroundMenu;

	sf::Texture _backgroundPlay;
	sf::Sprite backgroundPlay;

	sf::Texture _backgroundHighscore;
	sf::Sprite backgroundHighscore;

	sf::Texture _backgroundCredit;
	sf::Sprite backgroundCredit;

	sf::Texture _backgroundSetting;
	sf::Sprite backgroundSetting;

	sf::Texture _object;

	sf::Sprite filter;
	sf::Texture _filter;

	sf::Texture _filterCountdown;
	sf::Sprite filterCountdown;

	sf::Sprite gameOver;
	sf::Texture _gameOver;

	sf::Texture crash;
	sf::Sprite crashSprite;
	bool crashed;
	int crashAnimationCounter;

	GifManager clickGif;
	LaneManager laneManager;
	Character character;
	bool shouldGoFaster;

	sf::Sound backgroundMusic;
	sf::SoundBuffer backgroundBuffer;

	sf::Sound clickSound;
	sf::SoundBuffer clickBuffer;
	bool crashSoundPlayed;

	sf::Sound crashSound;
	sf::SoundBuffer crashBuffer;

	sf::Music musicMenu;
	sf::Music musicInGame;

	sf::Font font;

	Button newGameButton;
	Button playButton;
	Button highscoreButton;
	Button settingButton;
	Button creditButton;
	Button exitButton;
	Button selectArrow;

	sf::Texture _backButton0;
	sf::Texture _backButton1;
	sf::Sprite backButton;

	sf::Texture _replayButton0;
	sf::Texture _replayButton1;
	sf::Sprite replayButton;

	sf::Texture _addVol0;
	sf::Texture _addVol1;
	sf::Texture _minVol0;
	sf::Texture _minVol1;
	sf::Sprite addVol;
	sf::Sprite minVol;

	sf::Texture _up;
	sf::Texture _down;
	sf::Texture _right;
	sf::Texture _left;
	sf::Texture _up1;
	sf::Texture _down1;
	sf::Texture _right1;
	sf::Texture _left1;
	sf::Sprite up;
	sf::Sprite down;
	sf::Sprite left;
	sf::Sprite right;

	sf::Sprite replayButton;
	int score[5]{};

	int countdown;

	sf::Clock clock;

public:
	Game();
	void loadSound();
	void loadTexture();
	void run();
	void handleEvent();
	void update();
	void draw();
	void save();
	void loadFromFile();
	void addVolumn();
	void minVolumn();
	void drawVolumn();
	void drawDirect();
};