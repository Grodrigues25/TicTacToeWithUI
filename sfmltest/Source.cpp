#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// TODO: Understand how the sf::Mouse::getPosition() coordinates work

void generateMap(sf::RenderWindow& window)
{
    // Vertical Lines Definition
    sf::RectangleShape line1(sf::Vector2f(600.f, 10.f));
    line1.rotate(90.f);
    line1.setPosition(300, 100);
    line1.setFillColor(sf::Color::Black);

    sf::RectangleShape line2(sf::Vector2f(600.f, 10.f));
    line2.rotate(90.f);
    line2.setPosition(500, 100);
    line2.setFillColor(sf::Color::Black);
    
    // Horizontal Lines Definition
    sf::RectangleShape line3(sf::Vector2f(600.f, 10.f));
    line3.setPosition(100, 300);
    line3.setFillColor(sf::Color::Black);

    sf::RectangleShape line4(sf::Vector2f(600.f, 10.f));
    line4.setPosition(100, 500);
    line4.setFillColor(sf::Color::Black);

    // Draw
    window.draw(line1);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
}

void generateCrosses(sf::RenderWindow &window)
{
    sf::RectangleShape line1(sf::Vector2f(150.f, 10.f));
    line1.setRotation(45.f);
    line1.setPosition(350, 350);

    sf::RectangleShape line2(sf::Vector2f(150.f, 10.f));
    line2.setRotation(135.f);
    // Adjust for the fact that the rotation happens in relation to a corner of the rectangle.
    line2.setPosition(450 + 10 * sqrt(2) / 2, 350 + 10*sqrt(2)/2);

    line1.setFillColor(sf::Color::Black);
    line2.setFillColor(sf::Color::Black);

    window.draw(line1);
    window.draw(line2);
}

void generateCircles(sf::RenderWindow& window)
{
    sf::CircleShape outerCircle(60);
    outerCircle.setPosition(140, 140);

    sf::CircleShape innerCircle(50);
    innerCircle.setPosition(150, 150);

    outerCircle.setFillColor(sf::Color::Black);
    innerCircle.setFillColor(sf::Color::White);

    window.draw(outerCircle);
    window.draw(innerCircle);
}

int main()
{
    // SETTINGS
    int windowSize = 800;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "TicTacToe", sf::Style::Default, settings);
    sf::RectangleShape background(sf::Vector2f(windowSize, windowSize));
    background.setFillColor(sf::Color::White);

    //GAME DATA STRUCTURES
    string board[3][3] = { {" "," "," "},{" "," "," "},{" "," "," "} };
    int winStatus;
    sf::Vector2i localPosition;

    //WHILE WINDOW IS OPEN LOGIC AKA WHILE THE GAME IS RUNNING
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);

        generateMap(window);
        
        // GAME LOGIC TO PLAY ROUNDS AND SAVE PLAYED LOCATIONS
        
        /*
        For game logic check better how events work so I can make the game sort of wait for the mouse click before proceeding <- Priority!

        Also print in window which player turn it is
        */

        for (int playedMoves = 0; playedMoves < 9; playedMoves++)
        {
            cout << "Player " << playedMoves % 2 + 1 << " turn to play. Select your Board coordinates." << endl;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                if (localPosition.x > 105 && localPosition.x < 295 && localPosition.y > 105 && localPosition.y < 295)
                {
                    if (playedMoves % 2 + 1 == 1)
                    {
                        board[0][0] = "X";
                    }
                    else
                    {
                        board[0][0] = "O";
                    }
                }
            }

            for (int row = 0; row < 3; row++)
            {
                for (int column = 0; column < 3; column++)
                {
                    if (board[row][column] == "O")
                    {
                        generateCircles(window);
                    }
                    else
                    {
                        generateCrosses(window);
                    }

                }
            }
                

        }



        

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            if (localPosition.x > 105 && localPosition.x < 295 && localPosition.y > 105 && localPosition.y < 295)
            {
                generateCircles(window);
            }
        }

        window.display();

    }

    return 0;
}


/*
    1|2|3
    -|-|-
    4|5|6
    -|-|-
    7|8|9

Centers
// 1 -> 200,200
// 2 -> 400,200
// 3 -> 600,200
// 4 -> 200,400
// 5 -> 400,400
// 6 -> 600,400
// 7 -> 200,600
// 8 -> 400,600
// 9 -> 600,600

*/