#include <iostream>
#include<sstream>
#include <SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<SFML\Audio.hpp>
#include<math.h>
#include<stdlib.h>
#include <vector>

using namespace sf;

//bear && cloudsddweasqssdew

class Object {
public:
    sf::Texture bear;
    sf::Sprite bearSprite;
    sf::Texture cloud1;
    sf::Sprite cloud1Sprite;
    sf::Texture cloud2;
    sf::Sprite cloud2Sprite;  
    sf::Texture santa;
    sf::Sprite santaSprite;
    Object() {
        // bear
        this->bear.loadFromFile("images/bear.png");
        this->bearSprite.setTexture(this->bear);
        this->bearSprite.setScale(0.3f, 0.3f);
        this->bearSprite.setPosition(1300, 600);
        // cloud 1
        this->cloud1.loadFromFile("images/A2.png");
        this->cloud1Sprite.setTexture(this->cloud1);
        this->cloud1Sprite.setScale(0.4f, 0.4f);
        this->cloud1Sprite.setPosition(30.f, 90.f);
        // cloud 2
        this->cloud2.loadFromFile("images/A1.png");
        this->cloud2Sprite.setTexture(this->cloud2);
        this->cloud2Sprite.setScale(0.4f, 0.4f);
        this->cloud2Sprite.setPosition(1300.f, 90.f);

        // santa
        this->santa.loadFromFile("images/santa.png");
        this->santaSprite.setTexture(this->santa);
        this->santaSprite.setScale(0.3f, 0.3f);
        this->santaSprite.setPosition(1300.f, 50.f);

    }
    
};


// player
class Player {
public:
    sf::Texture player1;
    sf::Sprite playerSprite;
    sf::Texture player2;
    sf::Sprite playerSprite1;

    Player() {
        // player1
        this->player1.loadFromFile("images/penguin.png");
        this->playerSprite.setTexture(this->player1);
        this->playerSprite.setScale(0.3f, 0.3f);
        this->playerSprite.setPosition(1000, 790);

        // player2
        this->player2.loadFromFile("images/penguin2.png");
        this->playerSprite1.setTexture(this->player2);
        this->playerSprite1.setScale(0.2f, 0.2f);
        this->playerSprite1.setPosition(500, 810);
        
    }
};

// enemy class
class Enemy {
public:
    // player2
    unsigned points1;
    Text text1;
    sf::Font font1;
    int health1;

    // player1
    unsigned points;
    bool v;
    Text text;
    int randomMax;
    int random;
    int max;
    int health;
    bool end;
    sf::Texture world;
    sf::Sprite worldSprite;
    sf::Texture fish;
    sf::Sprite fishSprite;
    sf::Font font;  
    Enemy() {
        // text1 
        this->font.loadFromFile("images/Dosis-Bold.ttf");
        this->text.setFont(this -> font);
        this->text.setFillColor(Color::Magenta);
        this->text.setString("None");
        this->text.setCharacterSize(24);
        this->health = 10;
        this->points = 0;
        // text2
        this->font1.loadFromFile("images/Dosis-Bold.ttf");
        this->text1.setFont(this->font1);
        this->text1.setFillColor(Color::Magenta);
        this->text1.setString("None");
        this->text1.setCharacterSize(24);
        this->text1.setPosition(1400.f, 0.f);
        this->health1 = 10;
        this->points1 = 0;
        //other
        this->end = false;
        this->random = this->randomMax;
        this->max = 6; 
        this->v = false;
        // fish
        this->fish.loadFromFile("images/fish1.png");
        this->fishSprite.setTexture(fish);
        fishSprite.setScale(0.2f, 0.2f);

        // background
        this->world.loadFromFile("images/background.jpg");
        this->worldSprite.setTexture(world);
        
    }  
}; 


int main()
{
    srand(time(NULL)); 
    RenderWindow window(VideoMode(1500, 1000), "shooter game", Style::Default);
    window.setFramerateLimit(60);

    // sound
    sf::Music music;
    music.openFromFile("images/merry.ogg");
    music.setVolume(20);
    music.play();
    // line 
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(750, 800)),
        sf::Vertex(sf::Vector2f(750, 950))
    };


    // GAME OVER
    sf::Texture gameOver;
    sf::Sprite gameSprite;
    sf::Texture gameOver1;
    sf::Sprite gameSprite1;;

    // Object
    Object object;

    //Player
    Player godPlayer;

    // Enemy
    Enemy enemy;
    
    //mouse position
    sf::Vector2i mouse;
    sf::Vector2f mouseView;
    std::vector<Sprite> enemies;

    while (window.isOpen() && enemy.end != true) {
       
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        // game over
        if (enemy.health == 0) {
            gameOver.loadFromFile("images/player2.jpg");
            gameSprite.setTexture(gameOver); 
        }
        if (enemy.health1 == 0) {
            if (enemy.health1 == 0) {
                gameOver.loadFromFile("images/player1.jpg");
                gameSprite.setTexture(gameOver);
            }
        }

        if (enemy.points == 100) {
            gameOver.loadFromFile("images/player1.jpg");
            gameSprite.setTexture(gameOver);

        }
        if (enemy.points1 == 100) {
            gameOver.loadFromFile("images/player2.jpg");
            gameSprite.setTexture(gameOver);
        }


        
        
         std::cout<<"\nMouse Pos:" << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y;
        mouse = Mouse::getPosition(window);
        mouseView = window.mapPixelToCoords(mouse);

        // text1
        std::stringstream ss;
        ss << "Points: " << enemy.points << "\n" 
            << "Health: " << enemy.health;
        enemy.text.setString(ss.str());
        
        // text2
        std::stringstream ss1;
        ss1 << "Points: " << enemy.points1 << "\n"
            << "Health: " << enemy.health1;
        enemy.text1.setString(ss1.str());

        // enemies
        if (enemies.size() < enemy.max) {

            if (enemy.random <=  enemy.randomMax)
                enemy.random++;

            else {
                enemy.fishSprite.setPosition(rand() % window.getSize().x - enemy.fishSprite.getGlobalBounds().width + 20, 0.f);
                int rand1 = rand() % 6;
           
                switch (rand1) {
                case 0: 
                    enemy.fish.loadFromFile("images/fish1.png");
                  
                    break;
                case 1:
                    enemy.fish.loadFromFile("images/fish2.png");
   
                    break;
                case 2:
                    enemy.fish.loadFromFile("images/fish3.png");
             
                    break;
                case 3:
                    enemy.fish.loadFromFile("images/fish4.png");

                    break;
                case 4:
                    enemy.fish.loadFromFile("images/fish5.png");

                    break;
                case 5:
                    enemy.fish.loadFromFile("images/fish6.png");
                    break;
                default: 
                    break;
                }
              //  std::cout << "\nrand : " << rand1;
                enemies.push_back(Sprite(enemy.fishSprite));
                enemy.random = 0;
            }
        }
        // enemy move
        for (size_t i = 0; i < enemies.size(); i++) {

            bool deleted = false;
            enemies[i].move(0.f, 3.f);

            if (enemies[i].getPosition().y > window.getSize().y - 130.f && enemies[i].getPosition().x < 750.f) {
                enemies.erase(enemies.begin() + i);
                enemy.health -= 1;
                std::cout << "\nHealth: " << enemy.health;

            }
            if (enemies[i].getPosition().y > window.getSize().y - 130.f && enemies[i].getPosition().x > 750.f) {
                enemies.erase(enemies.begin() + i);
                enemy.health1 -= 1;
                std::cout << "\nHealth: " << enemy.health;

            }
        }
            // button daragdah vyd
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (enemy.v == false){
                    enemy.v = true;
                    bool deleted = false;
                    for (size_t i = 0; i < enemies.size() && deleted == false; i++) {
                        if (enemies[i].getGlobalBounds().contains(mouseView)) {
                            deleted = true;
                            enemies.erase(enemies.begin() + i);
                            enemy.points += 1;
                            std::cout << "\nPoints: " << enemy.points;
                        
                        }
                    }
            }
            }
            else {
                enemy.v = false;
            }

        // move penguin
            if (Keyboard::isKeyPressed(Keyboard::Left))
                godPlayer.playerSprite.move(-10.f, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::Right))
                godPlayer.playerSprite.move(10.f, 0.f);

            if (Keyboard::isKeyPressed(Keyboard::A))
                godPlayer.playerSprite1.move(-10.f, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::D))
                godPlayer.playerSprite1.move(10.f, 0.f);


       // penguin bolon fishig ideh
            for (int i = 0; i < enemies.size(); i++) {
                if (godPlayer.playerSprite.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
                    enemies.erase(enemies.begin() + i);
                    enemy.points1 += 1;
                }
                if (godPlayer.playerSprite1.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
                    enemies.erase(enemies.begin() + i);
                    enemy.points += 1;
                }
         }

        // penguin hanatai morgoldoh
            if (godPlayer.playerSprite.getPosition().x <= 0)  // L 
                godPlayer.playerSprite.setPosition(10.f, godPlayer.playerSprite.getPosition().y);
            if (godPlayer.playerSprite.getPosition().x >= window.getSize().x - godPlayer.playerSprite.getGlobalBounds().width) // R
                godPlayer.playerSprite.setPosition(window.getSize().x - godPlayer.playerSprite.getGlobalBounds().width, godPlayer.playerSprite.getPosition().y);
            
            if (godPlayer.playerSprite1.getPosition().x <= 0)  // L 
                godPlayer.playerSprite1.setPosition(10.f, godPlayer.playerSprite1.getPosition().y);
            if (godPlayer.playerSprite1.getPosition().x >= window.getSize().x - godPlayer.playerSprite1.getGlobalBounds().width) // R
                godPlayer.playerSprite1.setPosition(window.getSize().x - godPlayer.playerSprite1.getGlobalBounds().width, godPlayer.playerSprite1.getPosition().y);
       
            // object
            object.bearSprite.move(-1.f, 0.f);
            if(object.bearSprite.getPosition().x < 0)
                object.bearSprite.setPosition(1300, 600);

            // cloud 1 move
            object.cloud1Sprite.move(1.f, 0.f);
            if (object.cloud1Sprite.getPosition().x > window.getSize().x - 1100.f)
               object.cloud1Sprite.setPosition(30.f, 90.f);

            // cloud 2 move
            object.cloud2Sprite.move(-1.f, 0.f);
            if (object.cloud2Sprite.getPosition().x < 900.f)
                object.cloud2Sprite.setPosition(1300.f, 90.f);

            // santa move
            object.santaSprite.move(-2.f, 0.f);
            if (object.santaSprite.getPosition().x < 0.f)
                object.santaSprite.setPosition(1400.f, 50.f);



        window.clear();
        window.draw(enemy.worldSprite);

        // enemy

        for (size_t i = 0; i < enemies.size(); i++) {
            window.draw(enemies[i]);

        }
        window.draw(object.santaSprite);
        
        window.draw(godPlayer.playerSprite);
        window.draw(godPlayer.playerSprite1);

        window.draw(object.bearSprite);
        window.draw(object.cloud2Sprite);
        window.draw(object.cloud1Sprite);
    
        window.draw(enemy.text);
        window.draw(enemy.text1);
        window.draw(line, 2, sf::Lines);
        window.draw(gameSprite);
        window.display();
    }
}