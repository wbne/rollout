#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
int main()
{
    //Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rollout");
    //caps frame rate at monitor refresh rate
    window.setVerticalSyncEnabled(true);

    //Player 1
    sf::CircleShape blebby(30.f);
    blebby.setFillColor(sf::Color::White);
    bool inAir = true;
    bool hasSpeed = false;
    //Player 1 hit box
    sf::FloatRect boundingBox;
    //Player 1 velocity and spawn
    sf::Vector2f blebv(0, 0);
    blebby.setPosition(50.f, 50.f);
    //Floor
    sf::RectangleShape floor(sf::Vector2f(800.f, 160.f));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(sf::Vector2f(0.f, 500.f));

    //TODO: add player 2 and actual game play

    //loop boi
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
            case sf::Event::Closed: window.close(); break; //close
            case sf::Event::KeyPressed:
                //checks for player 1 key presses
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //up
                        if(!inAir)
                        {
                            blebv.y += -20;
                            inAir = true; //only jump on ground
                        }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left
                        blebv.x += -1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //right
                        blebv.y += 1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //down
                        blebv.x += 1;
                    break;
            default: break; //for later?
            }
        }



        if(inAir)
            blebv.y += 1; //gravity
        if(std::pow(blebv.x, 2) + std::pow(blebv.y,2) > 500)
        {
            hasSpeed = true; //checks if player 1 is fast enough for magic
            std::cout<<"SPEED:"<<blebv.x<<" "<<blebv.y<<std::endl;
        }
        else
            hasSpeed = false;

        blebby.move(blebv); //displacement applied from vector
        window.clear(sf::Color::Cyan); //sky
        window.draw(blebby); //drawing player 1 after moving
        window.draw(floor); //drawing floor
        window.display(); //render

        boundingBox = blebby.getGlobalBounds(); //checks for player 1 coords
        if(blebby.getPosition().x < 0) //left side
        {
           blebv.x = 0; //forcibly moves player within the screen
           blebby.setPosition(0, blebby.getPosition().y);
        }
        else if(blebby.getPosition().x > 740) //right side
        {
            blebv.x = 0;//same here
            blebby.setPosition(740, blebby.getPosition().y);
        }
        if(blebby.getPosition().y > 440) //floor "collision"
        {
            blebv.y = 0;//makes you grounded and sets your position
            blebby.setPosition(blebby.getPosition().x, 440.f);
            inAir = false;
        }
            //no sky hit box because I feel it's not needed


    }

    return 0;
}

