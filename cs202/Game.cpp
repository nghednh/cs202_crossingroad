#include "Game.h"

Game::Game() : window(sf::VideoMode(1600, 900), "Cross The Road", sf::Style::Close),
newGameButton(" new game ", { 230, 90 }, 50, sf::Color::Transparent, sf::Color::Transparent, font),
playButton("continue", { 230, 90 }, 50, sf::Color::Transparent, sf::Color::Transparent, font),
highscoreButton("highscore", { 230, 90 }, 50, sf::Color::Transparent, sf::Color::Transparent, font),
settingButton(" setting ", { 230, 90 }, 50, sf::Color::Transparent, sf::Color::Transparent, font),
creditButton("  credit  ", { 230, 90 }, 50, sf::Color::Transparent, sf::Color::Transparent, font),
exitButton("save & exit", { 230, 90 }, 50, sf::Color::Transparent, sf::Color::Transparent, font),
selectArrow(">           <", { 500, 90 }, 60, sf::Color::Transparent, sf::Color::Transparent, font),
textbox(50, sf::Color(255, 230, 153), sf::Color::Transparent, false)
{
	window.setFramerateLimit(60);
	this->state = MENU;
	loadTexture();
	loadSound();
	loadScore();
	font.loadFromFile("resource/fibberish.ttf");
	newGameButton.setPosition((int)((1600 - newGameButton.getSize().x) / 2), 245);
	playButton.setPosition((int)((1600 - playButton.getSize().x) / 2), 335-5);
	highscoreButton.setPosition((int)((1600 - highscoreButton.getSize().x) / 2), 425 + 5);
	settingButton.setPosition((int)((1600 - exitButton.getSize().x) / 2), 515 + 5);
	creditButton.setPosition((int)((1600 - settingButton.getSize().x) / 2), 605);
	exitButton.setPosition((int)((1600 - settingButton.getSize().x) / 2), 695);
	selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 350 - 5);
	textbox.setPosition(600, 750);
	textbox.setBoxPosition(600, 750);
	textbox.setBoxSize(sf::Vector2f(900, 50));
	textbox.setFont(font);
	textbox.setLimit(true, 20);
	currentScore = -1;
	ifstream in("Save.txt"); string tmp;
	if (in.is_open())
	{
		getline(in, tmp);
		if (!tmp.empty()) loadFromFile();
		else
		{
			for (int i = 0; i < 9; i++)
				laneManager.addLane(900 - i * 128);
			laneManager.initCharacter(&character);
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
			laneManager.addLane(900 - i * 128);
		laneManager.initCharacter(&character);
	}

	update();
	shouldGoFaster = false;
	crashed = false;
	crashAnimationCounter = 0;
	countdown = -1;
	crashSoundPlayed = false;
}

void Game::loadSound()
{
	if (!musicMenu.openFromFile("resource/sound/background.wav"))
		std::cout << "Error" << std::endl;
	if (!clickBuffer.loadFromFile("resource/sound/click.wav"))
		std::cout << "Error" << std::endl;
	if (!musicInGame.openFromFile("resource/sound/musicInGame.wav"))
		std::cout << "Error" << std::endl;
	if (!crashBuffer.loadFromFile("resource/sound/GameOver2.wav"))
		std::cout << "Error" << std::endl;
	crashSound.setBuffer(crashBuffer);
	musicMenu.play();
	musicMenu.setLoop(true);
	clickSound.setBuffer(clickBuffer);
	musicInGame.setVolume(30);
	musicInGame.setLoop(true);
}

void Game::loadTexture()
{
	_backgroundMenu.loadFromFile("resource/background/menu.jpg");
	backgroundMenu.setTexture(_backgroundMenu);

	_backgroundPlay.loadFromFile("resource/background/play.jpg");
	backgroundPlay.setTexture(_backgroundPlay);

	_backgroundHighscore.loadFromFile("resource/background/highscore.jpg");
	backgroundHighscore.setTexture(_backgroundHighscore);

	_backgroundCredit.loadFromFile("resource/background/credit.jpg");
	backgroundCredit.setTexture(_backgroundCredit);

	_backgroundSetting.loadFromFile("resource/background/setting.jpg");
	backgroundSetting.setTexture(_backgroundSetting);

	_object.loadFromFile("resource/object/object.png");

	_filter.loadFromFile("resource/filter.png");
	filter.setTexture(_filter);

	_filter1.loadFromFile("resource/filter1.png");
	filter1.setTexture(_filter1);

	_filterCountdown.loadFromFile("resource/countdown.png");
	filterCountdown.setTexture(_filterCountdown);

	_gameOver.loadFromFile("resource/gameOver.png");
	gameOver.setTexture(_gameOver);
	gameOver.setPosition(0, 0);

	crash.loadFromFile("resource/explode.png");
	crashSprite.setTexture(crash);
	crashSprite.setTextureRect(sf::IntRect(0, 0, 120, 109));
	crashSprite.setScale(2, 2);

	clickGif.load("resource/clickSprite.png", 0, 0, 100, 100, 30, 0.2, 2, 2);

	_backButton0.loadFromFile("resource/backButton0.png");
	_backButton1.loadFromFile("resource/backButton1.png");
	_addVol0.loadFromFile("resource/increaseButton0.png");
	_addVol1.loadFromFile("resource/increaseButton1.png");
	_minVol0.loadFromFile("resource/decreaseButton0.png");
	_minVol1.loadFromFile("resource/decreaseButton1.png");
	backButton.setTexture(_backButton0);
	backButton.setPosition(50, 20);
	addVol.setTexture(_addVol0);
	minVol.setTexture(_minVol0);
	addVol.setPosition(1050, 220);
	minVol.setPosition(920, 220);

	_up.loadFromFile("resource/keyButton0.png");
	_down.loadFromFile("resource/keyButton0.png");
	_left.loadFromFile("resource/keyButton0.png");
	_right.loadFromFile("resource/keyButton0.png");
	_up1.loadFromFile("resource/keyButton1.png");
	_down1.loadFromFile("resource/keyButton1.png");
	_left1.loadFromFile("resource/keyButton1.png");
	_right1.loadFromFile("resource/keyButton1.png");
	up.setTexture(_up);
	down.setTexture(_down);
	left.setTexture(_left);
	right.setTexture(_right);
	up.setPosition(1025, 430);
	up.setScale(0.4, 0.4);
	down.setPosition(825, 430);
	down.setScale(0.4, 0.4);
	left.setPosition(625, 430);
	left.setScale(0.4, 0.4);
	right.setPosition(425, 430);
	right.setScale(0.4, 0.4);

	_replayButton0.loadFromFile("resource/replayButton0.png");
	_replayButton1.loadFromFile("resource/replayButton1.png");
	replayButton.setTexture(_replayButton0);
	replayButton.setPosition(1400, 20);
}

void Game::loadScore()
{
	ifstream fin("highscore.txt"); //there are 5 lines, each line is a name and white space then score, want to extract the name and score
	for (int i = 0; i < 5; i++) {
		score[i] = -1;
		name[i] = "Untitled";
	}
	if (!fin.is_open()) {
		cout << "Error opening file highscore.txt" << endl;
	}
	else {
		string tmp;
		istringstream iss;
		int i = 0;
		while (getline(fin, tmp)) {
			iss.str(tmp);
			iss >> name[i];
			iss >> score[i];
			i++;
			iss.clear();
		}
		fin.close();
	}
	for (int i = 0; i < 5; i++) {
		cout << name[i] << " " << score[i] << endl;
	}
}

void Game::saveScore()
{
	ofstream fout("highscore.txt");
	if (!fout.is_open()) {
		cout << "Error opening file highscore.txt" << endl;
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (score[i] == -1)
			continue;
		fout << name[i] << " " << score[i] << endl;
	}
	fout.close();
}

void Game::run()
{
	while (window.isOpen())
	{
		handleEvent();
		update();
		draw();
	}
	saveScore();
}

void Game::handleEvent()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (state == MENU)
		{

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				clickSound.play();
				if (newGameButton.isMouseOver(window)) {
					this->state = PLAY;
					musicMenu.stop();
					musicInGame.play();
					musicInGame.setLoop(true);
					character.reset();
					laneManager.reset();
					crashed = false;
					crashAnimationCounter = 0;
					crashSoundPlayed = false;
					laneManager.initCharacter(&character);
					countdown = 4;
					currentScore = -1;
				}
				else if (playButton.isMouseOver(window)) {
					countdown = 4;
					this->state = PLAY;
					musicMenu.stop();
					if (!crashed)
						musicInGame.play();
				}
				else if (highscoreButton.isMouseOver(window)) {
					this->state = HIGHSCORE;
				}
				else if (exitButton.isMouseOver(window)) {
					save();
					window.close();
				}
				else if (creditButton.isMouseOver(window)) {
					this->state = CREDIT;
				}
				else if (settingButton.isMouseOver(window)) {
					this->state = SETTING;
				}
				else
					clickGif.addGif(sf::Mouse::getPosition(window).x - clickGif.getScaleX() * clickGif.getWidth() / 2, sf::Mouse::getPosition(window).y - clickGif.getScaleY() * clickGif.getHeight() / 2);
			}

		}
		else if (state == HIGHSCORE)
		{
			if (event.type == sf::Event::MouseButtonReleased) {
				clickSound.play();
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
				}
				else
					this->clickGif.addGif(sf::Mouse::getPosition(window).x - clickGif.getScaleX() * clickGif.getWidth() / 2, sf::Mouse::getPosition(window).y - clickGif.getScaleY() * clickGif.getHeight() / 2);
			}
		}
		else if (state == PLAY)
		{
			if (event.type == sf::Event::MouseButtonReleased) {
				//clickSound.play();
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
					countdown = -1;
					musicInGame.stop();
					musicMenu.play();
				}
				if (character.isDead())
					if (isMouseOver(replayButton, window)) {
						saveScore();
						this->state = PLAY;
						musicInGame.play();
						musicInGame.setLoop(true);
						character.reset();
						laneManager.reset();
						crashed = false;
						crashAnimationCounter = 0;
						crashSoundPlayed = false;
						laneManager.initCharacter(&character);
						countdown = 4;
						currentScore = -1;
					}
			}
			if (event.type == sf::Event::TextEntered && character.isDead())
			{
				textbox.setSelected(true);
				textbox.typedOn(event);
			}
			else
				textbox.setSelected(false);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (character.isDead())
				{
					if (textbox.getText() != "")
					{
						string tmp = textbox.getText();
						int i = 0;
						while (i < tmp.length() && tmp[i] == ' ')
							i++;
						if (i < tmp.length())
						{
							name[5] = tmp.substr(i);
							score[5] = currentScore;
							for (int i = 0; i < 6; i++)
								for (int j = 0; j < 6 - i - 1; j++) {
									//cout << score[j] << " " << score[j + 1] << endl;
									if (score[j] < score[j+1])
									{
										swap(score[j], score[j+1]);
										swap(name[j], name[j+1]);
										//cout << "Swap" << endl;
									}
								}
							textbox.clear();
							saveScore();
							character.reset();
							laneManager.reset();
							crashed = false;
							crashAnimationCounter = 0;
							crashSoundPlayed = false;
							laneManager.initCharacter(&character);
							countdown = 4;
							currentScore = -1;
							//debug purpose
							//for (int i = 0; i < 6; i++)
								//cout << name[i] << " " << score[i] << endl;
						}
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(u)) {
				laneManager.processUp();
			}
			if (sf::Keyboard::isKeyPressed(d)) {
				laneManager.processDown();
			}
			if (sf::Keyboard::isKeyPressed(l)) {
				laneManager.processLeft();
			}
			if (sf::Keyboard::isKeyPressed(r)) {
				laneManager.processRight();
			}
			/*if (crashed) {
				musicInGame.pause();
				if (!crashSoundPlayed) {
					crashSound.play();
					crashSoundPlayed = true;
				}
			}*/
		}
		else if (state == CREDIT) {
			if (event.type == sf::Event::MouseButtonReleased) {
				//clickSound.play();
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
				}
				else {
					clickSound.play();
					this->clickGif.addGif(sf::Mouse::getPosition(window).x - clickGif.getScaleX() * clickGif.getWidth() / 2, sf::Mouse::getPosition(window).y - clickGif.getScaleY() * clickGif.getHeight() / 2);
				}
			}
		}
		else if (state == SETTING) {
			if (event.type == sf::Event::MouseButtonReleased) {
				//clickSound.play();
				if (isMouseOver(backButton, window)) {
					this->state = MENU;
				}
				else {
					clickSound.play();
					this->clickGif.addGif(sf::Mouse::getPosition(window).x - clickGif.getScaleX() * clickGif.getWidth() / 2, sf::Mouse::getPosition(window).y - clickGif.getScaleY() * clickGif.getHeight() / 2);
				}
				if (isMouseOver(addVol, window)) {
					addVolumn();
				}
				if (isMouseOver(minVol, window)) {
					minVolumn();
				}
				if (isMouseOver(up, window)) {
					if (event.type == sf::Event::MouseButtonReleased)
						if (u == sf::Keyboard::W)
							u = sf::Keyboard::Up;
						else u = sf::Keyboard::W;
				}
				if (isMouseOver(down, window)) {
					if (event.type == sf::Event::MouseButtonReleased)
						if (d == sf::Keyboard::S)
							d = sf::Keyboard::Down;
						else d = sf::Keyboard::S;
				}if (isMouseOver(left, window)) {
					if (event.type == sf::Event::MouseButtonReleased)
						if (l == sf::Keyboard::A)
							l = sf::Keyboard::Left;
						else l = sf::Keyboard::A;
				}
				if (isMouseOver(right, window)) {
					if (event.type == sf::Event::MouseButtonReleased)
						if (r == sf::Keyboard::D)
							r = sf::Keyboard::Right;
						else r = sf::Keyboard::D;
				}
			}
		}
	}
}

void Game::update()
{
	if (state == MENU) {
		newGameButton.updateHalfTransparent(window);
		playButton.updateHalfTransparent(window);
		settingButton.updateHalfTransparent(window);
		highscoreButton.updateHalfTransparent(window);
		creditButton.updateHalfTransparent(window);
		exitButton.updateHalfTransparent(window);
		selectArrow.updateHalfTransparent(window);
		if (newGameButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 245 - 12);
		if (playButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 335 - 12);
		if (highscoreButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 425 - 12);
		if (settingButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 515 - 10);
		if (creditButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 605 - 10);
		if (exitButton.isMouseOver(window))
			selectArrow.setPosition((int)((1600 - selectArrow.getSize().x) / 2), 695 - 10);
		if (newGameButton.isMouseOver(window) || playButton.isMouseOver(window) || highscoreButton.isMouseOver(window) || settingButton.isMouseOver(window) || creditButton.isMouseOver(window) || exitButton.isMouseOver(window))
			selectArrow.setTextColor(darkBeige);
		else
			selectArrow.setTextColor(sf::Color::Transparent);
		clickGif.update();
	}
	else if (state == PLAY) {
		if (countdown <= 0) {
			if (isMouseOver(replayButton, window)) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					replayButton.setTexture(_replayButton1);
			}
			else
				replayButton.setTexture(_replayButton0);
			if (character.isDead()) {
				musicInGame.pause();
			}
			else {
				laneManager.update(shouldGoFaster);
				character.update();
				crashed = character.isCrashed();
				if (crashed) {
					musicInGame.pause();
					if (!crashSoundPlayed) {
						crashSound.play();
						crashSoundPlayed = true;
					}
				}
			}

		}
		if (currentScore <= character.index) {
			currentScore = character.index;
		}
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);
		//shouldGoFaster = character.shouldGoFaster();
	}
	else if (state == HIGHSCORE) {
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);
		clickGif.update();
	}
	else if (state == CREDIT) {
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);
		clickGif.update();
	}
	else if (state == SETTING) {
		if (isMouseOver(backButton, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				backButton.setTexture(_backButton1);
		}
		else
			backButton.setTexture(_backButton0);

		if (isMouseOver(addVol, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				addVol.setTexture(_addVol1);
		}
		else
			addVol.setTexture(_addVol0);

		if (isMouseOver(minVol, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				minVol.setTexture(_minVol1);
		}
		else
			minVol.setTexture(_minVol0);

		if (isMouseOver(up, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				up.setTexture(_up1);
		}
		else up.setTexture(_up);

		if (isMouseOver(down, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				down.setTexture(_down1);
		}
		else down.setTexture(_down);

		if (isMouseOver(right, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				right.setTexture(_right1);
		}
		else right.setTexture(_right);

		if (isMouseOver(left, window)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				left.setTexture(_left1);
		}
		else left.setTexture(_left);

		if (event.type == sf::Event::MouseButtonReleased) {
			backButton.setTexture(_backButton0);
			addVol.setTexture(_addVol0);
			minVol.setTexture(_minVol0);
			up.setTexture(_up);
			down.setTexture(_down);
			right.setTexture(_right);
			left.setTexture(_left);
		}
		clickGif.update();
	}
}

		

void Game::draw()
{
	window.clear();
	if (state == MENU)
	{
		window.draw(backgroundMenu);
		newGameButton.drawTo(window);
		playButton.drawTo(window);
		highscoreButton.drawTo(window);
		exitButton.drawTo(window);
		settingButton.drawTo(window);
		creditButton.drawTo(window);
		selectArrow.drawTo(window);
		clickGif.drawTo(window);
	}
	else if (state == PLAY)
	{
		if (character.isDead()) {
			window.draw(backgroundPlay);
			laneManager.drawTo(window);
			//character.draw(window);
			crashSprite.setPosition(character.getX() - 120 / 2, character.getY() - 109 / 2);
			if (crashAnimationCounter < 29) {
				int time = clock.getElapsedTime().asMilliseconds();
				if (time > 70) {
					clock.restart();
					crashAnimationCounter++;
				}
				crashSprite.setTextureRect(sf::IntRect(120 * crashAnimationCounter, 0, 120, 109));
				musicInGame.pause();
				window.draw(crashSprite);
				//window.draw(filter);
				//crashAnimationCounter++;
				//std::cout << crashAnimationCounter << std::endl;
			}
			else {
				window.draw(gameOver);
				window.draw(replayButton);
				sf::Text score;
				score.setFont(font);
				score.setCharacterSize(60);
				score.setString("Your score: " + to_string(currentScore));
				score.setFillColor(sf::Color::Black);
				score.setPosition(633, 503);
				window.draw(score);
				score.setFillColor(darkBeige);
				score.setPosition(630, 500);
				window.draw(score);
				score.setFillColor(sf::Color(255, 230, 153));
				score.setPosition(630, 497);
				window.draw(score);
				textbox.drawTo(window);
				window.draw(backButton);
			}
			//window.draw(backButton);
		}
		else {
			if (countdown <= 0) {
				window.draw(backgroundPlay);
				laneManager.drawTo(window);
				window.draw(filter);
				window.draw(filter1);
				sf::Text score;
				score.setFont(font);
				score.setCharacterSize(60);
				score.setString("Score: " + to_string(currentScore));
				score.setFillColor(sf::Color::Black);
				score.setPosition(1203, 18);
				window.draw(score);
				score.setFillColor(darkBeige);
				score.setPosition(1200, 15);
				window.draw(score);
				score.setFillColor(sf::Color(255, 230, 153));
				score.setPosition(1200, 12);
				window.draw(score);

				window.draw(backButton);
				//character.draw(window);
			}
			else {
				window.draw(backgroundPlay);
				laneManager.drawTo(window);
				character.draw(window);
				window.draw(filterCountdown);
				if (countdown != 4) {
					sf::Text text;
					text.setFont(font);
					text.setCharacterSize(200);
					text.setString(to_string(countdown));
					text.setFillColor(sf::Color::Black);
					text.setPosition(755, 105);
					window.draw(text);
					text.setFillColor(darkBeige);
					text.setPosition(750, 100);
					window.draw(text);
					text.setFillColor(sf::Color(255, 230, 153));
					text.setPosition(750, 95);
					window.draw(text);
				}
				int time = clock.getElapsedTime().asMilliseconds();
				if (time > 1000) {
					clock.restart();
					countdown--;
					if (countdown == 1 || countdown == 2 || countdown == 3)
						clickSound.play();
				}
				window.draw(backButton);
			}
		}
	}
	else if (state == HIGHSCORE) {
		window.draw(backgroundHighscore);
		window.draw(backButton);
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(50);
		text.setFillColor(darkBeige);
		text.setPosition(400, 250);
		text.setString("NAME");
		window.draw(text);
		text.setString("SCORE");
		text.setPosition(1060, 250);
		window.draw(text);
		ifstream fin("highscore.txt"); //there are 5 lines, each line is a name and white space then score, want to extract the name and score
		if (!fin.is_open()) {
			cout << "Error opening file" << endl;
			return;
		}
		else {
			string tmp;
			istringstream iss;
			int i = 0;
			while (getline(fin, tmp)) {
				iss.str(tmp);
				string name;
				int score;
				iss >> name;
				iss >> score;
				text.setString(name);
				text.setPosition(400, 330 + i * 60);
				window.draw(text);
				text.setString(to_string(score));
				text.setPosition(1060, 330 + i * 60);
				window.draw(text);
				i++;
				iss.clear();
			}
			fin.close();
		}
		clickGif.drawTo(window);
	}
	else if (state == CREDIT) {
		window.draw(backgroundCredit);
		window.draw(backButton);
		clickGif.drawTo(window);
	}
	else if (state == SETTING) {
		window.draw(backgroundSetting);
		window.draw(backButton);
		window.draw(minVol);
		window.draw(addVol);
		window.draw(up);
		window.draw(down);
		window.draw(right);
		window.draw(left);
		drawVolumn();
		drawDirect();
		clickGif.drawTo(window);
	}
	window.display();
}

void Game::save()
{
	laneManager.saveToFile();
	ofstream fout("Save.txt", ios::app);
	fout << "character " << character.info();
	fout << " " << currentScore;
	fout.close();
}

void Game::loadFromFile()
{
	laneManager.LaneManager::setIndex();
	ifstream in("Save.txt");
	string tmp;
	string charInfo = "";

	getline(in, tmp);
	laneManager.setRain(stoi(tmp));

	int indexChar = 0;
	for (int i = 0; i < 9; i++)
	{
		getline(in, tmp);
		laneManager.processEach(tmp, charInfo, indexChar);
	}
	getline(in, tmp);
	istringstream iss(tmp);
	string type;
	iss >> type;
	string xChar, yChar, posChar, indChar, speedChar, deadChar;
	iss >> xChar;
	iss >> yChar;
	iss >> speedChar;
	iss >> deadChar;
	iss >> posChar;
	iss >> indChar;
	iss >> currentScore;

	charInfo = xChar;
	charInfo += " ";
	charInfo += yChar;
	charInfo += " ";
	charInfo += speedChar;
	charInfo += " ";
	charInfo += deadChar;
	charInfo += " ";
	charInfo += posChar;
	charInfo += " ";
	charInfo += indChar;
	character.setInfoFromFile(charInfo);
	laneManager.initCharacter(&character);

	in.close();
}

void Game::addVolumn()
{
//	musicMenu.stop();

	float vol = round(musicMenu.getVolume());
	vol += 10.000000000;
	if (vol >= 100)
	{
		musicMenu.setVolume(100);
		musicInGame.setVolume(100);
		return;
	}
	musicMenu.setVolume(vol);
	musicInGame.setVolume(vol);

//	musicMenu.play();
}

void Game::minVolumn()
{
//	musicMenu.stop();
	float vol = round(musicMenu.getVolume());
	vol -= 10.000000;
	if (vol <= 0)
	{
		musicMenu.setVolume(0);
		musicInGame.setVolume(0);
		return;
	}
	musicMenu.setVolume(vol);
	musicInGame.setVolume(vol);
//	musicMenu.play();
}

void Game::drawVolumn()
{
	sf::Text textTmp;
	int tmp = round(musicMenu.getVolume());
	textTmp.setString("Volume: " + to_string(tmp));
	textTmp.setCharacterSize(80);
	textTmp.setFillColor(sf::Color::Black);
	textTmp.setFont(font);
	textTmp.setPosition(450, 230);
	window.draw(textTmp);
}

void Game::drawDirect() {
	sf::Text text;
	sf::Text tmp;
	float i, j;
	j = tmp.getGlobalBounds().width;
	tmp.setString("Arrow");
	tmp.setCharacterSize(50);
	tmp.setFillColor(sf::Color::Black);
	tmp.setFont(font);
	tmp.setCharacterSize(50);

	text.setString("Up");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setPosition(1085, 590);
	window.draw(text);

	text.setString("Down");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setPosition(863, 590);
	window.draw(text);

	text.setString("Left");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setPosition(670, 590);
	window.draw(text);

	text.setString("Right");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setPosition(460, 590);
	window.draw(text);

	text.setString(fromKtoS(u));
	i = text.getGlobalBounds().width;
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setCharacterSize(50);
	if (u == sf::Keyboard::W) {
		text.setPosition(1105 - i, 470);
		window.draw(text);
	}
	else {
		text.setPosition(1105 - i + 8, 450);
		window.draw(text);
		tmp.setPosition(1105 - j - 65, 490);
		window.draw(tmp);
	}

	text.setString(fromKtoS(d));
	i = text.getGlobalBounds().width;
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	if (d == sf::Keyboard::S) {
		text.setPosition(895 - i/2, 470);
		window.draw(text);
	}
	else {
		text.setPosition(895 - i/2 + 3, 450);
		window.draw(text);
		tmp.setPosition(895 - j/2 - 58, 490);
		window.draw(tmp);
	}

	text.setString(fromKtoS(l));
	i = text.getGlobalBounds().width;
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	if (l == sf::Keyboard::A) {
		text.setPosition(695 - i / 2, 470);
		window.draw(text);
	}
	else {
		text.setPosition(695 - i / 2 + 2, 450);
		window.draw(text);
		tmp.setPosition(695 - j / 2 - 58, 490);
		window.draw(tmp);
	}

	text.setString(fromKtoS(r));
	i = text.getGlobalBounds().width;
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	if (r == sf::Keyboard::D) {
		text.setPosition(495 - i / 2, 470);
		window.draw(text);
	}
	else {
		text.setPosition(495 - i / 2, 450);
		window.draw(text);
		tmp.setPosition(495 - j / 2 - 58, 490);
		window.draw(tmp);
	}
}
string Game::fromKtoS(const sf::Keyboard::Key& k) {
	string ret;
	switch (k) {

	case sf::Keyboard::A:

		ret = "A";
		break;
	case sf::Keyboard::B:

		ret = "B";
		break;
	case sf::Keyboard::C:

		ret = "C";
		break;
	case sf::Keyboard::D:

		ret = "D";
		break;
	case sf::Keyboard::E:

		ret = "E";
		break;
	case sf::Keyboard::F:

		ret = "F";
		break;
	case sf::Keyboard::G:

		ret = "G";
		break;
	case sf::Keyboard::H:

		ret = "H";
		break;
	case sf::Keyboard::I:

		ret = "I";
		break;
	case sf::Keyboard::J:

		ret = "J";
		break;
	case sf::Keyboard::K:

		ret = "K";
		break;
	case sf::Keyboard::L:

		ret = "L";
		break;
	case sf::Keyboard::M:

		ret = "M";
		break;
	case sf::Keyboard::N:

		ret = "N";
		break;
	case sf::Keyboard::O:

		ret = "O";
		break;
	case sf::Keyboard::P:

		ret = "P";
		break;
	case sf::Keyboard::Q:

		ret = "Q";
		break;
	case sf::Keyboard::R:

		ret = "R";
		break;
	case sf::Keyboard::S:

		ret = "S";
		break;
	case sf::Keyboard::T:

		ret = "T";
		break;
	case sf::Keyboard::U:

		ret = "U";
		break;
	case sf::Keyboard::V:

		ret = "V";
		break;
	case sf::Keyboard::W:

		ret = "W";
		break;
	case sf::Keyboard::X:

		ret = "X";
		break;
	case sf::Keyboard::Y:

		ret = "Y";
		break;
	case sf::Keyboard::Z:

		ret = "Z";
		break;
	case sf::Keyboard::Num0:

		ret = "Num0";
		break;
	case sf::Keyboard::Num1:

		ret = "Num1";
		break;
	case sf::Keyboard::Num2:

		ret = "Num2";
		break;
	case sf::Keyboard::Num3:

		ret = "Num3";
		break;
	case sf::Keyboard::Num4:

		ret = "Num4";
		break;
	case sf::Keyboard::Num5:

		ret = "Num5";
		break;
	case sf::Keyboard::Num6:

		ret = "Num6";
		break;
	case sf::Keyboard::Num7:

		ret = "Num7";
		break;
	case sf::Keyboard::Num8:

		ret = "Num8";
		break;
	case sf::Keyboard::Num9:

		ret = "Num9";
		break;
	case sf::Keyboard::Escape:

		ret = "Escape";
		break;
	case sf::Keyboard::LControl:

		ret = "LControl";
		break;
	case sf::Keyboard::LShift:

		ret = "LShift";
		break;
	case sf::Keyboard::LAlt:

		ret = "LAlt";
		break;
	case sf::Keyboard::LSystem:

		ret = "LSystem";
		break;
	case sf::Keyboard::RControl:

		ret = "RControl";
		break;
	case sf::Keyboard::RShift:

		ret = "RShift";
		break;
	case sf::Keyboard::RAlt:

		ret = "RAlt";
		break;
	case sf::Keyboard::RSystem:

		ret = "RSystem";
		break;
	case sf::Keyboard::Menu:

		ret = "Menu";
		break;
	case sf::Keyboard::LBracket:

		ret = "LBracket";
		break;
	case sf::Keyboard::RBracket:

		ret = "RBracket";
		break;
	case sf::Keyboard::SemiColon:

		ret = "SemiColon";
		break;
	case sf::Keyboard::Comma:

		ret = "Comma";
		break;
	case sf::Keyboard::Period:

		ret = "Period";
		break;
	case sf::Keyboard::Quote:

		ret = "Quote";
		break;
	case sf::Keyboard::Slash:

		ret = "Slash";
		break;
	case sf::Keyboard::BackSlash:

		ret = "BackSlash";
		break;
	case sf::Keyboard::Tilde:

		ret = "Tilde";
		break;
	case sf::Keyboard::Equal:

		ret = "Equal";
		break;
	case sf::Keyboard::Dash:

		ret = "Dash";
		break;
	case sf::Keyboard::Space:

		ret = "Space";
		break;
	case sf::Keyboard::Return:

		ret = "Return";
		break;
	case sf::Keyboard::BackSpace:

		ret = "BackSpace";
		break;
	case sf::Keyboard::Tab:

		ret = "Tab";
		break;
	case sf::Keyboard::PageUp:

		ret = "PageUp";
		break;
	case sf::Keyboard::PageDown:

		ret = "PageDown";
		break;
	case sf::Keyboard::End:

		ret = "End";
		break;
	case sf::Keyboard::Home:

		ret = "Home";
		break;
	case sf::Keyboard::Insert:

		ret = "Insert";
		break;
	case sf::Keyboard::Delete:

		ret = "Delete";
		break;
	case sf::Keyboard::Add:

		ret = "Add";
		break;
	case sf::Keyboard::Subtract:

		ret = "Subtract";
		break;
	case sf::Keyboard::Multiply:

		ret = "Multiply";
		break;
	case sf::Keyboard::Divide:

		ret = "Divide";
		break;
	case sf::Keyboard::Left:

		ret = "Left";
		break;
	case sf::Keyboard::Right:

		ret = "Right";
		break;
	case sf::Keyboard::Up:

		ret = "Up";
		break;
	case sf::Keyboard::Down:

		ret = "Down";
		break;
	case sf::Keyboard::Pause:

		ret = "Pause";
		break;
	default:
		ret = "Unknown";
		break;
	}
	return ret;
}