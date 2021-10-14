#include "Game.h"

//Private functions

void Game::initVariable() {
    this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->health = 10;
    this->points = 0;
    this->enemySpawnTimerMax = 100.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode,"Game Project",
                                        sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (this->font.loadFromFile("/home/kevin/CLionProjects/GameProject/Fonts/Amatic-Bold.ttf")) {
        std::cout << "ERROR::GAME::initFonts() - fail to load font" << "\n";
    }
}

void Game::intEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Black);
    this->enemy.setOutlineThickness(2.f);
}

//Constructor
Game::Game() {
    this->initVariable();
    this->initWindow();
    this->intEnemies();
    this->initFonts();
    this->initText();
}

//Destructor
Game::~Game() {
    delete this->window;
}

//Accessors
const bool Game::running() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

//Functions

void Game::spawnEnemy() {
 /*Return void
  spawn enemy and set theirs color and positions
  -set a random position
  -set a random color
  -add enemy to the vector
  */

    this->enemy.setPosition(
            static_cast<float>(rand()%static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            static_cast<float>(rand()%static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)));

    this->enemy.setFillColor(sf::Color::Green);

    //spawn the enemy
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {
    //event pulling / updating events
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }

}

void Game::updateMousePositions() {
    /* void return
    Update mouse positions:
        Mouse position relative to windows (vector2i)
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText() {
    std::stringstream ss;
    ss << "points " << this->points << "\n"
        << "health " << this->health << "\n";
    this->uiText.setString(ss.str());
}

void Game::updateEnemies() {
    /* Return void
      updates the enemy spawn timer and spawn enemies when
      the total amount of enemies is smaller than the maximum
      movies the enemies downwards
      removes the enemies at the edge of the screen //TO do
     */
//updating the timer for enemies to spawn
    if(this->enemies.size() < this->maxEnemies) {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            //spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Moving and updating enemies
    for (int i = 0; i < this->enemies.size(); i++) {
        bool deleted = false;

       this->enemies[i].move(0.f, 1.f);

        //If the enemy pass the Y part of the screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "health: " << this->health << "\n";
        }

    }

    //check if clicked upon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(this->mouseHeld == false) {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    //gain points
                    this->points += 1;
                    std::cout << "points: " << this->points << "\n";
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Game::update() {

    this->pollEvents();
    if(this->endGame == false){
        this->updateMousePositions();
        this->updateEnemies();
        this->updateText();
    }

    //EndGame condition
    if(this->health <= 0) {
        this->endGame = true;
    }

}

void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Game::render() {
    /*Return void
    render the game objects
    1) Render game object
    2) clear old frame
    3) display frames in window
    */

    this->window->clear();

    //draw game objects
    this->renderEnemies(*this->window);
    this->renderText(*this->window);

    this->window->display();
}


















