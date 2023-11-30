/*#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;

// A common interface for all players
class Player
{
public:
    virtual void assignWeapon(const std::string& weapon) = 0;
    virtual void mission() = 0;
};

// Terrorist must have weapon and mission
class Terrorist : public Player
{
private:
    const std::string TASK;
    std::string weapon;

public:
    Terrorist() : TASK("PLANT A BOMB") {}

    void assignWeapon(const std::string& weapon) override
    {
        this->weapon = weapon;
    }

    void mission() override
    {
        std::cout << "Terrorist with weapon " << weapon << "| Task is " << TASK << std::endl;
    }
};

// CounterTerrorist must have weapon and mission
class CounterTerrorist : public Player
{
private:
    const std::string TASK;
    std::string weapon;

public:
    CounterTerrorist() : TASK("DIFFUSE BOMB") {}

    void assignWeapon(const std::string& weapon) override
    {
        this->weapon = weapon;
    }

    void mission() override
    {
        std::cout << "Counter Terrorist with weapon " << weapon << "| Task is " << TASK << std::endl;
    }
};

// Class used to get a player using unordered_map (Returns
// an existing player if a player of given type exists.
// Else creates a new player and returns it.
class PlayerFactory
{
public:
    static std::unordered_map<std::string, Player*> players;

public:
    // Method to get a player
    static Player* getPlayer(const std::string& type)
    {
        Player* p = nullptr;

        // If an object for the type has already been created, simply return its reference
        if (players.find(type) != players.end())
            p = players[type];
        else
        {
            // Create an object of the corresponding type
            if (type == "Terrorist")
            {
                std::cout << "Terrorist Created" << std::endl;
                cout << "Created here !!!!" << endl;
                p = new Terrorist();
            }
            else if (type == "CounterTerrorist")
            {
                std::cout << "Counter Terrorist Created" << std::endl;
                cout << "Created here !!!!!" << endl;
                p = new CounterTerrorist();
            }
            else
            {
                std::cout << "Unreachable code!" << std::endl;
            }

            // Once created, insert it into the unordered_map
            players[type] = p;
        }
        return p;
    }
};

// Initialize static member of PlayerFactory
std::unordered_map<std::string, Player *> PlayerFactory::players;

// Driver class
int main()
{
    // All player types and weapons
    std::vector<std::string> playerTypes = { "Terrorist", "CounterTerrorist" };
    std::vector<std::string> weapons = { "AK-47", "Maverick", "Gut Knife", "Desert Eagle" };

    // Seed for random number generation
    std::srand(std::time(0));

    // Assume that we have a total of 10 players in the game
    for (int i = 0; i < 10; i++)
    {
        // Get a random player type
        std::string randomPlayerType = playerTypes[std::rand() % playerTypes.size()];
        std::cout << randomPlayerType << std::endl;

        // Get a random weapon
        std::string randomWeapon = weapons[std::rand() % weapons.size()];
        std::cout << randomWeapon << std::endl;

        // Get a player using the PlayerFactory
        Player* p = PlayerFactory::getPlayer(randomPlayerType);

        // Assign a random weapon to the player
        p->assignWeapon(randomWeapon);

        // Send this player on a mission
        p->mission();
        std::cout << std::endl << std::endl;
    }

    // Clean up: delete players created by PlayerFactory
    for (auto& entry : PlayerFactory::players)
    {
        delete entry.second;
    }

    return 0;
}
*/
/*
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>

// Bullet class
class Bullet {
public:
    Bullet(sf::Texture& texture) : sprite(texture) {}

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
};

// BulletFactory class
class BulletFactory {
public:
    BulletFactory() {
        texture.loadFromFile("resource/backButton0.png");
    }

    std::shared_ptr<Bullet> createBullet() {
        return std::make_shared<Bullet>(texture);
    }

private:
    sf::Texture texture;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flyweight Pattern Example");

    BulletFactory bulletFactory;
    std::vector<std::shared_ptr<Bullet>> bullets;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << "Press" << std::endl;
                auto bullet = bulletFactory.createBullet();
                bullets.push_back(bullet);
            }
        }

        for (auto& bullet : bullets) {
            bullet->move(5, 5);
        }

        window.clear();
        for (auto& bullet : bullets) {
            bullet->draw(window);
        }
        window.display();
    }

    return 0;
}
*/
/*

    static Texture* getBulletTexture(const std::string& type)
    {
        Texture* tmp = nullptr;

        if (textures.find(type) != textures.end())
            tmp = textures[type];
        else
        {
            if (type == "Red")
            {
                cout << "Red bullet Created" << endl;
                tmp = new Texture;
                tmp->loadFromFile("resource/redBullet.png");
            }
            else if (type == "Black")
            {
                cout << "Blue bullet Created" << endl;
                tmp = new Texture;
                tmp->loadFromFile("resource/blueBullet.png");
            }
            else if (type == "Gray")
            {
                cout << "Gray bullet Created" << endl;
                tmp = new Texture;
                tmp->loadFromFile("resource/grayBullet.png");
            }
            textures[type] = tmp;
        }
        return tmp;
    }
    
    */

#include "Seminar.h"

int main()
{
    Game a;
}