#include "Textbox.h"

Textbox::Textbox(int size, sf::Color textColor, sf::Color boxColor, bool sel) {
    textbox.setCharacterSize(size);
    textbox.setFillColor(textColor);
    theBox.setFillColor(boxColor);
    theBox.setSize({100, 100});
    theBox.setPosition({100, 100});
    isSelected = sel;

    // Check if the textbox is selected upon creation and display it accordingly:
    if (isSelected)
        textbox.setString(textbox.getString() + "_");
    else
        textbox.setString("");
}

// Make sure font is passed by reference:
void Textbox::setFont(const sf::Font& fonts) {
    textbox.setFont(fonts);
}

void Textbox::setPosition(const sf::Vector2f &point) {
    textbox.setPosition(point);
}

void Textbox::setPosition(float xIn, float yIn)
{
    textbox.setPosition(xIn, yIn);
}

// Set char limits:
void Textbox::setLimit(bool ToF) {
    hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim) {
    hasLimit = ToF;
    limit = lim - 1;
}

// Set character size
void Textbox::setCharacterSize(unsigned int size) {
    textbox.setCharacterSize(size);
}

// Change selected state:
void Textbox::setSelected(bool sel) {
    isSelected = sel;

    // If not selected, remove the '_' at the end:
    if (!sel) {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length(); i++) {
            newT += t[i];
        }
        textbox.setString(newT);    
    }
    else {
        textbox.setString(text.str() + "_");
    }
}

std::string Textbox::getText() {
    return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window) {
    window.draw(textbox);
    window.draw(theBox);
}

// Function for event loop:
void Textbox::typedOn(sf::Event input) {
    if (isSelected) {
        int charTyped = input.text.unicode;

        // Only allow normal inputs:
        if (charTyped < 128) {
            if (hasLimit) {
                // If there's a limit, don't go over it:
                if (text.str().length() <= limit) {
                    inputLogic(charTyped);
                }
                // But allow for char deletions:
                else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                    deleteLastChar();
                }
            }
            // If no limit exists, just run the function:
            else {
                inputLogic(charTyped);
            }
        }
    }
}

void Textbox::setBoxPosition(const sf::Vector2f &pos)
{
    theBox.setPosition(pos);
}

void Textbox::setBoxPosition(float xIn, float yIn)
{
    theBox.setPosition(xIn, yIn);
}

void Textbox::setBoxSize(const sf::Vector2f &pos)
{
    theBox.setSize(pos);
}

void Textbox::setOutlineThickness(float thickness)
{
    theBox.setOutlineThickness(thickness);
}

void Textbox::setOutlineColor(const sf::Color &color)
{
    theBox.setOutlineColor(color);
}

void Textbox::setStyle(sf::Uint32 style)
{
    textbox.setStyle(style);
}

void Textbox::setTextColor(const sf::Color &color)
{
    textbox.setFillColor(color);
}

void Textbox::setText(const sf::String& theText)
{
    textbox.setString(theText);
    text.str("");
    std::string textStream = theText;
    text << textStream;
}

const sf::Vector2f &Textbox::getBoxPosition() const
{
    return theBox.getPosition();
}

const sf::Vector2f &Textbox::getTextPosition() const
{
    return textbox.getPosition();
}

sf::FloatRect Textbox::getGlobalBounds() const
{
    return textbox.getGlobalBounds();
}

sf::FloatRect Textbox::getBoxGlobalBounds() const
{
    return theBox.getGlobalBounds();
}

const sf::Vector2f &Textbox::getBoxSize() const
{
    return theBox.getSize();
}

bool Textbox::isMouseOver(sf::RenderWindow &window)
{
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    int btnPosX = theBox.getPosition().x;
    int btnPosY = theBox.getPosition().y;

    int btnxPosWidth = theBox.getPosition().x + theBox.getSize().x;
    int btnyPosHeight = theBox.getPosition().y + theBox.getSize().y;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

bool Textbox::isSelect()
{
    return isSelected;
}

void Textbox::wrapText(sf::Text &theText)
{
    std::string str = theText.getString();
    std::string wrappedStr;

    std::istringstream iss(str);
    std::string word;
    std::string line;

    // Clear theText before wrapping
    theText.setString("");

    while (std::getline(iss, word, '\n')) {
        // Process each line separately
        if (!line.empty()) {
            // Add the previous line to the wrapped text and start a new line
            wrappedStr += line + '\n';
            line.clear();
        }
        std::istringstream lineIss(word);
        while (lineIss >> word) {
            // Set theText with the current line + the next word
            theText.setString(line + (line.empty() ? "" : " ") + word);
            if (theText.getLocalBounds().width > theBox.getLocalBounds().width) {
                // Add the current line to the wrapped text and start a new line
                wrappedStr += line + '\n';
                line = word;
            } else {
                // Continue adding words to the current line
                line += (line.empty() ? "" : " ") + word;
            }
        }
    }

    // Add the last line to the wrapped text
    wrappedStr += line;

    // Set theText with the wrapped text
    theText.setString(wrappedStr);
}

void Textbox::clear()
{
    text.str("");
    textbox.setString("");
}

void Textbox::deleteLastChar() {
    std::string t = text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    text.str("");
    text << newT;
    textbox.setString(text.str() + "_");
}

// Get user input:
void Textbox::inputLogic(int charTyped) {
    // If the key pressed isn't delete, or the two selection keys, then append the text with the char:
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped!= SPACEBAR_KEY) {
        text << static_cast<char>(charTyped);
    }
    // If the key is delete, then delete the char:
    else if (charTyped == DELETE_KEY) {
        if (text.str().length() > 0) {
            deleteLastChar();
        }
    }
    // Set the textbox text:
    textbox.setString(text.str() + "_");
    wrapText(textbox);
    std::string currentText = textbox.getString();
    if(currentText[currentText.length()-1] == '_')
        currentText.pop_back();
    text.str("");
    text << currentText;
}