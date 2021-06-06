﻿#pragma warning(disable : 4996) 
//Biblioteki
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h> 

//Klasy
#include "Player.h"
#include "Collectible.h"
#include "Button.h"

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
bool can_change_dir = true;
int size{ 1 };
unsigned int score{ 0 };


int speed = 120;
const int step = 40;

struct Point{
    int x = 0;
    int y = 80;
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

    /*GAMEPLAY SETUP*/
    sf::Sprite gameplayBackground;
    sf::Texture gameplayBackgroundTexture;
    if (!gameplayBackgroundTexture.loadFromFile("Graphics/background.png")) {
        std::cout << "Error: Texture not found" << std::endl;
    }
    gameplayBackground.setTexture(gameplayBackgroundTexture);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setColor({ 86, 27, 174 });
    scoreText.setCharacterSize(18);
    scoreText.setOrigin({ 0,0 });
    scoreText.setPosition({ 20, 20 });
    scoreText.setString("Score: "+std::to_string(score));

    /*GAME OVER SETUP*/
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setColor({ 86, 27, 174 });
    gameOverText.setCharacterSize(48);
    gameOverText.setOrigin({ 170,20 });
    gameOverText.setPosition({ WindowWidth/2, WindowHeight/8 });
    gameOverText.setString("GAME OVER");

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed && can_change_dir) {
                if ((event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) && dir != 1) {
                    dir = 0;
                    can_change_dir = false;
                }
                else if ((event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) && dir != 0) {
                    dir = 1;
                    can_change_dir = false;
                }
                else if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) && dir != 3) {
                    dir = 2;
                    can_change_dir = false;
                }
                else if ((event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) && dir != 2) {
                    dir = 3;
                    can_change_dir = false;
                }
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
            window.display();
            /*----/MAIN MENU-----*/
            break;

        case GAMEPLAY:
            /*-----GAMEPLAY-----*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                GAME_STATE = STATES::PAUSE;
            }

            if (size > 1) {
                for (int i = 1; i < size; i++) {
                    if (p[0].x == p[i].x && p[0].y == p[i].y) {
                        window.clear();
                        GAME_STATE = STATES::GAME_OVER;
                    }
                }
            }
           

            for (int i = size; i > 0; i--) {
                p[i].x = p[i - 1].x;
                p[i].y = p[i - 1].y;
            }

            if (dir == 0) {
                if (p[0].y > 80) p[0].y -= step;
                else p[0].y += WindowHeight - (step+80);
            }

            if (dir == 1) {
                if (p[0].y < WindowHeight - step) p[0].y += step;
                else p[0].y -= WindowHeight - (step+80);
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
                score += 10;
                scoreText.setString("Score: " + std::to_string(score));
                
                coll.randomPosition();
            }

            for (int i = 0; i < size; i++) {
                if (i == 0) player.setColor(sf::Color::Green);
                else player.setColor(sf::Color::White);
                player.setPosition(p[i].x, p[i].y);
                window.draw(player);
            }
                window.draw(gameplayBackground);
                window.draw(coll);
                window.draw(scoreText);
                can_change_dir = true;
                window.display();
                Sleep(speed);
            /*-----/GAMEPLAY-----*/;
            break;
                  
        case GAME_OVER:
            /*-----GAME OVER-----*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                GAME_STATE = STATES::GAMEPLAY;
            }
            for (int i = 0; i < size; i++) {
                if (i == 0) player.setColor(sf::Color::Green);
                else player.setColor(sf::Color::White);
                player.setPosition(p[i].x, p[i].y);
                window.draw(player);
            }
            window.draw(gameOverText);
            window.display();
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                GAME_STATE = STATES::GAMEPLAY;
            }
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
      
        
        //can_change_dir = true;
    }
    return 0;
}