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


class MovingParticle;
class Particle;
class Player;
class Game;

class SetTexture {
private:
    static Texture* texture;

    SetTexture() {
        texture = new Texture[2];
        texture[0].loadFromFile("resource/bullet.png");
        texture[1].loadFromFile("resource/gun.png");
    }

    ~SetTexture() = default;
    SetTexture(const SetTexture&) = delete;
    SetTexture& operator=(const SetTexture&) = delete;

public:
    static Texture& getTexture(int i) {
        if (!texture) SetTexture();
        return texture[i];
    }
};

class Particle {
private:
    Sprite sprite;
public:
    Particle(double x, double y, int textNum);
    void update(double x, double y);
    Vector2f getPos();
    Sprite& getSprite();
};

class MovingParticle : public Particle {
private:
    double directionX, directionY;
    double speed;
public:
    MovingParticle(int x, int y, double desX, double desY, double speed);
    bool update();
    Sprite& getSprite();
};

class Game {
private:
    vector <Particle> particles;
    vector <MovingParticle> mps;
    RenderWindow window;
public:
    Game();
    void render();
    void updateAndDraw();
    void addMovingParticle(Unit& src, Unit& des, double speed);
    void addParticle(double x, double y);
};

class Unit : public Game {
private:
    int x;
    int y;
public:
    Unit(int x, int y);
    void fireAt(Unit& target);
    void placeGun();
    friend void Game::addMovingParticle(Unit& src, Unit& des, double speed);
};
