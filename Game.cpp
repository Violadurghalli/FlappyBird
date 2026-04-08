//
// Created by Viola Durghalli on 11/24/25.
//

#include "Game.h"
#include <ctime>

Game::Game() : backgroundSprite(background), getReadySprite(spriteSheet),
    gameOverSprite(spriteSheet), birdSprite(birdTexture), getReadySprite2(spriteSheet), gameOverSprite2(spriteSheet) ,
score(spriteSheet), highScore(spriteSheet), scoreOnes(spriteSheet), scoreTens(spriteSheet), scoreHundreds(spriteSheet),
highScoreOnes(spriteSheet), highScoreTens(spriteSheet), highScoreHundreds(spriteSheet)
{
    srand(time(0));
    if (!background.loadFromFile("../../assets/background.png"))
    {
        std::cerr << "ERROR: background texture not loaded." << std::endl;
    }
    backgroundSprite.setTexture(background, true);

    if (!pipeTexture.loadFromFile("../../assets/PipeSprite.png"))
    {
        std::cerr << "ERROR: pipe texture not loaded." << std::endl;
    }

    if (!birdTexture.loadFromFile("../../assets/bird2.png"))
    {
        std::cerr << "Error: bird texture not loaded." << std::endl;
    }

    if (!numbersTexture.loadFromFile("../../assets/numbers.png")) {
        std::cerr << "Error: numbers texture not loaded." << std::endl;
    }

    bird.setTexture(&birdTexture);

    bird.setSize({34.f, 24.f});

    // reset origin to the center of its new size
    bird.setOrigin({34.f / 2.0f, 24.f / 2.0f});

    // have it scale down properly
    // this uses its full image, but makes it 34x24
    sf::Vector2u textureSize = birdTexture.getSize();
    bird.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(textureSize.x), static_cast<int>(textureSize.y)}));


    for(int i=0; i<10; i++) //game consists of ten pipes
    {
        auto topHeight = static_cast<float>(rand() % 251 + 150);
        Pipe p(48.f, topHeight, pipeTexture);
        //^^the width is hardcoded to 48.f but the height is set random

        auto topHeight2 = 720 - topHeight - 115 - 101; // 115 will account for box
        Pipe p2(48.f, topHeight2, pipeTexture);

        sf::RectangleShape box({48.f, 50.f});

        p.setScale({1, -1}); //The set scale is moving it from the origin, the top left, so we need to adjust the y position
        p.setPosition({528, 0+p.getSize().y - 4});
        // ^^makes them get created off of screen before sliding through


        p2.setPosition({528, ((720-topHeight2-101.f))});
        box.setPosition({528, 720-topHeight2});
        // height2 and p2 are both for the bottom pipes

        top_pipes.push_back(p);
        // makes a vector of the ten pipes that are placed to start at their width behind the screen
        bottom_pipes.push_back(p2);

        boxes.push_back(box);
    }
    iter = top_pipes.begin();
    iter2 = bottom_pipes.begin();

//-----------------------------------------------------------------------
    // initialize state
    currentState = WAITING;

    // load sprite sheet
    if (!spriteSheet.loadFromFile("../../assets/Flappy Bird Sprites.png")) {
        std::cerr << "Error loading sprites sheet" << std::endl;
    }

    // start up screen setup
    getReadySprite.setTexture(spriteSheet);

    getReadySprite2.setTexture(spriteSheet);
    //  setTextureRect(Left-X, Top-Y, Width, Height)
    getReadySprite2.setTextureRect(sf::IntRect({350, 70}, {375, 22}));
    // Center the origin so it's easy to position
    getReadySprite2.setOrigin({250 / 2.0f, 27 / 2.0f});
    getReadySprite2.setPosition({350, 375});
    getReadySprite2.setScale({2.f, 2.f});

    getReadySprite.setTextureRect(sf::IntRect({250, 70}, {97, 27}));
    // ^^find "get ready" on sprite sheet

    getReadySprite.setOrigin({184 / 2.0f, 50 / 2.0f});
    getReadySprite.setPosition({350, 175});
    getReadySprite.setScale({2.8f, 2.8f});

    scoreValue = 0;
    highScoreValue = 0;

    // end screen setup
    gameOverSprite.setTexture(spriteSheet);
    gameOverSprite2.setTexture(spriteSheet);

    // setTextureRect(Left-X, Top-Y, Width, Height)
    gameOverSprite.setTextureRect(sf::IntRect({260, 195}, {121, 60}));
    gameOverSprite2.setTextureRect(sf::IntRect({150, 170}, {100, 27}));

    gameOverSprite.setOrigin({192 / 2.0f, 42 / 2.0f});
    gameOverSprite.setPosition({340, 300});
    gameOverSprite.setScale({2.5f, 2.5f});

    gameOverSprite2.setOrigin({97 / 2.0f, 27 / 2.0f});
    gameOverSprite2.setPosition({235, 175});
    gameOverSprite2.setScale({2.5f, 2.5f});

    score.setTexture(spriteSheet);
    highScore.setTexture(spriteSheet);

    score.setTextureRect(sf::IntRect({248, 95}, {17, 20}));
    highScore.setTextureRect(sf::IntRect({248, 95}, {17, 20}));

    score.setPosition({315, 287});
    score.setScale({1.3f, 1.3f});

    highScore.setPosition({315, 340});
    highScore.setScale({1.3f, 1.3f});

    // score sprites
    scoreOnes.setTexture(spriteSheet);
    scoreTens.setTexture(spriteSheet);
    scoreHundreds.setTexture(spriteSheet);

    scoreOnes.setScale({1.3f, 1.3f});
    scoreTens.setScale({1.3f, 1.3f});
    scoreHundreds.setScale({1.3f, 1.3f});

    scoreOnes.setPosition({315, 287});       // digit on the right
    scoreTens.setPosition({300, 287});       // middle digit, -15 pixels
    scoreHundreds.setPosition({285, 287});   // left digit, -30 pixels

    // high score sprites
    highScoreOnes.setTexture(spriteSheet);
    highScoreTens.setTexture(spriteSheet);
    highScoreHundreds.setTexture(spriteSheet);

    highScoreOnes.setScale({1.3f, 1.3f});
    highScoreTens.setScale({1.3f, 1.3f});
    highScoreHundreds.setScale({1.3f, 1.3f});

    // set below score
    highScoreOnes.setPosition({315, 340});
    highScoreTens.setPosition({300, 340});
    highScoreHundreds.setPosition({285, 340});

    currentPipeIndex = 0;
}

void Game::runGame()
{
    //float topHeight = static_cast<float>(rand() % 251 + 150);
    std::srand(std::time(0));
    sf::Clock dtClock; // clock for gravity
    int i = 0;


    sf::RenderWindow window(sf::VideoMode({480, 720},32),"Flappy Bird"); // open game window

    window.setFramerateLimit(60); // runs 60 times per second

    // get the size of the texture
    sf::Vector2u textureSize = background.getSize();

    // target dimensions
    sf::Vector2u windowSize = window.getSize(); // {480, 720}

    // typecast to float to keep decimal precision
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);

    backgroundSprite.setScale({scaleX, scaleY});

    srand(time(0));



    while (window.isOpen())
    {
        sf::Time dt = dtClock.restart(); // get time passed since last frame, dt - change of time

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // check for space bar
            if (event->is<sf::Event::KeyPressed>())
            {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
                {
                    // if waiting, start game
                    if (currentState == WAITING)
                    {
                        currentState = PLAYING;
                        bird.jump();
                    }
                    else if (currentState == PLAYING)
                    {
                        bird.jump();
                    }
                    else if (currentState == GAME_OVER)
                    {
                        resetGame();
                    }
                }
            }
        }

        if (currentState == PLAYING)
        {
            bird.update(dt);

            // check if bird passed pipe
            // if the pipe's right edge passes the bird, +point
            if (top_pipes[currentPipeIndex].getPosition().x + 48 < 155)
            {
                scoreValue++;

                // debug----------------------
                std::cout << "Pipe Passed! Score is now: " << scoreValue << std::endl;
                // ---------------------------

                // move on to the next pipe in the list
                currentPipeIndex++;

                // if reached the end of the vector (10), go back to 0
                if (currentPipeIndex >= top_pipes.size()) {
                    currentPipeIndex = 0;
                }
            }

            if(clock.getElapsedTime().asMilliseconds() > 1400) // every 1400 ms(1.4 secs)
            {
                iter->moving = true;    // wakes up pipe
                iter2->moving = true;   // wakes up next pipe
                iter++;                 // move on to next pipe
                iter2++;
                i++;


                //auto it = top_pipes.rbegin();
                if(iter == top_pipes.end()) // checks if you've reached end of list, if so, it restarts.
                {
                    iter = top_pipes.begin();
                    iter2 = bottom_pipes.begin();
                }

                clock.restart();
            }

            resizePipes(); // checks if they've left screen, then resets size and position before pushing it on screen again.

            if (checkCollision())
            {
                std::cout << "GAME OVER!" << std::endl;
                if (scoreValue > highScoreValue) {
                    highScoreValue = scoreValue;
                }
                //window.close();
                currentState = GAME_OVER;
                // resetGame();
            }

        }

        else if (currentState == WAITING) //bird floats
        {
            // sine wave hover effect
            // 310 is the base Y position. 3 is speed. 10 is range (pixels up/down).
            float hoverY = 310 + std::sin(dtClock.getElapsedTime().asSeconds() * 3) * 10;

            // y changes, x stays at 155
            bird.setPosition({155, hoverY});

            // reset rotation so it looks flat while hovering
            bird.setRotation(sf::degrees(0));
        }

        window.clear();
        //painters algorithm: draw background first, then middle layer, then top layer last.
        window.draw(backgroundSprite);
        window.draw(bird);
        for(auto & p : top_pipes)
            window.draw(p);

        for(auto & p2 : bottom_pipes)
            window.draw(p2);

        if (currentState == WAITING)
        {
            window.draw(getReadySprite);
            window.draw(getReadySprite2);

        }
        else if (currentState == GAME_OVER)
        {
            window.draw(gameOverSprite);
            window.draw(gameOverSprite2);

            updateScoreVisuals(scoreValue, scoreOnes, scoreTens, scoreHundreds);
            updateScoreVisuals(highScoreValue, highScoreOnes, highScoreTens, highScoreHundreds);

            // current score position
            scoreOnes.setPosition({315, 287});
            scoreTens.setPosition({300, 287});
            scoreHundreds.setPosition({285, 287});

            // high score position
            highScoreOnes.setPosition({315, 340});
            highScoreTens.setPosition({300, 340});
            highScoreHundreds.setPosition({285, 340});

            // debug------------
            // scoreOnes.setTextureRect(sf::IntRect({0, 0}, {20, 20}));
            // scoreOnes.setColor(sf::Color::Red);
            // ------------------

            // draw ones place
            window.draw(scoreOnes);
            if (scoreValue >= 10) window.draw(scoreTens);
            if (scoreValue >= 100) window.draw(scoreHundreds);

            // draw high score
            window.draw(highScoreOnes);
            if (highScoreValue >= 10) window.draw(highScoreTens);
            if (highScoreValue >= 100) window.draw(highScoreHundreds);
        }

        window.display();
    }
}

void Game::resizePipes()
{
    for(auto &p : top_pipes)
    {
        if(p.moving)
            p.move({-2, 0});
        if(p.getPosition().x < -48) // if left->right make this: if(p.getPosition().x > window.getSize().x)
        {
            p.moving = false;
            p.setSize({48.f, static_cast<float>(rand() % 251 + 150)});
            p.setPosition({528, 0+p.getSize().y -4});
            height = p.getSize().y;

        }

    }

    for(auto &p2 : bottom_pipes)
    {
        if(p2.moving)
            p2.move({-2, 0});
        if(p2.getPosition().x < -48)
        {
            p2.moving = false;
            p2.setSize({48.f, 720 - height - 115 -101});
            p2.setPosition({528, (720 - p2.getSize().y -101.f)});
            //top_pipes[i]
        }
    }

}

bool Game::checkCollision()
{
    // real "hit box" of the bird image
    sf::FloatRect birdBounds = bird.getGlobalBounds();

    // smaller "Hit box" just for math
    //  -5 pixels off every side
    sf::FloatRect hitBox;
    hitBox.position.x = birdBounds.position.x + 10.f;
    hitBox.position.y = birdBounds.position.y + 10.f;
    hitBox.size.x = birdBounds.size.x - 20.f; // -5 from left, -5 from right
    hitBox.size.y = birdBounds.size.y - 20.f; // -5 from top, -5 from bottom

    // check collision with top pipes
    for (const auto& pipe : top_pipes)
    {
        if (hitBox.findIntersection(pipe.getGlobalBounds()))
        {
            return true; // collision detected
        }
    }

    // check collision with bottom pipes
    for (const auto& pipe : bottom_pipes)
    {
        if (hitBox.findIntersection(pipe.getGlobalBounds()))
        {
            return true; // collision detected
        }
    }

    // check collision with floor
    if (bird.getPosition().y + bird.getSize().y >= 720.f - (105.f)) // the floor is drawn on image so we'll account for it here
    {
        return true;
    }

    return false; // no collision found
}


void Game::resetGame()
{
    scoreValue = 0;
    currentPipeIndex = 0;

    // reset bird
    bird.setPosition({155, 310});
    bird.setRotation(sf::degrees(0));
    bird.set_velocity({0, 0});

    // reset top pipes
    for (auto& p : top_pipes)
    {
        // set the new random size
        float newHeight = static_cast<float>(rand() % 251 + 150);
        p.setSize({48.f, newHeight});

        // set the position based on new size
        p.setPosition({528, 0 + p.getSize().y - 4});

        p.moving = false;
    }

    // reset bottom pipes
    for (size_t i = 0; i < bottom_pipes.size(); i++)
    {
        // get height of corresponding top pipe
        float topHeight = top_pipes[i].getSize().y;

        // calculate bottom pipe
        auto& p2 = bottom_pipes[i];

        p2.setSize({48.f, 720 - topHeight - 115 - 101});
        p2.setPosition({528, (720 - p2.getSize().y - 101.f)});

        p2.moving = false;
    }

    // reset iterators
    iter = top_pipes.begin();
    iter2 = bottom_pipes.begin();

    currentState = WAITING;
}

void Game::updateScoreVisuals(int scoreVal, sf::Sprite& ones, sf::Sprite& tens, sf::Sprite& hundreds)
{
    // calc digits
    int oneDigit = scoreVal % 10;
    int tenDigit = (scoreVal / 10) % 10;
    int hunDigit = (scoreVal / 100) % 10;

    // set textures
    setNumberSprite(ones, oneDigit);
    setNumberSprite(tens, tenDigit);
    setNumberSprite(hundreds, hunDigit);
}

void Game::setNumberSprite(sf::Sprite& sprite, int number)
{
    int width = 16;
    int height = 20;
    if(number ==1)
        width= 11;
    else if(number == 0)
        width = 17;
    int x = 0;
    int y = 0;

    switch (number) {
        case 0: x = 248; y = 95; break;
        case 1: x = 237; y = 80; break;
        case 2: x = 322; y = 147; break;
        case 3: x = 337; y = 147; break;
        case 4: x = 351; y = 147; break;
        case 5: x = 365; y = 147; break;
        case 6: x = 322; y = 172; break;
        case 7: x = 337; y = 172; break;
        case 8: x = 351; y = 172; break;
        case 9: x = 365; y = 172; break;
    }

    sprite.setTextureRect(sf::IntRect({x, y}, {width, height}));
}