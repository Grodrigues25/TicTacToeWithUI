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
// TODO: Find a way for a player to win and then the board gets blocked, and the window does not close -> DONE
// TODO: Make a pop up square asking the player if they want to play again
// TODO: Analyse implementing replayability features, such a playing a new game after one ends
// TODO: Analyse implementing a Scoreboard
// TODO: Add a draw scenario -> DONE

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

void generateCrosses(sf::RenderWindow& window, int x, int y){
    
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

void generateCircles(sf::RenderWindow& window, int x, int y){
    
    sf::CircleShape outerCircle(60);
    outerCircle.setPosition(x-60, y-60);

    sf::CircleShape innerCircle(50);
    innerCircle.setPosition(x-50, y-50);

    outerCircle.setFillColor(sf::Color::Black);
    innerCircle.setFillColor(sf::Color::White);

    window.draw(outerCircle);
    window.draw(innerCircle);
}

void generateMap(sf::RenderWindow &window, string board[3][3]){

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
    for (int row = 0; row < 3; row++){
        for (int column = 0; column < 3; column++){
            if (board[row][column] == "X"){
                generateCrosses(window, boardSquaresCentroids[row][column][0], boardSquaresCentroids[row][column][1]);
            }
            if (board[row][column] == "O"){
                generateCircles(window, boardSquaresCentroids[row][column][0], boardSquaresCentroids[row][column][1]);
            }
        }
    }
}

void generateWinningLine(sf::RenderWindow &window, int winLocation){
    
    float length;

    winLocation >= 7 ? length = sqrt(600 * 600 + 600 * 600) : length = 600.f;

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

void generateTitle(sf::RenderWindow& window, int turn){
    
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

int* playedCoords(int clickCoords[2]){

    int* coords = new int[2];

    //1
    if (clickCoords[0] > 105 && clickCoords[0] < 295 && clickCoords[1] > 105 && clickCoords[1] < 295)
    {
        coords[0] = 0;
        coords[1] = 0;
        return coords;
    }

    //2
    if (clickCoords[0] > 305 && clickCoords[0] < 495 && clickCoords[1] > 105 && clickCoords[1] < 295)
    {
        coords[0] = 0;
        coords[1] = 1;
        return coords;
    }

    //3
    if (clickCoords[0] > 505 && clickCoords[0] < 695 && clickCoords[1] > 105 && clickCoords[1] < 295)
    {
        coords[0] = 0;
        coords[1] = 2;
        return coords;
    }

    //4
    if (clickCoords[0] > 105 && clickCoords[0] < 295 && clickCoords[1] > 305 && clickCoords[1] < 495)
    {
        coords[0] = 1;
        coords[1] = 0;
        return coords;
    }

    // 5
    if (clickCoords[0] > 305 && clickCoords[0] < 495 && clickCoords[1] > 305 && clickCoords[1] < 495)
    {
        coords[0] = 1;
        coords[1] = 1;
        return coords;
    }

    //6
    if (clickCoords[0] > 505 && clickCoords[0] < 695 && clickCoords[1] > 305 && clickCoords[1] < 495)
    {
        coords[0] = 1;
        coords[1] = 2;
        return coords;
    }

    //7
    if (clickCoords[0] > 105 && clickCoords[0] < 295 && clickCoords[1] > 505 && clickCoords[1] < 695)
    {
        coords[0] = 2;
        coords[1] = 0;
        return coords;
    }

    // 8
    if (clickCoords[0] > 305 && clickCoords[0] < 495 && clickCoords[1] > 505 && clickCoords[1] < 695)
    {
        coords[0] = 2;
        coords[1] = 1;
        return coords;
    }

    //9
    if (clickCoords[0] > 505 && clickCoords[0] < 695 && clickCoords[1] > 505 && clickCoords[1] < 695)
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

int winConditions(string board[3][3]){

    // ROWS
    if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] != " " && board[0][1] != " " && board[0][2] != " "){
        return board[0][0] == "X" ? 11 : 12;
    }
    if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] != " " && board[1][1] != " " && board[1][2] != " "){
        return board[1][0] == "X" ? 21 : 22;
    }
    if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] != " " && board[2][1] != " " && board[2][2] != " "){
        return board[2][0] == "X" ? 31 : 32;
    }

    // COLUMNS
    if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] != " " && board[1][0] != " " && board[2][0] != " "){
        return board[0][0] == "X" ? 41 : 42;
    }
    if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] != " " && board[1][1] != " " && board[2][1] != " "){
        return board[0][1] == "X" ? 51 : 51;
    }
    if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] != " " && board[1][2] != " " && board[2][2] != " "){
        return board[0][2] == "X" ? 61 : 62;
    }

    //DIAGONALS
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != " " && board[1][1] != " " && board[2][2] != " "){
        return board[0][0] == "X" ? 71 : 72;

    }
    if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != " " && board[1][1] != " " && board[0][2] != " "){
        return board[2][0] == "X" ? 81 : 82;
    }

    return 0;
}

int roundEnded(sf::RenderWindow& window, int winCode, int turn){
    
    if (turn == 9){
        cout << "It's a Draw!" << endl;
        return -1;
    }

    int divisor = 10;
    int winLine = (int)winCode / divisor;
    int winningPlayer = winCode % divisor;
    generateWinningLine(window, winLine);

    if (winningPlayer == 1){
        cout << "Player 1 Wins!! " << endl;
        return 0;
    }
    else if (winningPlayer == 2){
        cout << "Player 2 Wins!! " << endl;
        return 1;
    }
}

void generatePlayAgainBox(sf::RenderWindow& window){

    sf::Text playAgainQuestion;
    sf::Text Yes;
    sf::Text No;
    sf::Font font;
    font.loadFromFile("C:\\Users\\gonca\\source\\repos\\sfmltest\\include\\fonts\\Coffee Fills.ttf");

    sf::RectangleShape boxOutline(sf::Vector2f(500, 240));
    boxOutline.setPosition(150, 250);
    boxOutline.setFillColor(sf::Color::Black);

    sf::RectangleShape boxContents(sf::Vector2f(490, 230));
    boxContents.setPosition(155, 255);
    boxContents.setFillColor(sf::Color::White);

    sf::RectangleShape yesBoxOutline(sf::Vector2f(70, 50));
    yesBoxOutline.setPosition(300, 375);
    yesBoxOutline.setFillColor(sf::Color::Black);

    sf::RectangleShape yesBoxContents(sf::Vector2f(66, 46));
    yesBoxContents.setPosition(302, 377);
    yesBoxContents.setFillColor(sf::Color::White);

    sf::RectangleShape noBoxOutline(sf::Vector2f(70, 50));
    noBoxOutline.setPosition(425, 375);
    noBoxOutline.setFillColor(sf::Color::Black);

    sf::RectangleShape noBoxContents(sf::Vector2f(66, 46));
    noBoxContents.setPosition(427, 377);
    noBoxContents.setFillColor(sf::Color::White);

    playAgainQuestion.setFont(font);
    playAgainQuestion.setString("Would like to play again?");
    playAgainQuestion.setCharacterSize(30); // in pixels, not points!
    playAgainQuestion.setFillColor(sf::Color::Black);
    playAgainQuestion.setStyle(sf::Text::Bold | sf::Text::Underlined);
    playAgainQuestion.setPosition(210, 300);

    Yes.setFont(font);
    Yes.setString("Yes");
    Yes.setCharacterSize(30); // in pixels, not points!
    Yes.setFillColor(sf::Color::Black);
    Yes.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Yes.setPosition(312, 380);
    
    No.setFont(font);
    No.setString("No");
    No.setCharacterSize(30); // in pixels, not points!
    No.setFillColor(sf::Color::Black);
    No.setStyle(sf::Text::Bold | sf::Text::Underlined);
    No.setPosition(442, 380);

    window.draw(boxOutline);
    window.draw(boxContents);
    window.draw(playAgainQuestion);
    window.draw(yesBoxOutline);
    window.draw(yesBoxContents);
    window.draw(Yes);
    window.draw(noBoxOutline);
    window.draw(noBoxContents);
    window.draw(No);
}

int main(){

    // SETTINGS
    int windowSize = 800;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowSize, 1000), "TicTacToe", sf::Style::Close, settings);
    sf::RectangleShape background(sf::Vector2f(windowSize, 1000));
    background.setFillColor(sf::Color::White);
    window.setVerticalSyncEnabled(true);

    //GAME DATA STRUCTURES
    string board[3][3] = { {" "," "," "},{" "," "," "},{" "," "," "} };
    int winCode = 0;
    int turn = 0;
    int intDiv[2] = { 0,0 };
    int score[2] = {0,0};
    int leftMouseClickCoords[2] = { 0,0 };
    bool gameRunning = true;
    
    //WHILE WINDOW IS OPEN LOGIC AKA WHILE THE GAME IS RUNNING
    while (window.isOpen() && gameRunning){
        sf::Event event;

        while (window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:

                    if (event.mouseButton.button == sf::Mouse::Left){                    
                        leftMouseClickCoords[0] = event.mouseButton.x;
                        leftMouseClickCoords[1] = event.mouseButton.y;                        
                    }
                    break;
            }

        }

        window.clear();
        window.draw(background);

        generateTitle(window, turn);
        generateMap(window, board);

        // WinCode == 0 means no player has still won the game
        if (winCode == 0){
            int* playerCoordsPlayed = 0;
            playerCoordsPlayed = playedCoords(leftMouseClickCoords);

            if (playerCoordsPlayed[0] != -1 && board[playerCoordsPlayed[0]][playerCoordsPlayed[1]] == " "){
                // Ternary operator "Boolean operation" ? result if true : result if false;
                string symbol = turn % 2 + 1 == 1 ? "X" : "O";
                board[playerCoordsPlayed[0]][playerCoordsPlayed[1]] = symbol;

                turn++;
            }

            delete[] playerCoordsPlayed;
        }

        // Check if a player has won after the last play
        winCode = winConditions(board);

        if (winCode > 0){
            int winningPlayer = roundEnded(window, winCode, turn);
            // -1 means draw
            if (winningPlayer != -1){
                score[winningPlayer]++;
            }

            generatePlayAgainBox(window);
        }        

        window.display();
        
    }

    return 0;
}
