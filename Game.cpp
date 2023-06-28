#include "Game.h"

void Game::initVariables(){
    this->pi = 3.14159f;
    this->gameWidth = 800;
    this->gameHeight = 600;
    this->paddleSize(50, 100);
    this->ballRadius = 40.f;

}

void Game::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight), 32), "SFML Tennis",
                            sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);

    if(!this->loadscreenTexture.loadFromFile("resources/rumham.png"))
        exit(0);
    this->loadscreen.setTexture(loadscreenTexture);
    this->loadscreen.setPosition(170, 50);
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

}


