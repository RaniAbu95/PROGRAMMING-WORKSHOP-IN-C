/**
 * @file Gomoku.c
 * @author  rani.aboraya
 * @date 25 Nov 2015
 *
 * @brief driver for Board
 *	 
 *
 *
 * @section DESCRIPTION
 *  Gomoku game
 * 
 */

// ------------------------------ includes ------------------------------
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>            /* For exit */
#include "Board.h"
#define ARGUMENTS_NUM 3 
#define ONE '1'
#define TWO '2'
#define THREE '3'
#define FOUR '4'
#define X 'X'
#define O 'O'
#define GOOD_FORMAT 3 
#define NO_WINNER ' '

/**
* @brief check the legability of the program's argument
* @param numOfArgs The number of arguments that the game takes
* @param inputFile A pointer for a file that we are reading from
* @param outputFile A pointer for a file that prints the output of the game
* @return true if the program takes legal arguments, false otherwise.
*/
static bool checkLegalArgs(int numOfArgs, FILE *inputFile, FILE *outputFile)
{
    if(numOfArgs != ARGUMENTS_NUM)
    {
        fprintf(outputFile, "Wrong parameters. Usage: \n Gomoku <input_file> <output_file>");
        return false;
    }
    else if(inputFile == NULL)
    {
        fprintf(outputFile, "Can not open file: <file_name>\n");
        return false;
    }
    return true;
}

/**
* @brief check if the command that the player entered is legal
* @param row The current row in the file
* @param curX The current x coordinate in the board 
* @param curY The current y coordinate in the board 
* @param firstInput The first input in the file 
* @param secondInput The second input in the file
* @param inputFile A pointer for a file that we are reading from
* @param outputFile A pointer for a file that prints the output of the game
* @return true if the command is legal, false otherwse
*/
static bool checkCommand(int row, int curX, int curY, char firstInput, char secondInput, FILE *outputFile, BoardP theBoard)
{
    if(firstInput == EOF)
    {
        if(row > 0)
        {
           printBoard(outputFile, theBoard, curX, curY);
           fprintf(outputFile, "The game ended with a tie...\n");
           return false;
        }        
        fprintf(outputFile, "illegal command at line %d\n", row);
        return false;
    }
    if(((firstInput < ONE) || (firstInput > FOUR)) || ((secondInput != '\n') && (secondInput != EOF)))
    {
        row++;
        fprintf(outputFile, "illegal command at line %d\n", row);
        return false;
    }
    return true;
}

/**
* @brief A function that is responsible for exiting the game and to free all the allocated memmory
* @brief and to close all the opened files
* @param theBoard A pointer for the game Board
* @param inputFile A pointer for a file that we are reading from
* @param outputFile A pointer for a file that prints the output of the game
*/
static void exitGame(BoardP theBoard, FILE *inputFile, FILE *outputFile)
{
    freeBoard(theBoard); 
    fclose(inputFile);
    fclose(outputFile);
}

/**
* @brief The main function
* @param argc The number of the arguments that the program takes
* @param argv An array that contains all the arguments 
* @return Return 0 if the the game ended
* @output Prints the last situation of the board.
*/
int main(int argc, char** argv)
{
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w+");
    int curY = 0, curX = 0, row = 0;
    bool moveSucc;
    BoardP theBoard = createNewDefaultBoard();
    char currentPlayer = X;
    if(theBoard == NULL) 
    {
		return 0;
	}
    if(!checkLegalArgs(argc, inputFile, outputFile))
    {
        return 0;
    }
    int getX, getY;
    char secondInput, firstInput, newRow;
    while(1)
    {
        firstInput = fgetc(inputFile);
        secondInput = fgetc(inputFile);
        if(!checkCommand(row, curX, curY, firstInput, secondInput, outputFile, theBoard))
        {
            break;
        }
        row++;
        
        if(firstInput == FOUR)
        {
            printBoard(outputFile, theBoard, curX, curY);
            fprintf(outputFile, "The game ended with a tie...\n");
            break;
        }
        if(fscanf(inputFile, "(%d,%d)%c", &getX, &getY, &newRow) != GOOD_FORMAT || newRow != '\n')
        {
            row++;
            fprintf(outputFile, "Wrong format input file at %d\n", row);
            break;
        }
        
        row++;
        
        if(firstInput == ONE)
        {
            moveSucc = putBoardSquare(theBoard, getX, getY, currentPlayer);
        }
        if(firstInput == TWO)
        {
            moveSucc = cancelMove(theBoard, getX, getY);
        }
        if((firstInput == ONE || firstInput == TWO) && moveSucc)
        {
            // the player end his turn
            if (currentPlayer == X)
            {
               currentPlayer = O;
            }
            else
            {
               currentPlayer = X;
            }
        }
        if(firstInput == THREE)
        {
            curX = getX;
            curY = getY;
        }
        
        if (getWinner(theBoard) != NO_WINNER)
        {
            printBoard(outputFile, theBoard, curX, curY);
            fprintf(outputFile, "\n\n%c wins the game!!!\n\n", getWinner(theBoard));
            break;
        }
    }
    exitGame(theBoard, inputFile, outputFile);
    return 0;
}
       
