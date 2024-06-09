#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// TODO: Check why game breaks when clicking on a position that is not a playable square
// TODO: Include checks to see if the played location is valid
// TODO: Include an header to display which player's turn it is to play
// TODO: Include a title
// TODO: Check what adaptations I need to do for the game to work in different window sizes
// TODO: Include win condition checks
// TODO: Block playability when a player wins
// TODO: Draw a line on the winning line
// TODO: Analyse implementing replayability features, such a playing a new game after one ends
// TODO: Analyse implementing a Scoreboard

void generateCrosses(sf::RenderWindow& window, int x, int y)
{
    sf::RectangleShape line1(sf::Vector2f(150.f, 10.f));
    line1.setRotation(45.f);
    line1.setPosition(x-50, y-50);

    sf::RectangleShape line2(sf::Vector2f(150.f, 10.f));
    line2.setRotation(135.f);
    // Adjust for the fact that the rotation happens in relation to a corner of the rectangle.
    line2.setPosition(x + 50 + 10 * sqrt(2) / 2, y - 50 + 10 * sqrt(2) / 2);

    line1.setFillColor(sf::Color::Black);
    line2.setFillColor(sf::Color::Black);

    window.draw(line1);
    window.draw(line2);
}

void generateCircles(sf::RenderWindow& window, int x, int y)
{
    sf::CircleShape outerCircle(60);
    outerCircle.setPosition(x-60, y-60);

    sf::CircleShape innerCircle(50);
    innerCircle.setPosition(x-50, y-50);

    outerCircle.setFillColor(sf::Color::Black);
    innerCircle.setFillColor(sf::Color::White);

    window.draw(outerCircle);
    window.draw(innerCircle);
}

void generateMap(sf::RenderWindow &window, string board[3][3])
{

    int boardSquaresCentroids[3][3][2] = {
        {{200,200},{400,200},{600,200}},
        {{200,400},{400,400},{600,400}},
        {{200,600},{400,600},{600,600}},
    };

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

    
    //Draw Played Locations
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (board[row][column] == "X") {
                generateCrosses(window, boardSquaresCentroids[row][column][0], boardSquaresCentroids[row][column][1]);
            }
            if (board[row][column] == "O")
            {
                generateCircles(window, boardSquaresCentroids[row][column][0], boardSquaresCentroids[row][column][1]);
            }
        }
    }
}

int* playedCoords(sf::Event event)
{
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

    int* coords = new int[2];

    //1
    if (event.mouseButton.x > 105 && event.mouseButton.x < 295 && event.mouseButton.y > 105 && event.mouseButton.y < 295)
    {
        coords[0] = 0;
        coords[1] = 0;
        return coords;
    }

    //2
    if (event.mouseButton.x > 305 && event.mouseButton.x < 495 && event.mouseButton.y > 105 && event.mouseButton.y < 295)
    {
        coords[0] = 0;
        coords[1] = 1;
        return coords;
    }

    //3
    if (event.mouseButton.x > 505 && event.mouseButton.x < 695 && event.mouseButton.y > 105 && event.mouseButton.y < 295)
    {
        coords[0] = 0;
        coords[1] = 2;
        return coords;
    }

    //4
    if (event.mouseButton.x > 105 && event.mouseButton.x < 295 && event.mouseButton.y > 305 && event.mouseButton.y < 495)
    {
        coords[0] = 1;
        coords[1] = 0;
        return coords;
    }

    // 5
    if (event.mouseButton.x > 305 && event.mouseButton.x < 495 && event.mouseButton.y > 305 && event.mouseButton.y < 495)
    {
        coords[0] = 1;
        coords[1] = 1;
        return coords;
    }

    //6
    if (event.mouseButton.x > 505 && event.mouseButton.x < 695 && event.mouseButton.y > 305 && event.mouseButton.y < 495)
    {
        coords[0] = 1;
        coords[1] = 2;
        return coords;
    }

    //7
    if (event.mouseButton.x > 105 && event.mouseButton.x < 295 && event.mouseButton.y > 505 && event.mouseButton.y < 695)
    {
        coords[0] = 2;
        coords[1] = 0;
        return coords;
    }

    // 8
    if (event.mouseButton.x > 305 && event.mouseButton.x < 495 && event.mouseButton.y > 505 && event.mouseButton.y < 695)
    {
        coords[0] = 2;
        coords[1] = 1;
        return coords;
    }

    //9
    if (event.mouseButton.x > 505 && event.mouseButton.x < 695 && event.mouseButton.y > 505 && event.mouseButton.y < 695)
    {
        coords[0] = 2;
        coords[1] = 2;
        return coords;
    }

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
    int turn = 0;
    
    //WHILE WINDOW IS OPEN LOGIC AKA WHILE THE GAME IS RUNNING
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int* playerCoordsPlayed = 0;
                    playerCoordsPlayed = playedCoords(event);

                    string symbol = "O";
                    if (turn % 2 + 1 == 1)
                    {
                        symbol = "X";
                    }

                    board[playerCoordsPlayed[0]][playerCoordsPlayed[1]] = symbol;

                    turn++;

                    delete[] playerCoordsPlayed;
                }
            }
        }

        window.clear();
        window.draw(background);

        generateMap(window, board);

        window.display();
        
    }

    return 0;
}


