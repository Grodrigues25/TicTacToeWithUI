#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// TODO: Check why game breaks when clicking on a position that is not a playable square -> DONE AND FIXED
// TODO: Include checks to see if the played location is valid -> DONE
// TODO: Include an header to display which player's turn it is to play -> DONE
// TODO: Include a title -> DONE
// TODO: Check what adaptations I need to do for the game to work in different window sizes -> POSTPONED -> https://www.sfml-dev.org/tutorials/2.2/graphics-view.php#showing-more-when-the-window-is-resized
// TODO: Include win condition checks -> DONE
// TODO: Block playability when a player wins -> DONE
// TODO: Draw a line on the winning line -> DONE
// TODO: Check if diagonal line definitions in the win conditions and the drawWinnningLine functions match -> DONE
// TODO: Calculate length of diagonal lines so that they can go completely accross -> DONE
// TODO: Cleanup Code -> IN PROGRESS
// TODO: Analyse implementing replayability features, such a playing a new game after one ends
// TODO: Analyse implementing a Scoreboard
// TODO: Add a draw scenario -> IN PROGRESS

/*
    1|2|3
    -|-|-
    4|5|6
    -|-|-
    7|8|9

Squares Centroids
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

    
    //Draw Played Locations by walking through the array containing board information
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

void generateWinningLine(sf::RenderWindow &window, int winLocation) 
{
    float length;

    if (winLocation >= 7)
    {
        length = sqrt(600*600+600*600);
    }
    else
    {
        length = 600.f;
    }

    sf::RectangleShape winningLine(sf::Vector2f(length, 10.f));
    winningLine.setFillColor(sf::Color::Green);

    switch (winLocation) {
        case 1:
            //top horizontal line
            winningLine.setPosition(100, 200);
            break;

        case 2:
            //middle horizontal line
            winningLine.setPosition(100, 400);
            break;

        case 3:
            //bottom horizontal line
            winningLine.setPosition(100, 600);
            break;
            
        case 4:
            //left vertical line
            winningLine.setPosition(200, 100);
            winningLine.rotate(90.f);
            break;

        case 5:
            //middle vertical line
            winningLine.setPosition(400, 100);
            winningLine.rotate(90.f);
            break;

        case 6:
            //right vertical line
            winningLine.setPosition(600, 100);
            winningLine.rotate(90.f);
            break;

        case 7:
            //diagonal top left to bottom right
            winningLine.setPosition(100, 100);
            winningLine.rotate(45.f);
            break;

        case 8:
            //diagonal top right to bottom left
            winningLine.setPosition(700, 100);
            winningLine.rotate(135.f);
            break;
    }

    window.draw(winningLine);

}

void generateTitle(sf::RenderWindow& window, int turn) 
{
    
    sf::Text title;
    sf::Text playerToPlay;
    sf::Font font;

    // "TIC TAC TOE" Title
    font.loadFromFile("C:\\Users\\gonca\\source\\repos\\sfmltest\\include\\fonts\\Coffee Fills.ttf");
    title.setFont(font); 
    title.setString("Tic Tac Toe");
    title.setCharacterSize(48); // in pixels, not points!
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setPosition(275, 25);

    // Player turn text and winning player text
    playerToPlay.setFont(font);
    playerToPlay.setCharacterSize(48); // in pixels, not points!
    playerToPlay.setFillColor(sf::Color::Black);
    playerToPlay.setStyle(sf::Text::Bold | sf::Text::Underlined);
    playerToPlay.setPosition(260, 800);

    turn % 2 == 0 ? playerToPlay.setString("Crosses Turn!") : playerToPlay.setString("Circles Turn!");
    
    // inside the main loop, between window.clear() and window.display()
    window.draw(title);
    window.draw(playerToPlay);

}

int* playedCoords(sf::Event event)
{

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

    // If player clicks on any place outside the valid squares
    coords[0] = -1;
    coords[1] = -1;
    return coords;
}

int winConditions(string board[3][3])
{
    // ROWS
    if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] != " " && board[0][1] != " " && board[0][2] != " ")
    {
        if (board[0][0] == "X") { return 11; }
        else { return 12; }
    }
    if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] != " " && board[1][1] != " " && board[1][2] != " ")
    {
        if (board[1][0] == "X") { return 21; }
        else { return 22; }
    }
    if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] != " " && board[2][1] != " " && board[2][2] != " ")
    {
        if (board[2][0] == "X") { return 31; }
        else { return 32; }
    }

    // COLUMNS
    if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] != " " && board[1][0] != " " && board[2][0] != " ")
    {
        if (board[0][0] == "X") { return 41; }
        else { return 42; }
    }
    if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] != " " && board[1][1] != " " && board[2][1] != " ")
    {
        if (board[0][1] == "X") { return 51; }
        else { return 52; }
    }
    if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] != " " && board[1][2] != " " && board[2][2] != " ")
    {
        if (board[0][2] == "X") { return 61; }
        else { return 62; }
    }

    //DIAGONALS
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != " " && board[1][1] != " " && board[2][2] != " ")
    {
        if (board[0][0] == "X") { return 71; }
        else { return 72; }
    }
    if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != " " && board[1][1] != " " && board[0][2] != " ")
    {
        if (board[2][0] == "X") { return 81; }
        else { return 82; }
    }

    return 99;
}

int main()
{
    // SETTINGS
    int windowSize = 800;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowSize, 1000), "TicTacToe", sf::Style::Close, settings);
    sf::RectangleShape background(sf::Vector2f(windowSize, 1000));
    background.setFillColor(sf::Color::White);

    //GAME DATA STRUCTURES
    string board[3][3] = { {" "," "," "},{" "," "," "},{" "," "," "} };
    int winStatus;
    int turn = 0;
    int intDiv[2] = { 0,0 };
    
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

                        if (playerCoordsPlayed[0] != -1 && board[playerCoordsPlayed[0]][playerCoordsPlayed[1]] == " ")
                        {
                            // Ternary operator "Boolean operation" ? result if true : result if false;
                            string symbol = turn % 2 + 1 == 1 ? "X" : "O";
                            board[playerCoordsPlayed[0]][playerCoordsPlayed[1]] = symbol;
                            turn++;
                        }

                        delete[] playerCoordsPlayed;
                    }
                    break;
            }

        }

        window.clear();
        window.draw(background);

        generateTitle(window, turn);
        generateMap(window, board);

        int winCode = winConditions(board);

        if (winCode != 0)
        {
            int divisor = 10;
            int winLine = (int)winCode / divisor;
            int winningPlayer = winCode % divisor;
            generateWinningLine(window, winLine);
            window.display();

            if (winningPlayer == 1)
            {
                cout << "Player 1 Wins!! " << endl;
                //score[0]++;
                break;
            }
            else if (winningPlayer == 2)
            {
                cout << "Player 2 Wins!! " << endl;
                //score[1]++;
                break;
            }
        }

        window.display();
        
    }

    return 0;
}


