#include "LoadRandom.h"

int randomNum(int range)
{
    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<int> distribution(1, range);
    return distribution(generator);
}

void delayFunction() {
    // Simulate a function that takes one second to execute
    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() < 50) {
        // Do some non-blocking work here
    }
}

string pos[6] =
{
    "resource/tiles/grass1.png",
    "resource/tiles/grass2.png",
    "resource/tiles/grass3.png",
    "resource/tiles/grass4.png",
    "resource/tiles/train.png",
    "resource/tiles/road.png"
};

void loadGrass()
{
    sf::RenderWindow window(sf::VideoMode(1280, 640), "MyProgram");
    window.setFramerateLimit(60);
    auto start = std::chrono::high_resolution_clock::now();


    Sprite grass[11];
    Texture _grass[11];
    //string posGrass = "resource/tiles/grass";

    for (int i = 0; i < 11; i++)
    {
        _grass[i].loadFromFile(pos[randomNum(6) - 1]);
        grass[i].setTexture(_grass[i]);
        grass[i].setPosition(Vector2f(0, i * 64));
    }

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        for (int i = 0; i < 11; i++)
        {
            if (grass[i].getPosition().y >= 639) {
                _grass[i].loadFromFile(pos[randomNum(6) - 1]);
                grass[i].setPosition(Vector2f(0, -63));
            }
            else
                grass[i].setPosition(Vector2f(0, (grass[i].getPosition().y + 1)));

            window.draw(grass[i]);
        }

        window.display();

        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() < 500) {}
    }

}
