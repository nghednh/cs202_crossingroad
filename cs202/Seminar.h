#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;


class Bullet;
class Player;

class BulletTexture {
public:
    static BulletTexture& Instance() {
        static BulletTexture instance; 
        return instance;
    }
    Texture& getBulletTexture() {
        return bulletTexture;
    }
private:
    Texture bulletTexture;

    BulletTexture() {
        bulletTexture.loadFromFile("resource/bullet.png");
    }
    ~BulletTexture() = default;
    BulletTexture(const BulletTexture&) = delete;
    BulletTexture& operator=(const BulletTexture&) = delete;
};

class Bullet {
private:
    double x, y;
    double directionX, directionY;
    double speed;
    Sprite texture;
public:
    Bullet(Player& src, double desX, double desY, double speed);
    bool update();
    Sprite& getTexture();
};

class Player {
private:
    int x;
    int y;
	vector <Bullet> bullets;
public:
	void addParticle(double desX, double desY, double speed);
	void render(RenderWindow&);
    friend Bullet::Bullet(Player& src, double desX, double desY, double speed);
};

class Game {
private:
	vector <Player> player;
    RenderWindow window;
public:
    Game();
	void render();
};

