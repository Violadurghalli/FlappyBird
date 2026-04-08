//
// Created by Viola Durghalli on 11/24/25.
//

#ifndef GAME_H
#define GAME_H

#include "Pipe.h"
#include "FlyingObject.h"
#include <SFML/Graphics.hpp>

enum GameState {
    WAITING,   // shows a screen, bird shows
    PLAYING,   // run game
    GAME_OVER  // player lost, show game over screen with scores
};

class Game {
    sf::Texture pipeTexture;  // the textures show up in the order that you draw them.
    sf::Texture background;
    sf::Sprite backgroundSprite;
    sf::Texture birdTexture;
    sf::Sprite birdSprite;
    bool moving = false;
    //so if you want pipes to show up above the background, draw the background first

    bool checkCollision();

    FlyingObject bird;

    std::vector<Pipe> top_pipes;
    std::vector<Pipe> bottom_pipes;
    std::vector<sf::RectangleShape> boxes;
    //^^the boxes will be placed between top and bottom pipes to account for necessary space.


    std::vector<Pipe>::iterator iter; // for top pipes
    std::vector<Pipe>::iterator iter2; // for bottom pipes

    sf::Clock clock;
    float height;
    void resizePipes();

    sf::Texture spriteSheet;

    sf::Sprite getReadySprite;
    sf::Sprite getReadySprite2;

    sf::Sprite gameOverSprite;
    sf::Sprite gameOverSprite2;
    sf::Sprite score, highScore;

    GameState currentState;

    sf::Texture numbersTexture;             // holds numbers.png
    std::vector<sf::Sprite> scoreSprites;   // holds the displayed digits
    // ^^helpers to display score


    void updateScoreDisplay(int score);

    int scoreValue;
    int highScoreValue;

    // score sprites - can only go up to 999
    sf::Sprite scoreOnes, scoreTens, scoreHundreds;

    // high score sprites
    sf::Sprite highScoreOnes, highScoreTens, highScoreHundreds;

    void setNumberSprite(sf::Sprite& sprite, int number);
    void updateScoreVisuals(int scoreVal, sf::Sprite& ones, sf::Sprite& tens, sf::Sprite& hundreds);

    int currentPipeIndex;
public:
    Game();
    void runGame();
    void resetGame();
};


#endif //GAME_H
