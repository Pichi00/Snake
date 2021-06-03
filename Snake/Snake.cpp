//Biblioteki
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

//Klasy
#include "Player.h"
#include "Collectible.h"

//using namespace sf;

/*Wymiary okna*/
const int WindowWidth = 720;
const int WindowHeight = 720;

float randX{ 0 }, randY{ 0 };

//Okreslenie kierunku
/*
    0 - gora
    1 - dol
    2 - prawo
    3 - lewo
*/
char dir{ 2 }; 
int size{ 1 };


int speed = 140;
const int step = 40;

struct Point{
    int x = 0;
    int y = 0;
}p[100];

int main(){
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Snake" , sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);

    Player player(WindowWidth/2, WindowHeight/2);
    Collectible coll;

    srand(time(NULL));

    randX = 40.f * float(rand() % 18);
    randY = 40.f * float(rand() % 18);
    std::cout << randX << std::endl << randY << std::endl;
    coll.setPosition(randX, randY);

    while (window.isOpen()){
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up && dir != 1) dir = 0;
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down && dir != 0) dir = 1;
                else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right && dir != 3) dir = 2;
                else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left && dir != 2) dir = 3;
            }
        }

        if (dir == 0) p[0].y -= step;
        else if (dir == 1) p[0].y += step;
        else if (dir == 2) p[0].x += step;
        else if (dir == 3) p[0].x -= step;
        for (int i = 0; i < size; i++) {
            player.setPosition(p[i].x, p[i].y);
            window.draw(player);
        }
        window.draw(coll);
      
        window.display(); 
        Sleep(speed);
    }
    return 0;
}