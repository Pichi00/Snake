#pragma warning(disable : 4996) 
//Biblioteki
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

//Klasy
#include "Player.h"
#include "Collectible.h"
#include "Button.h"
//using namespace sf;

/*Wymiary okna*/
const int WindowWidth = 720;
const int WindowHeight = 720;

/*Stany w których może być gra*/
enum STATES { MAIN_MENU = 1, GAMEPLAY, GAME_OVER, HOW_TO_PLAY, BEST_SCORES, PAUSE };
char GAME_STATE = STATES::MAIN_MENU;

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
}p[350];

int main(){
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Snake" , sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);

    Player player(WindowWidth/2, WindowHeight/2);
    Collectible coll;

    //FONT
    sf::Font font;
    font.loadFromFile("Fonts/dogica.ttf");

    /*MAIN MENU SETUP*/
    sf::Sprite MainMenu;
    sf::Texture MainMenuBackground;
    sf::Text authorText;

    Button startGameButton(187, 173);
    startGameButton.setTextTexture("Graphics/grajtxt.png");
    Button bestScoresButton(187, 253);
    bestScoresButton.setTextTexture("Graphics/bestscorestxt.png");
    Button howToButton(187, 333);
    howToButton.setTextTexture("Graphics/howtotxt.png");
    Button exitGameButton(187, 413);
    exitGameButton.setTextTexture("Graphics/wyjdztxt.png");

    authorText.setFont(font);
    authorText.setColor({ 86, 27, 174 });
    authorText.setCharacterSize(14);
    authorText.setOrigin({ 170,20 });
    authorText.setPosition({ WindowWidth - 220, WindowHeight - 5 });
    authorText.setString("Author: PK/WM");

    if (!MainMenuBackground.loadFromFile("Graphics/mainmenu.png")) {
        std::cout << "Error: Texture not found" << std::endl;
    }
    MainMenu.setTexture(MainMenuBackground);

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if ((event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) && dir != 1) dir = 0;
                else if ((event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) && dir != 0) dir = 1;
                else if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) && dir != 3) dir = 2;
                else if ((event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) && dir != 2) dir = 3;
            }
        }
        switch (GAME_STATE) {
        case MAIN_MENU:
            /*-----MAIN MENU-----*/

            if (startGameButton.isPressed(window)) {
                GAME_STATE = STATES::GAMEPLAY;
            }
            else if (bestScoresButton.isPressed(window)) {
                GAME_STATE = STATES::BEST_SCORES;
            }
            else if (howToButton.isPressed(window)) {
                GAME_STATE = STATES::HOW_TO_PLAY;
            }
            else if (exitGameButton.isPressed(window)) {
                window.close();
            }

            window.draw(MainMenu);
            window.draw(authorText);
            window.draw(startGameButton);
            window.draw(bestScoresButton);
            window.draw(howToButton);
            window.draw(exitGameButton);
            /*----/MAIN MENU-----*/
            break;

        case GAMEPLAY:
            /*-----GAMEPLAY-----*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                GAME_STATE = STATES::PAUSE;
            }

            for (int i = size; i > 0; i--) {
                p[i].x = p[i - 1].x;
                p[i].y = p[i - 1].y;
            }

            if (dir == 0) {
                if (p[0].y > 0) p[0].y -= step;
                else p[0].y += WindowHeight - step;
            }

            if (dir == 1) {
                if (p[0].y < WindowHeight - step) p[0].y += step;
                else p[0].y -= WindowHeight - step;
            }
            if (dir == 2) {
                if (p[0].x < WindowWidth - step) p[0].x += step;
                else p[0].x -= WindowWidth - step;
            }
            if (dir == 3) {
                if (p[0].x > 0) p[0].x -= step;
                else p[0].x += WindowWidth - step;
            }


            if (p[0].x == coll.getPosition().x && p[0].y == coll.getPosition().y) {
                size++;
                coll.randomPosition();
            }

            for (int i = 0; i < size; i++) {
                player.setPosition(p[i].x, p[i].y);
                window.draw(player);
            }
                window.draw(coll);

            /*-----/GAMEPLAY-----*/;
            break;
                  
        case GAME_OVER:
            /*-----GAME OVER-----*/
            
            /*-----/GAME OVER-----*/
            break;

        case BEST_SCORES:
            /*------BEST SCORES-----*/
           
            /*------/BEST SCORES-----*/
            break;

            /*------HOW TO PLAY-----*/
        case HOW_TO_PLAY:
            
            /*------/HOW TO PLAY-----*/
            break;

            /*------PAUSE-----*/
        case PAUSE:
            
            /*------/PAUSE-----*/
            break;
        }


      /* for (int i = size; i > 0; i--) {
            p[i].x = p[i - 1].x;
            p[i].y = p[i - 1].y;
        }

        if (dir == 0) {
            if (p[0].y > 0) p[0].y -= step;            
            else p[0].y += WindowHeight-step;                
        }
           
        if (dir == 1) {
            if (p[0].y < WindowHeight - step) p[0].y += step;
            else p[0].y -= WindowHeight - step ;
        } 
        if (dir == 2) {
            if (p[0].x < WindowWidth - step ) p[0].x += step;
            else p[0].x -= WindowWidth - step;
        }
        if (dir == 3) {
            if (p[0].x > 0) p[0].x -= step;
            else p[0].x += WindowWidth - step;
        }
            

        if (p[0].x == coll.getPosition().x && p[0].y == coll.getPosition().y) {
            size++;
            coll.randomPosition();
        }

        for (int i = 0; i < size; i++) {
            player.setPosition(p[i].x, p[i].y);
            window.draw(player);
        }*/
        //window.draw(coll);
      
        window.display(); 
        Sleep(speed);
    }
    return 0;
}