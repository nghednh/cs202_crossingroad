#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <unordered_map>
using namespace std;
using namespace sf;


class Bullet {
private:
    Sprite sprite;
public:
    Bullet(Texture& texture) : sprite(texture) {}

    void draw(RenderWindow& window)
    {
        window.draw(sprite);
    }

    void move(double offsetX, double offsetY)
    {
        sprite.move(offsetX, offsetY);
    }
};

class BulletFactory {
public:
    unordered_map<string, Texture> textures;
    vector <string> type = { "RED", "BLACK", "GRAY", "PURPLE"};

    BulletFactory()
    {
        textures["RED"].loadFromFile("resource/backButton0.png");
        textures["BLACK"].loadFromFile("resource/backButton1.png");
        textures["GRAY"].loadFromFile("resource/bullet.png");
        textures["GRAY"].loadFromFile("resource/object.png");
    }

    Bullet createBullet()
    {
        return Bullet(textures[type[rand() % 4]]);
    }
};

class Game {
private:
    vector <Bullet> bullets;
    RenderWindow window;
    BulletFactory bulletFactory;
public:
    Game() : bulletFactory()
    {
        RenderWindow window(sf::VideoMode(800, 600), "Flyweight Pattern Example");

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) window.close();
                else if (event.type == Event::MouseButtonPressed) {
                    auto bullet = bulletFactory.createBullet();
                    bullets.push_back(bullet);
                }
            }

            for (auto& bullet : bullets) {
                bullet.move(1, 1);
            }

            window.clear();
            for (auto& bullet : bullets) {
                bullet.draw(window);
            }
            window.display();
        }
    }
};

int main()
{
    Game a;
}
