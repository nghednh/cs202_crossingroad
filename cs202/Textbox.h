#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_h

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define SPACEBAR_KEY 32

class Textbox {
public:
	Textbox(int size, sf::Color textColor, sf::Color boxColor, bool sel);

	// Make sure font is passed by reference:
	void setFont(const sf::Font& fonts);

	void setPosition(const sf::Vector2f &point);

	void setPosition(float xIn, float yIn);

	// Set char limits:
	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	// Set character size
	void setCharacterSize(unsigned int size);

	// Change selected state:
	void setSelected(bool sel);

	std::string getText();

	void drawTo(sf::RenderWindow& window);

	// Function for event loop:
	void typedOn(sf::Event input);

	void setBoxPosition(const sf::Vector2f& pos);
	void setBoxPosition(float xIn, float yIn);
	void setBoxSize(const sf::Vector2f& pos);
	void setOutlineThickness(float thickness);
	void setOutlineColor(const sf::Color& color);
	void setStyle(sf::Uint32 style);
	void setTextColor(const sf::Color& color);
	void setText(const sf::String& theText);

	const sf::Vector2f& getBoxPosition() const;
	const sf::Vector2f& getTextPosition() const;

	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getBoxGlobalBounds() const;
	
	const sf::Vector2f& getBoxSize() const;

	bool isMouseOver(sf::RenderWindow& window);
	bool isSelect();
	void wrapText(sf::Text& theText);
	void clear();
private:
	sf::Text textbox;
	sf::RectangleShape theBox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

private:
	// Delete the last character of the text:
	void deleteLastChar();

	// Get user input:
	void inputLogic(int charTyped);
};

#endif