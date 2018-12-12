#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
int main()
{
    //Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rollout");
    //caps frame rate at monitor refresh rate
    window.setVerticalSyncEnabled(true);

    int point = 0;
    int rando = 0;
    //Player 1
    sf::CircleShape blebby(30.f);
    blebby.setFillColor(sf::Color::White);
    bool inAir = true;
    bool hasSpeed = false;
    int blebscore = 0;
    //Player 1 hit box
    sf::FloatRect boundingBox;
    //Player 1 velocity and spawn
    sf::Vector2f blebv(0, 0);
    blebby.setPosition(50.f, 50.f);
    double blebspeed = 0;

    //Player 2
    sf::CircleShape blebster(30.f);
    blebster.setFillColor(sf::Color::Black);
    bool inAirster = true;
    bool hasSpeedster = false;
    int blebsterscore = 0;
    //Player 2 hit box
    sf::FloatRect boundingBoxster;
    //Player 2 velocity and spawn
    sf::Vector2f blebsterv(0, 0);
    blebster.setPosition(150.f, 150.f);
    double blebsterspeed = 0;

    //Floor
    sf::RectangleShape floor(sf::Vector2f(800.f, 160.f));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(sf::Vector2f(0.f, 500.f));

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
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //down
                        blebv.y += 1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //left
                        blebv.x += 1;
                        //p2 stuff
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //up
                    if(!inAirster)
                        {
                            blebsterv.y += -20;
                            inAirster = true; //only jump on ground
                        }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //left
                        blebsterv.x += -1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //down
                        blebsterv.y += 1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //right
                        blebsterv.x += 1;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        std::cout<<blebscore<<"-"<<blebsterscore<<std::endl;
                    break;
            default: break; //for later?
            }
        }



        if(inAir)
            blebv.y += 1; //gravity
        if(inAirster)
            blebsterv.y +=1; //grav 2
        if(blebspeed > 400)
        {
            hasSpeed = true; //checks if player 1 is fast enough for magic
           //std::cout<<"SPEED:"<<blebv.x<<" "<<blebv.y<<std::endl;
        }
        else
            hasSpeed = false;
        if(blebsterspeed > 400) //p2 speed
        {
            hasSpeedster = true; //checks if player 1 is fast enough for magic
            //std::cout<<"SPEEDster:"<<blebsterv.x<<" "<<blebsterv.y<<std::endl;
        }
        else
            hasSpeedster = false;

            //calculates blebs speeds
        blebspeed = std::pow(blebv.x, 2) + std::pow(blebv.y, 2);
        blebsterspeed = std::pow(blebsterv.x, 2) + std::pow(blebsterv.y, 2);

        //actual game thing
        if(boundingBox.intersects(boundingBoxster))
        {
            //std::cout<<hasSpeed<<hasSpeedster<<std::endl;
            point = 0;
            rando = rand() % 800;
            if(hasSpeed && hasSpeedster)
                if(blebsterspeed > blebspeed)
                    point = 2;
                else
                    point = 1;
            else if(hasSpeed)
                point = 1;
            else if(hasSpeedster)
                point = 2;
            //std::cout<<"blebby: "<<blebscore<<std::endl;
            //std::cout<<"blebster: "<<blebsterscore<<std::endl;
            switch(point)
            {
                case 1:
                    blebscore++;
                    blebster.setPosition(rando,0);
                    inAirster = true;
                    break;
                case 2:
                    blebsterscore++;
                    blebby.setPosition(rando,0);
                    inAir = true;
                    break;
                default:
                    break;
            }
            hasSpeed = false;
            hasSpeedster = false;
        }

        blebby.move(blebv); //displacement applied from vector
        blebster.move(blebsterv); //displacement from vector 2
        window.clear(sf::Color::Cyan); //sky
        window.draw(blebby); //drawing player 1 after moving
        window.draw(blebster); //drawing p2
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
        boundingBoxster = blebster.getGlobalBounds(); //checks for player 2 coords
        if(blebster.getPosition().x < 0) //left side
        {
           blebsterv.x = 0; //forcibly moves player within the screen
           blebster.setPosition(0, blebster.getPosition().y);
        }
        else if(blebster.getPosition().x > 740) //right side
        {
            blebsterv.x = 0;//same here
            blebster.setPosition(740, blebster.getPosition().y);
        }
        if(blebster.getPosition().y > 440) //floor "collision"
        {
            blebsterv.y = 0;//makes you grounded and sets your position
            blebster.setPosition(blebster.getPosition().x, 440.f);
            inAirster = false;
        }
            //no sky hit box because I feel it's not needed


    }

    return 0;
}

