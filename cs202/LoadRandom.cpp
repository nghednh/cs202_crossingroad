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

const int numTitle = 6;

string pos[numTitle] =
{
    "resource/tiles/grass.jpg",
    "resource/tiles/road.png",
    "resource/tiles/grassFlower.jpg",
    "resource/tiles/train.png",
    "resource/tiles/road.png",
    "resource/tiles/grassFlower.jpg"
};

struct Node
{
    Texture t;
    Node* next;
};

vector <Node*> arrObj;

Texture _grass[6];

void setTexture()
{
    for (int i = 0; i < 6; i++)
        _grass[i].loadFromFile(pos[i]);

    for (int i = 0; i < 11; i++)
    {
        Node* tmp = nullptr;
        arrObj.push_back(tmp);
    }
}

void loadGrass()
{
    setTexture();
    sf::RenderWindow window(sf::VideoMode(1280, 640), "MyProgram");
    window.setFramerateLimit(60);
    auto start = std::chrono::high_resolution_clock::now();


    Sprite grass[11];

    //string posGrass = "resource/tiles/grass";

    for (int i = 0; i < 11; i++)
    {
        grass[i].setTexture(_grass[randomNum(numTitle) - 1]);
        grass[i].setPosition(Vector2f(0, i * 64));
    }

    Texture obj;
    Sprite rock;
    obj.loadFromFile("resource/object.png");
    rock.setTexture(obj);
    rock.setTextureRect(sf::IntRect(18, 48, 12, 12));
    rock.scale(5, 5);
    rock.setPosition(0, 0);

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
                grass[i].setTexture(_grass[randomNum(numTitle) - 1]);
                grass[i].setPosition(Vector2f(0, -63));
            }
            else
            {
                grass[i].setPosition(Vector2f(0, (grass[i].getPosition().y + 1)));
            }
          
            window.draw(grass[i]);
        }

        if (rock.getPosition().y >= 639) {
            rock.setPosition(Vector2f(randomNum(1280 - 64), -63));
        }
        else
        {
            rock.setPosition(Vector2f(rock.getPosition().x, rock.getPosition().y + 1));
        }
        window.draw(rock);




        window.display();

        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() < 500) {}
    }

}
