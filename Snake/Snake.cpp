//Biblioteki
#include <SFML/Graphics.hpp>

//Klasy
#include "Player.h"

//using namespace sf;

/*Wymiary okna*/
const int WindowWidth = 700;
const int WindowHeight = 700;

int main(){
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Snake" };
    window.setFramerateLimit(60);

    Player player(WindowWidth/2, WindowHeight/2);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(player);

        window.display(); 
    }
    return 0;
}