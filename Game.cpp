#include "Game.h"
#include <string> 

void Game::initVariables(){
    this->pi = 3.14159f;
    this->gameWidth = 800;
    this->gameHeight = 600;
    this->paddleSize = sf::Vector2f(50, 100);
    this->ballRadius = 40.f;
    this->AITime = sf::seconds(0.1f);
    this->basePaddleSpeed = 400.f;
    this->paddleSpeed = 400.f;
    this->rightPaddleSpeed = 0.f;
    this->baseBallSpeed = 400.f;
    this->ballSpeed = 400.f;
    this->ballAngle = 0.f; // TODO
    this->dannyAngle = 0.f;
    this->isPlaying = false;
    this->userPoint = 0;
    this->cpuPoint = 0;
    this->dannySpeed = 400.f;

}

void Game::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight), 32), "SFML Tennis",
                            sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);

    if(!this->loadscreenTexture.loadFromFile("resources/rumham.png"))
        exit(0);
    this->loadscreen.setTexture(loadscreenTexture);
    this->loadscreen.setPosition(170, 50);

    this->dannyTexture.loadFromFile("resources/dannysprite.png");
    this->dannySprite = sf::IntRect(32, 0, 32, 48); //128 x 192
    this->sprite = sf::Sprite(dannyTexture,dannySprite);
    this->sprite.setPosition(500, 100);
}

void Game::initPaddles(){
      // Create the left paddle
    this->leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    this->leftPaddle.setOutlineThickness(3);
    this->leftPaddle.setOutlineColor(sf::Color::Black);
    this->leftPaddle.setFillColor(sf::Color(100, 100, 200));
    this->leftPaddle.setOrigin(paddleSize / 2.f);
    if(!this->leftPaddleTexture.loadFromFile("resources/leftpaddle.png"))
        return exit(0);
    this->leftPaddle.setTexture(&leftPaddleTexture);

    // Create the right paddle
    this->rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    this->rightPaddle.setOutlineThickness(3);
    this->rightPaddle.setOutlineColor(sf::Color::Black);
    this->rightPaddle.setFillColor(sf::Color(200, 100, 100));
    this->rightPaddle.setOrigin(paddleSize / 2.f);
    if(!this->rightPaddleTexture.loadFromFile("resources/rightpaddle.png"))
        return exit(0);
    rightPaddle.setTexture(&rightPaddleTexture);

    // Moving box
    this->middleLine.setSize(paddleSize - sf::Vector2f(3, 3));
    this->middleLine.setOutlineColor(sf::Color::Black);
    this->middleLine.setOutlineThickness(3);
    this->middleLine.setPosition(300, 400);
    this->middleLine.setTexture(&loadscreenTexture);


}
void Game::initBall(){
    // Create the rum ball
    this->ball.setRadius(ballRadius - 3);
    //this->ball.setOutlineThickness(2);
    this->ball.setOutlineColor(sf::Color::Black);
    this->ball.setFillColor(sf::Color::White);
    this->ball.setOrigin(ballRadius / 1, ballRadius / 1);
    if (!this->balltexture.loadFromFile("resources/rumball.png"))
        return exit(0);
    this->ball.setTexture(&balltexture);
}

void Game::initFonts(){
    if (!this->font.loadFromFile("resources/tuffy.ttf"))
        return exit(0);
}

void Game::initMessages(){
    this->pauseMessage.setFont(font);
    this->pauseMessage.setCharacterSize(40);
    this->pauseMessage.setPosition(170.f, 200.f);
    this->pauseMessage.setFillColor(sf::Color::White);
    this->pauseMessage.setString("Welcome to Danny Pong!\n\nPress space to start the game.");
    this->countScore();
}

void Game::countScore(){
    this->scoreCard.setFont(font);
    this->scoreCard.setCharacterSize(40);
    this->scoreCard.setPosition(333.f, 25.f);
    this->scoreCard.setFillColor(sf::Color::White);
    std::string cpuScore = std::to_string(this->cpuPoint);
    std::string userScore = std::to_string(this->userPoint);
    this->scoreCard.setString(userScore + " to " + cpuScore);
    this->ballSpeed = baseBallSpeed;
    this->paddleSpeed = basePaddleSpeed;
}

const bool Game::running() const{
	return this->window->isOpen();
}

void Game::pollEvents(){
    while (this->window->pollEvent(this->event)){
            // Window closed or escape key pressed: exit
            if ((this->event.type == sf::Event::Closed) ||
               ((this->event.type == sf::Event::KeyPressed) && (this->event.key.code == sf::Keyboard::Escape))){
                this->window->close();
                break;
            }
            // Space key pressed: play
            if (((this->event.type == sf::Event::KeyPressed) && (this->event.key.code == sf::Keyboard::Space)) ||
                (this->event.type == sf::Event::TouchBegan)){
                if (!this->isPlaying){
                    // (re)start the game
                    this->isPlaying = true;
                    clock.restart();

                    // Reset the position of the paddles and ball
                    leftPaddle.setPosition(10.f + paddleSize.x / 2.f, gameHeight / 2.f);
                    rightPaddle.setPosition(gameWidth - 10.f - paddleSize.x / 2.f, gameHeight / 2.f);
                    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);

                    // Reset the ball angle
                    do{
                        // Make sure the ball initial angle is not too much vertical
                        dannyAngle = static_cast<float>(std::rand() % 360) * 2.f * pi / 360.f;
                        ballAngle = static_cast<float>(std::rand() % 360) * 2.f * pi / 360.f;
                    }
                    while (std::abs(std::cos(ballAngle)) < 0.7f && std::abs(std::cos(dannyAngle)) < 0.7f);
                }
            }

            // Window size changed, adjust view appropriately
            if (this->event.type == sf::Event::Resized){
                sf::View view;
                view.setSize(gameWidth, gameHeight);
                view.setCenter(gameWidth / 2.f, gameHeight  /2.f);
                this->window->setView(view);
            }
        }
}

void Game::movePaddles(){
     if (this->isPlaying){
        float deltaTime = clock.restart().asSeconds();

        // Move user paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            (leftPaddle.getPosition().y - paddleSize.y / 2 > 5.f)){
            leftPaddle.move(0.f, -paddleSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            (leftPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f)){
            leftPaddle.move(0.f, paddleSpeed * deltaTime);
        }

        if (sf::Touch::isDown(0)){
            sf::Vector2i pos = sf::Touch::getPosition(0);
            sf::Vector2f mappedPos = this->window->mapPixelToCoords(pos);
            leftPaddle.setPosition(leftPaddle.getPosition().x, mappedPos.y);
        }

        // Move CPU paddle
        if (((rightPaddleSpeed < 0.f) && (rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
            ((rightPaddleSpeed > 0.f) && (rightPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))){
            rightPaddle.move(0.f, rightPaddleSpeed * deltaTime);
        }

        // Update the CPU paddle direction according to the ball position
        if (AITimer.getElapsedTime() > AITime){
            AITimer.restart();
            if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + paddleSize.y / 2)
                rightPaddleSpeed = paddleSpeed;
            else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - paddleSize.y / 2)
                rightPaddleSpeed = -paddleSpeed;
            else
                rightPaddleSpeed = 0.f;
        }

        // Move the ball
        float factor = ballSpeed * deltaTime;
        ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
        float dannyFactor = dannySpeed * deltaTime;
        sprite.move(std::cos(dannyAngle) * dannyFactor, std::sin(dannyAngle) * dannyFactor);

    }
}
void Game::checkCollisions(){
    const std::string inputString = "Press space to restart or\nescape to exit.";
    // Check collisions between the ball and the screen
    if (ball.getPosition().x - ballRadius <= 0.f){
        this->isPlaying = false;
        pauseMessage.setString("You Lost!\n\n" + inputString);
        this->cpuPoint++;
        this->point(); // Move box after win
        this->countScore();
    }
    if (ball.getPosition().x + ballRadius > gameWidth){
        this->isPlaying = false;
        pauseMessage.setString("You Won!\n\n" + inputString);
        this->userPoint++;
        this->point(); // Move box after win
        this->countScore();
    }
    if (ball.getPosition().y - ballRadius < 0.f){
        this->ballAngle = -ballAngle;
        ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
    }
    if (ball.getPosition().y + ballRadius > gameHeight){
        this->ballAngle = -ballAngle;
        ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.1f);
    }

    // Check the collisions between the ball and the paddles
    // Left Paddle
    if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
        ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
        ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
        ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2){
        if (ball.getPosition().y > leftPaddle.getPosition().y)
            this->ballAngle = pi - ballAngle + static_cast<float>(std::rand() % 20) * pi / 180;
        else
            this->ballAngle = pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;
        
        this->ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
    }

    // Right Paddle
    if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 &&
        ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
        ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
        ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2){
        if (ball.getPosition().y > rightPaddle.getPosition().y)
            this->ballAngle = pi - ballAngle + static_cast<float>(std::rand() % 20) * pi / 180;
        else
            this->ballAngle = pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;

        this->ball.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
    }   

    // Box
    if (ball.getPosition().x + ballRadius > sprite.getPosition().x - paddleSize.x / 2 &&
        ball.getPosition().x + ballRadius < sprite.getPosition().x &&
        ball.getPosition().y + ballRadius >= sprite.getPosition().y - paddleSize.y / 2 &&
        ball.getPosition().y - ballRadius <= sprite.getPosition().y + paddleSize.y / 2){
        if (ball.getPosition().y > sprite.getPosition().y)
            this->ballAngle = pi - ballAngle + static_cast<float>(std::rand() % 20) * pi / 180;
        else
            this->ballAngle = pi - ballAngle - static_cast<float>(std::rand() % 20) * pi / 180;

        this->ball.setPosition(sprite.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
        this->point();
        this->paddleSpeed+=100;
    }
    this->moveDanny();
}
void Game::moveDanny(){
    // Check collisions between the danny and the screen
    if (sprite.getPosition().x <= 0.f){
        this->dannyAngle = pi - dannyAngle - static_cast<float>(std::rand() % 20) * pi / 180;
        this->sprite.setPosition(0.1f, sprite.getPosition().y);
    }
    if (sprite.getPosition().x > gameWidth){
        this->dannyAngle = pi - dannyAngle - static_cast<float>(std::rand() % 20) * pi / 180;
        this->sprite.setPosition(gameWidth, sprite.getPosition().y);
    }
    if (sprite.getPosition().y - ballRadius < 0.f){
        this->dannyAngle = -dannyAngle;
        this->sprite.setPosition(sprite.getPosition().x, ballRadius + 0.1f);
    }
    if (sprite.getPosition().y + ballRadius > gameHeight){
        this->dannyAngle = -dannyAngle;
        this->sprite.setPosition(sprite.getPosition().x, gameHeight - ballRadius - 0.1f);
    }
}
void Game::point(){
    this->ballSpeed+=100;
    this->sprite.setPosition(rand() % 700 + 100, rand() % 500 + 100);
}
void Game::danny(){
    if (this->dannyClock.getElapsedTime().asSeconds() > 0.5f){
      if (dannySprite.left > 64) 
        dannySprite.left = 0;
      else
        dannySprite.left += 32;

      sprite.setTextureRect(dannySprite);
      this->dannyClock.restart();
    }
}
void Game::rungame(){
    while (this->window->isOpen()){
        // Handle events
        this->pollEvents();

        // Clear the window
        this->window->clear(sf::Color(0, 0, 0));

        if (this->isPlaying){
            // Draw the paddles and the ball
            this->window->draw(scoreCard);
            this->window->draw(leftPaddle);
            this->window->draw(rightPaddle);
            this->window->draw(ball);
            this->window->draw(sprite);
            this->danny();
            this->movePaddles();
            this->checkCollisions();
        }
        else{
            // Draw the pause message
            this->danny();
            this->window->draw(sprite);
            this->window->draw(pauseMessage);
            this->window->draw(loadscreen);
        }

        // Display things on screen
        this->window->display();
    }
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initPaddles();
    this->initBall();
	this->initFonts();
	this->initMessages();
}