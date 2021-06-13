#pragma warning(disable : 4996) 
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
enum STATES { MAIN_MENU = 1, GAMEPLAY, GAME_OVER, OPTIONS, HOW_TO_PLAY, BEST_SCORES, PAUSE };
char GAME_STATE = STATES::GAME_OVER;

//Okreslenie kierunku
/*
    0 - gora
    1 - prawo
    2 - dol
    3 - lewo
*/
char dir{ 1 }; 
char last_segment_dir{ 1 };
bool can_change_dir = true;
int size{ 2 };
unsigned int score{ 0 };


int speed = 120;
const int step = 40;

sf::Text scoreText;

struct Point{
    int x = 20;
    int y = 100;
    int dir{ 1 };
}p[350];

void new_game(Player& player, Collectible& coll);


int main(){
    /*GENERAL SETUP*/
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Snake" , sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);

    Player player(WindowWidth / 2, WindowHeight / 2);
    Collectible coll;

    Button backToMenuButton(WindowWidth - 180, WindowHeight - 50);
    backToMenuButton.setTextTexture("Graphics/backtomenutxt.png");

    Button restartGameButton(180, WindowHeight - 50);
    restartGameButton.setTextTexture("Graphics/resumetxt.png");

    //FONT
    sf::Font font;
    font.loadFromFile("Fonts/dogica.ttf");

    /*MAIN MENU SETUP*/
    sf::Sprite MainMenu;
    sf::Texture MainMenuBackground;
    sf::Text authorText;

    Button startGameButton(WindowWidth/2, 273);
    startGameButton.setTextTexture("Graphics/grajtxt.png");
    Button optionsButton(WindowWidth / 2, 353);
    optionsButton.setTextTexture("Graphics/optionstxt.png");
    Button bestScoresButton(WindowWidth / 2, 433);
    bestScoresButton.setTextTexture("Graphics/bestscorestxt.png");
    Button howToButton(WindowWidth / 2, 513);
    howToButton.setTextTexture("Graphics/howtotxt.png");
    Button exitGameButton(WindowWidth / 2, 593);
    exitGameButton.setTextTexture("Graphics/wyjdztxt.png");

    authorText.setFont(font);
    authorText.setColor(sf::Color::White);
    authorText.setCharacterSize(14);
    //authorText.setOrigin({ 170,20 });
    authorText.setPosition({ 10, WindowHeight - 25 });
    authorText.setString("Authors: Piotr Kolodziejski & Wiktor Machon");

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

    
    scoreText.setFont(font);
   // scoreText.setColor({ 86, 27, 174 });
    scoreText.setColor(sf::Color::White);
    scoreText.setCharacterSize(18);
    scoreText.setOrigin({ 0,0 });
    scoreText.setPosition({ 20, 20 });
    scoreText.setString("Score: "+std::to_string(score));

    /*GAME OVER SETUP*/
    sf::Text gameOverText;
    gameOverText.setFont(font);
    //gameOverText.setColor({ 86, 27, 174 });
    gameOverText.setColor(sf::Color::White);
    gameOverText.setCharacterSize(48);
    gameOverText.setOrigin({ 0,0 });
    gameOverText.setPosition({ WindowWidth/5, WindowHeight/2 });
    gameOverText.setString("GAME OVER");


    /*OPTIONS SETUP*/
    sf::Sprite optionsBackground;
    sf::Texture optionsBackgroundTexture;
    if (!optionsBackgroundTexture.loadFromFile("Graphics/options.png")) {
        std::cout << "Error: Texture not found" << std::endl;
    }
    optionsBackground.setTexture(optionsBackgroundTexture);

    /*BEST SCORES SETUP*/
    sf::Sprite bestScoresBackground;
    sf::Texture bestScoresBackgroundTexture;
    if (!bestScoresBackgroundTexture.loadFromFile("Graphics/bestscores.png")) {
        std::cout << "Error: Texture not found" << std::endl;
    }
    bestScoresBackground.setTexture(bestScoresBackgroundTexture);

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed && can_change_dir) {
                if ((event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) && dir != 2) {
                    dir = 0;
                    can_change_dir = false;
                }
                else if ((event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) && dir != 0) {
                    dir = 2;
                    can_change_dir = false;
                }
                else if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) && dir != 3) {
                    dir = 1;
                    can_change_dir = false;
                }
                else if ((event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) && dir != 1) {
                    dir = 3;
                    can_change_dir = false;
                }
            }
        }
        switch (GAME_STATE) {
        case MAIN_MENU:
            /*-----MAIN MENU-----*/

            if (startGameButton.isPressed(window)) {
                new_game(player, coll);
                GAME_STATE = STATES::GAMEPLAY;
            }
            else if (optionsButton.isPressed(window)) {
                GAME_STATE = STATES::OPTIONS;
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
            window.draw(optionsButton);
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


            for (int i = size; i > 0; i--) {
                p[i].x = p[i - 1].x;
                p[i].y = p[i - 1].y;   
                p[i].dir = p[i-1].dir;
                //std::cout << pd[i].dir << std::endl;
            }
           /* std::cout << "---" << std::endl;
            Sleep(200);*/

            

            if (dir == 0) {
                if (p[0].y > 100) p[0].y -= step;
                else p[0].y += WindowHeight - (step+80);
            }

            if (dir == 2) {
                if (p[0].y < WindowHeight - step) p[0].y += step;
                else p[0].y -= WindowHeight - (step+80);
            }
            if (dir == 1) {
                if (p[0].x < WindowWidth - step) p[0].x += step;
                else p[0].x -= WindowWidth - step;
            }
            if (dir == 3) {
                if (p[0].x > 20) p[0].x -= step;
                else p[0].x += WindowWidth - step;
            }

            p[0].dir = dir;
            
            /* if (p[size - 1].x < p[size - 2].x) last_segment_dir = 1;
             else if (p[size - 1].x > p[size - 2].x) last_segment_dir = 3;
             else if (p[size - 1].y > p[size - 2].y) last_segment_dir = 0;
             else last_segment_dir = 2;*/
            
            

            if (p[0].x == coll.getPosition().x && p[0].y == coll.getPosition().y) {
                size++;
                score += 10;
                scoreText.setString("Score: " + std::to_string(score));
                
                coll.randomPosition();
            }


                window.draw(gameplayBackground);
            for (int i = size - 1; i >= 0; i--) {
                /*if (i == size - 1) player.setTexture(i, last_segment_dir, size - 1);
                else player.setTexture(i, dir, size-1);*/
                player.setTexture(i, p[i].dir, size - 1);
                player.setPosition(p[i].x, p[i].y);
                window.draw(player);
            }                
                window.draw(coll);
                window.draw(scoreText);
                can_change_dir = true;
                window.display();
                Sleep(speed);

                /*Warunek sprawdzający czy głowa węża nie napotkała jakiegoś jego segmentu*/
                if (size > 1) {
                    for (int i = 1; i < size; i++) {
                        if (p[0].x == p[i].x && p[0].y == p[i].y) {
                            window.clear();
                            GAME_STATE = STATES::GAME_OVER;
                        }
                    }
                }
            /*-----/GAMEPLAY-----*/;
            break;
                  
        case GAME_OVER:
            /*-----GAME OVER-----*/
            if (restartGameButton.isPressed(window)) {
                new_game(player, coll);
            }
            if (backToMenuButton.isPressed(window)) {
                GAME_STATE = STATES::MAIN_MENU;
            }

            window.draw(gameplayBackground);
            window.draw(restartGameButton);
            window.draw(backToMenuButton);
            for (int i = size-1; i >=0; i--) {
                /*if(i==size-1) player.setTexture(i, last_segment_dir, size - 1);
                else player.setTexture(i, dir,size-1);*/
                player.setTexture(i, p[i].dir, size - 1);               
                player.setPosition(p[i].x, p[i].y);
                window.draw(player);
            }
            window.draw(gameOverText);
            window.draw(scoreText);
            window.display();
            /*-----/GAME OVER-----*/
            break;
            /*-----OPTIONS--------*/
        case OPTIONS:
            if (backToMenuButton.isPressed(window)) {
                GAME_STATE = STATES::MAIN_MENU;
            }
            window.draw(optionsBackground);
            window.draw(backToMenuButton);
            window.display();
            break;
            /*-----/OPTIONS-------*/
        case BEST_SCORES:
            /*------BEST SCORES-----*/
            if (backToMenuButton.isPressed(window)) {
                GAME_STATE = STATES::MAIN_MENU;
            }
            window.draw(bestScoresBackground);
            window.draw(backToMenuButton);
            window.display();
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
    }
    return 0;
}


void new_game(Player& player, Collectible& coll){
    score = 0;
    scoreText.setString("Score: " + std::to_string(score));
    p[0].x = 20;
    p[0].y = 100;
    dir = 1;
    coll.randomPosition();
    for (int i = 1; i < size; i++) {
        p[i].x = 0;
        p[i].y = 0;
        p[i].dir = 1;
    }
    player.setPosition(p[0].x, p[0].y);
    size = 2;
    GAME_STATE = STATES::GAMEPLAY;
}