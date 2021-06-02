//Biblioteki
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

//Klasy
#include "Player.h"

//using namespace sf;

/*Wymiary okna*/
const int WindowWidth = 720;
const int WindowHeight = 720;

//Okreslenie kierunku
/*
    0 - gora
    1 - dol
    2 - prawo
    3 - lewo
*/
char dir{ 2 }; 
int size{ 1 };


int speed = 120;
const int step = 40;

struct Point{
    int x = 0;
    int y = 0;
}p[100];

int main(){
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Snake" };
    window.setFramerateLimit(60);

    Player player(WindowWidth/2, WindowHeight/2);

    while (window.isOpen()){
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W && dir != 1) dir = 0;
                else if (event.key.code == sf::Keyboard::S && dir != 0) dir = 1;
                else if (event.key.code == sf::Keyboard::D && dir != 3) dir = 2;
                else if (event.key.code == sf::Keyboard::A && dir != 2) dir = 3;
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
      
        window.display(); 
        Sleep(speed);
    }
    return 0;
}