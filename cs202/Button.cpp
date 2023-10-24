
#include "Button.h"

Button::Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
    button.setSize(buttonSize);
    button.setFillColor(bgColor);

    // Get these for later use:
    btnWidth = buttonSize.x;
    btnHeight = buttonSize.y;
    text.setString(btnText);
    text.setCharacterSize(charSize);
    text.setFillColor(textColor);
}

// Pass font by reference:
void Button::setFont(const sf::Font& font) {
    text.setFont(font);
}

void Button::setBackColor(const sf::Color &color) {
    button.setFillColor(color);
}

void Button::setTextColor(const sf::Color &color) {
    text.setFillColor(color);
}

void Button::setPosition(const sf::Vector2f &point) {
    button.setPosition(point);

    // Center text on button:
    float xPos = (point.x + btnWidth / 2.0) - (text.getLocalBounds().width / 2);
    float yPos = (point.y + btnHeight / 2.5) - (text.getLocalBounds().height / 2);
    text.setPosition(xPos, yPos);
}

void Button::setPosition(float x, float y)
{
    button.setPosition(x, y);
    float xPos = (x + btnWidth / 2.0) - (text.getLocalBounds().width / 2);
    float yPos = (y + btnHeight / 2.5) - (text.getLocalBounds().height / 2);
    text.setPosition(xPos, yPos);
}

void Button::setOutlineThickness(float thickness)
{
    button.setOutlineThickness(thickness);
}

void Button::setOutlineColor(const sf::Color &color)
{
    button.setOutlineColor(color);
}

void Button::setTexture(const sf::Texture *texture)
{
    button.setTexture(texture);
}

const sf::Vector2f& Button::getSize()
{
    return button.getSize();
}

void Button::drawTo(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::isMouseOver(sf::RenderWindow& window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    int btnPosX = button.getPosition().x;
    int btnPosY = button.getPosition().y;

    int btnxPosWidth = button.getPosition().x + btnWidth;
    int btnyPosHeight = button.getPosition().y + btnHeight;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

void Button::update(sf::RenderWindow& window)
{
    sf::Color grey(0, 0, 0, 120);
    if (isMouseOver(window)) {
		button.setOutlineColor(grey);
	}
    else {
		button.setOutlineColor(sf::Color::Transparent);
	}
}

void Button::setString(std::string text)
{
    this->text.setString(text);
}

void Button::setStyle(sf::Uint32 style)
{
    text.setStyle(style);
}

void Button::adjustSizeToContainText()
{
    button.setSize(sf::Vector2f(text.getGlobalBounds().width + 30, text.getGlobalBounds().height + 10));
    btnWidth = button.getSize().x;
    btnHeight = button.getSize().y;
    
}
