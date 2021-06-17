#pragma warning(disable : 4996) 
//Biblioteki
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <windows.h> 
#include <sstream>
#include <fstream>
#include <cstdio>
#include <ctime>

//Klasy
#include "Player.h"
#include "Collectible.h"
#include "SlowBonus.h"
#include "Button.h"

/*Wymiary okna*/
const int WindowWidth = 720;
const int WindowHeight = 720;

/*Stany w których może być gra*/
enum STATES { MAIN_MENU = 1, GAMEPLAY, GAME_OVER, OPTIONS, HOW_TO_PLAY, BEST_SCORES, PAUSE };
char GAME_STATE = STATES::MAIN_MENU;

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
unsigned int bestScore{ 0 };


int speed = 120;
const int step = 40;

sf::Text scoreText;
sf::Text bestScoreText;
sf::Text scoresText[15];

struct Point{
    int x = 20;
    int y = 100;
    int dir{ 1 };
}p[350];

void new_game(Player& player, Collectible& coll);
void saveResult(unsigned int points);
void getResults(sf::Text scoresText[]);

void sort(int tab[15], std::string s[15][3]);


int main(){
    /*GENERAL SETUP*/
    srand(time(NULL));
    sf::RenderWindow window{ sf::VideoMode(WindowWidth,WindowHeight), "Snake" , sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(60);

    Player player(WindowWidth / 2, WindowHeight / 2);
    Collectible coll("Graphics/collectible.png");
    Collectible slowB("Graphics/slow.png");
    Collectible fastB("Graphics/fast.png");

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
    scoreText.setColor(sf::Color::White);
    scoreText.setCharacterSize(18);
    scoreText.setOrigin({ 0,0 });
    scoreText.setPosition({ 20, 5 });
    scoreText.setString("Score: " + std::to_string(score));

    bestScoreText.setFont(font);
    bestScoreText.setColor(sf::Color::White);
    bestScoreText.setCharacterSize(18);
    bestScoreText.setOrigin({ 0,0 });
    bestScoreText.setPosition({ 20, 35 });
    //bestScoreText.setString("Best Score: " + std::to_string(score));

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
    
    for (int i = 0; i < 15; i++) {
        scoresText[i].setFont(font);
        scoresText[i].setFillColor(sf::Color::White);
        scoresText[i].setPosition({ 50,150 + 30 * static_cast<float>(i) });
        scoresText[i].setCharacterSize(16);
    }


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
                getResults(scoresText);
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
            

            if (p[0].x == coll.getPosition().x && p[0].y == coll.getPosition().y) {
                size++;
                score += 10;
                scoreText.setString("Score: " + std::to_string(score));
                bool bad = true;
                
                while (bad) {                                        
                    coll.randomPosition();
                    if (size % 2 == 0)   slowB.randomPosition();
                    else slowB.setPosition(-100, -100);
                    for (int i = 0; i < size; i++) {
                        if (coll.getPosition().x == p[i].x && coll.getPosition().y == p[i].y) {
                            bad = true;
                            break;
                        }
                        else bad = false;
                    }                    
                }

            }

            if (p[0].x == slowB.getPosition().x && p[0].y == slowB.getPosition().y) {
                speed += 50;
                slowB.setPosition(-100,-100);
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
                window.draw(slowB);
                window.draw(fastB);
                window.draw(scoreText);
                window.draw(bestScoreText);
                can_change_dir = true;
                window.display();
                Sleep(speed);

                /*Warunek sprawdzający czy głowa węża nie napotkała jakiegoś jego segmentu*/
                if (size > 1) {
                    for (int i = 1; i < size; i++) {
                        if (p[0].x == p[i].x && p[0].y == p[i].y) {
                            window.clear();
                            saveResult(score);
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
            
            for (int i = size-1; i >=0; i--) {
                /*if(i==size-1) player.setTexture(i, last_segment_dir, size - 1);
                else player.setTexture(i, dir,size-1);*/
                player.setTexture(i, p[i].dir, size - 1);               
                player.setPosition(p[i].x, p[i].y);
                window.draw(player);
            }
            window.draw(restartGameButton);
            window.draw(backToMenuButton);
            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(bestScoreText);
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
            for (int i = 0; i < 15; i++) {
                window.draw(scoresText[i]);
            }
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
    getResults(scoresText);
    GAME_STATE = STATES::GAMEPLAY;
}

void saveResult(unsigned int points) {
    std::fstream plik;
    std::string scores[15][3];
    int tab[15];

    plik.open("results.txt", std::ios::in);
    for (int i = 0; i < 15; i++) {
        plik >> scores[i][0] >> scores[i][1] >> scores[i][2];
        try {

            tab[i] = stoi(scores[i][0]);
        }
        catch (std::exception& err) {
            tab[i] = 0;
        }
    }
    sort(tab, scores);
    /*--- Zapis daty i godziny do stringa --*/
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::stringstream dateStream;
    std::stringstream timeStream;
    dateStream << std::put_time(&tm, "%d-%m-%Y");
    timeStream << std::put_time(&tm, "%H:%M:%S");
    std::string date = dateStream.str();
    std::string time = timeStream.str();
    /*----------------------------*/

    if (points > tab[14]) {
        tab[14] = points;
        scores[14][0] = std::to_string(points);
        scores[14][1] = date;
        scores[14][2] = time;
    }
    sort(tab, scores);
    plik.close();

    plik.open("results.txt", std::ios::out);
    for (int i = 0; i < 15; i++) {
        plik << scores[i][0] << " " << scores[i][1] << " " << scores[i][2] << std::endl;
    }
    plik.close();
}

void sort(int tab[15], std::string s[15][3]) {
    bool sorted = false;
    while (!sorted) {
        for (int i = 0; i < 14; i++) {
            if (tab[i] < tab[i + 1]) {
                std::swap(tab[i], tab[i + 1]);
                std::swap(s[i][0], s[i + 1][0]);
                std::swap(s[i][1], s[i + 1][1]);
                std::swap(s[i][2], s[i + 1][2]);
                sorted = false;
                break;
            }
            else {
                sorted = true;
            }
        }
    }
}

void getResults(sf::Text scoresText[]) {
    std::fstream plik;
    std::string strings[15][3];

    plik.open("results.txt", std::ios::in);
    std::cout << strings[0][0] << std::endl;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 3; j++) {
            plik >> strings[i][j];
        }
        std::stringstream ss;
        if (!strings[i][0].empty()) {
            ss << std::setw(2) << i + 1 << ". " << std::setw(6) << strings[i][0] << " | " << strings[i][1] << " | " << strings[i][2];
            scoresText[i].setString(ss.str());
        }
        
    }
    bestScoreText.setString("Best Score: " + strings[0][0]);
    plik.close();
}
