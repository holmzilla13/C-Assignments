#include "connectfour.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();

    // call function playGame
    playGame();

    // program executed successfully
    return 0;
}

// welcomeScreen function displays the Connect Four logo and rules of the game
void welcomeScreen ()
{
	printf (" CCCC  OOOO   N    N  N    N EEEEE  CCCC TTTTT   FFFFF  OOOO   U    U  RRRR  \n");
	printf ("C     O    O  N N  N  N N  N EE    C       T     F     O    O  U    U  R   R \n");
	printf ("C     O    O  N  N N  N  N N EEEE  C       T     FFF   O    O  U    U  R  R  \n");
	printf ("C     O    O  N   NN  N   NN EE    C       T     F     O    O  U    U  R R   \n");
	printf (" CCCC  OOOO   N    N  N    N EEEEE  CCCC   T     F      OOOO    UUUU   R   R \n");
	printf ("\n");
	printf ("CONNECT FOUR GAME RULES\n\n");
    printf("\t 1. The board is 6 rows and 7 columns.\n");
    printf("\t 2. The player with the yellow discs goes first.\n");
    printf("\t 3. Players drop 1 disc in the grid at a time.\n");
    printf("\t 4. Players alternate turns.\n");
    printf("\t 5. Once a player has four discs in a row vertically, horizontally or diagonally, they have won the game!\n");
}

// function displayEmptyBoard displays a hardcoded version of an Connect Four board
void displayEmptyBoard()
{
    printf("|------------------------------------------\n");
    printf("|  A  |  B  |  C  |  D  |  E  |  F  |  G  |\n");
    printf("|------------------------------------------\n");
    printf("|------------------------------------------\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|------------------------------------------\n");
 }

 void playGame()
{
    // declare variable for each player as a struct
    struct Player yellow;
    struct Player red;

    // yellow (Y) always goes first
    int currentPlayer = YELLOW;
    int loop = ZERO;

    char board[ROW][COL]; // this is really a memory location of board[0][0]

    // create struct for each player
    printf("Player Yellow, please enter your name\n");
    scanf("%s", yellow.playerName);
    yellow.playerNum = YELLOW;
    yellow.playChar = 'Y';
    yellow.numDisc = DISC;

    printf("Player Red, please enter your name\n");
    scanf("%s", red.playerName);
    red.playerNum = RED;
    red.playChar = 'R';
    red.numDisc = DISC;

    printf("%s and %s, let's play Connect Four!\n", yellow.playerName, red.playerName);

    // call function initializeBoard
    initializeBoard(board);

    displayBoard(board);

    while(gameOver(board, yellow, red) == FALSE)
    {
        
        // switch players for each move
        if(currentPlayer == YELLOW)
        {
            makeMove(&yellow, board);

            // switch players
            currentPlayer = RED;
        }
        else if(currentPlayer == RED)
        {
            makeMove(&red, board);

            currentPlayer = YELLOW;
        }

        displayStats(yellow);
        displayStats(red);
        // call function displayBoard
        displayBoard(board);


        loop++;
    }
    displayGameOver();
}

void initializeBoard(char board[ROW][COL])
{
    for(int row = 0; row < ROW; row++)
    {
        for(int col = 0; col < COL; col++)
        {
            board[row][col] = SPACE;
        }
    }
}

void displayBoard(char board[ROW][COL])
{
    printf("|-----------------------------------------|\n");
    printf("|  A  |  B  |  C  |  D  |  E  |  F  |  G  |\n");
    printf("|-----------------------------------------|\n");

    for(int row = 0; row < ROW; row++)
    {
        printf("|-----------------------------------------|\n");
        printf("|");

        for(int col = 0; col < COL; col++)
        {
            printf("  %c  |", board[row][col]);
        }

        printf("\n");
    }

    printf("|-----------------------------------------|\n");
}

void makeMove(struct Player *player, char board[ROW][COL])
{
    char move[TWO]; // A
    int valid = FALSE;

    // loop until the player enters a valid move
    while(valid == FALSE)
    {
        printf("%s, enter the column to place disc (e.g. B)\n", player->playerName);
        scanf("%s", move);
        printf("%s, you entered %s\n\n", player->playerName, move);

        int length = (int)strlen(move);

        if(length == ONE && getMoveCol(move) != INVALID &&
           isColFull(move, board) == FALSE)
        {
            valid = TRUE;
            updateBoard(move, board, player);
        }
        else
            valid = FALSE;

        if(valid == FALSE)
            printf("Invalid move, try again\n\n");
    }
}

int getMoveCol(char move[TWO])
{
    // initialize to an invalid value
    int colInt = INVALID;
    // use the array to get the index value for the board array row
    //              0    1    2    3    4    5    6
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    for(int col = 0; col < COL; col++)
    {
        // convert the first character to upper case
        if(toupper(move[ZERO]) == cols[col])
            colInt = col;
    }

    return colInt;
}

void displayStats(struct Player player)
{
    printf("****** %s's Statistics ******\n", player.playerName);
    printf("Player number:    %d\n", player.playerNum);
    printf("Player character: %c\n", player.playChar);
    printf("Player discs:  %d\n\n", player.numDisc);
}

int isColFull(char move[TWO], char board[ROW][COL])
{
    int full = FALSE;
    int count = 0;

    // get the index for the board column to check the array
    int col = getMoveCol(move);

    for(int row = 0; row < ROW; row++)
    {
        if(board[row][col] != SPACE)
            count++;
    }

    if(count == ROW)
    {
        full = TRUE;
        printf("\n Column is full!\n");
    }
    else
        full = FALSE;

    return full;
}

void updateBoard(char move[TWO], char board[ROW][COL], struct Player *player)
{
    // move col
    int col = getMoveCol(move);

    // find the last empty row in the array and store the player's character
    for(int row = (ROW - 1); row >= ZERO; row--)
    {
        if(board[row][col] == SPACE)
        {
            board[row][col] = player->playChar;
            player->numDisc--;
            break;
        }
    }
}

int gameOver(char board[ROW][COL], struct Player yellow, struct Player red)
{
    int over = FALSE;

    if(yellow.numDisc == ZERO || red.numDisc == ZERO)
        over = TRUE;
    else if(checkWin(board))
        over = TRUE;
    else
        over = FALSE;

    return over;
}

int checkHorizontal(char board[ROW][COL]){
    // Checks through array horizontally
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col <= COL -4; col++){
            // Checks for 4 consecutive disks
            if (board[row][col] == board[row][col +1] &&
                board[row][col] == board[row][col +2] &&
                board[row][col] == board[row][col +3] &&
                (board[row][col] == 'Y' || board[row][col] == 'R')
            ){
                return TRUE;
            }

        }
    }return FALSE;
}

int checkVertical(char board[ROW][COL]){
    // Checks through array vertically
    for (int col = 0; col < COL; col++){
        for (int row = 0; row <= ROW -4; row++){
            // Checks for 4 consecutive discs
            if (board[row][col] == board[row + 1][col] &&
                board[row+1][col] == board[row + 2][col] &&
                board[row+2][col] == board[row + 3][col] &&
                (board[row][col] == 'Y' || board[row][col] == 'R')){
                    return TRUE;
                }
            
        }
    }
    return FALSE;
}

int checkDiagonal(char board[ROW][COL]){
    // Checks board from top left to bottom right
    for (int row = 0; row <= ROW -4; row++){
        for(int col = 0; col <= COL -4; col++){
            //Checks for 4 consecutive discs
            if (board[row][col] == board[row + 1][col + 1] &&
                board[row+1][col+1] == board[row + 2][col + 2] &&
                board[row+2][col+2] == board[row + 3][col + 3] &&
                (board[row][col] == 'Y' || board[row][col] == 'R')
            ){
                return TRUE;
            }
        }
    }

    // Checks board from bottom left to top right
    for (int row = ROW - 1; row >=3; row--){
        for (int col = 0; col <= COL -4; col++){
            // Checks for four consecutive discs
            if (board[row][col] == board[row - 1][col + 1] &&
                board[row - 1][col + 1] == board[row - 2][col + 2] &&
                board[row - 2][col + 2] == board[row - 3][col + 3] &&
                (board[row][col] == 'Y' || board[row][col] == 'R')
            ){
                return TRUE;
        }
    }
}
    return FALSE;
}
int checkWin(char board[ROW][COL])
{
    int win = FALSE;

    if (checkHorizontal(board) == TRUE ||
        checkVertical(board) == TRUE ||
        checkDiagonal(board) == TRUE){
            win = TRUE;
        }

    return win;
}

void displayGameOver(void){
    printf("\n********* GAME OVER *********\n");
    printf("Thank you for playing Connect Four!\n");
}

