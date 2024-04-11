/**
 * @file Board.c
 * @author  rani.aborayas
 * @version 1.0
 * @date 25 Nov 2015
 *
 * @brief Board implement an interface for Gomoku game.
 *
 *
 *
 * @section DESCRIPTION
 * @brief Board  interface for Gomoku game.
*/


#define BOARD_H

// ------------------------------ includes ------------------------------
#include <stdbool.h>
#include <stdio.h>
#include "ErrorHandle.h"
#include "Board.h"
#include <stdlib.h>
// --------------------------  definitions -------------------------
#define DEFAULT_ROWS 10
#define DEFAULT_COLOMNS 10
#define ERROR 'E'
#define EMPTY_SQUARE ' '
#define X_MOVE 'X'
#define O_MOVE 'O'
#define X_PLAYER 'X'
#define O_PLAYER 'O'
#define LEGAL_SEQUANCES 4
#define SEQUANCE_LENGTH 5
#define INCREASE_FACTOR 2
#define VERTICAL 0
#define HORIZONAL 1
#define DIAGONAL_RIGHT 2
#define DIAGONAL_LEFT 3
#define COLOMNS_NUM 10
#define SEQUANCE_RADIUS 4

//A struct that defines the Board game
typedef struct Board
{
    int _rows;
    int _colomns;
    char _curPlayer;
    int _lastMove_X_Coordinate;
    int _lastMove_Y_Coordinate;
    char **_arr;
}Board;

 /**
  * A pointer to Gomoku table.
 */

typedef struct Board* BoardP;

/**
* A struct of a Gomoku table.
*/

typedef const struct Board* ConstBoardP;


//free the two-dimential array that is in the struct
void freeArray(BoardP board , int lastAllocatedRow)
{
    int i;
    for(i = 0; i < lastAllocatedRow; i++)
    {
        free(board->_arr[i]);
        board->_arr[i] = NULL;
    }
    free(board->_arr);
    board->_arr = NULL;
    
}

//a helper func for freeBoard
void freeBoardHelper(BoardP board, int lastAllocatedRow)
{
    freeArray (board, lastAllocatedRow);
    free(board);
    board = NULL;
}


/**
* Free all the memory allocated for the board. It's the user responsibility to call this function before
* exiting the program.
*/
void freeBoard(BoardP board)
{
    freeBoardHelper(board, board ->_rows);
}

/**
* create new array for the board based on the given rows and colomns.
*/
BoardP createNewArray(BoardP theBoard, int rows, int cols)
{
    int i, j;
    freeArray(theBoard, theBoard->_rows);
    theBoard->_rows = rows;
    theBoard->_colomns = cols;
    theBoard->_arr = (char**)malloc(rows * sizeof(char*));
    if(theBoard->_arr == NULL)
    {
        freeBoardHelper(theBoard, 0);
        return NULL;
    }
    for(i = 0; i < theBoard->_rows; i++)
    {
        theBoard->_arr[i] = (char*)malloc(cols * sizeof(char));
        if(theBoard->_arr[i] == NULL)
        {
            freeBoardHelper(theBoard, i);
            return NULL;   
        }
        for(j = 0; j < theBoard->_colomns; j++)
        {
            theBoard->_arr[i][j] = EMPTY_SQUARE;
        }
    }
    return theBoard;
}


/**
 * Allocate memory for an empty board (size rows X cols) and return it.
 * If run out of memory, free all the memory that was allocate, report error MEM_OUT and return NULL.
 */
BoardP createNewBoard(int rows, int cols)
{
    int i, j;
    BoardP theBoard = (Board*)malloc(sizeof(Board));
    if(theBoard == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    theBoard->_rows = rows;
    theBoard->_colomns = cols;
    theBoard->_curPlayer = 'X';

    theBoard->_arr = (char**)malloc(rows * sizeof(char*));
    if(theBoard->_arr == NULL)
    {
        freeBoardHelper(theBoard, 0);
        return NULL;
    }
    for(i = 0; i < rows; i++)
    {
        theBoard->_arr[i] = (char*)malloc(cols * sizeof(char));
        if(theBoard->_arr[i] == NULL)
        {
            freeBoardHelper(theBoard, i);
            return NULL;   
        }
        for(j = 0; j < theBoard->_colomns; j++)
        {
            theBoard->_arr[i][j] = EMPTY_SQUARE;
        }
    }
    return theBoard;
}

/**
 * Allocate memory for a default empty board (size 10X10) and return it.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */
BoardP createNewDefaultBoard()
{
    
    BoardP theBoard = createNewBoard(DEFAULT_ROWS, DEFAULT_COLOMNS);
    return theBoard;
}

/**
 * Duplicate the original board and return a new one.
 * The old board stays exactly the same (its memory is not freed etc).
 * In case the function runs out of memory while creating the new board:
 * MEM_OUT error is reported.
 * The old board stays the same.
 * You should free all the memory that was already allocated for the new board.
 * NULL is returned.
 */
BoardP duplicateBoard(ConstBoardP originalBoard)
{
    int i, j;
    if(originalBoard == NULL)
    {
        return NULL;
    }
    BoardP duplicatedBoard = createNewBoard(originalBoard->_rows, originalBoard->_colomns);
    if(duplicatedBoard == NULL)
    {
        return NULL;
    }
    duplicatedBoard->_rows = originalBoard->_rows;
    duplicatedBoard->_colomns = originalBoard->_colomns;
    duplicatedBoard->_curPlayer = originalBoard->_curPlayer;
    for(i = 0; i < duplicatedBoard->_rows; i++)
    {
        for(j = 0; j < duplicatedBoard->_colomns; j++)
        {
            duplicatedBoard->_arr[i][j] = originalBoard->_arr[i][j];
        }
    }
    return duplicatedBoard;
}


/**
 * Check the value of the square row,col on the board. Assume the squares index is starting from zero.
 * Return 'X' if X player owns the square, 'O' (big o, not a zero) if O player owns the square, and ' ' (a space) if it's an empty square.
 * If row or col are negative, report an error OUT_OF_BOUND and return 'E'.
 * If (row,col) is out of the current memory allocated area, then it must be an empty square - return ' ' (a space).
 */
char getBoardSquare(ConstBoardP theBoard, int row, int col)
{
    if(theBoard == NULL)
    {
        return ERROR;
    }

    if((row < 0) || (col < 0))
    {
        reportError(MEM_OUT);
        return ERROR;
    }

    else if((row >= theBoard->_rows) || (col >= theBoard->_colomns))
    {
        return EMPTY_SQUARE;
    }
    else
    {
        return theBoard->_arr[row][col];
    }
}

/**
 *changing the players turns.
 */
static void changePlayersTurns(BoardP theBoard, char curPlayerTurn)
{

    
    if(curPlayerTurn == X_PLAYER)
    {
        theBoard->_curPlayer = O_PLAYER;
    }
    else
    {
        theBoard->_curPlayer = X_PLAYER;
    }

}



/**
 * make the required change for the board's array in case that the player want to mark legal square
 * that is out of the allocated memmory.
 */
static BoardP boardResizing(BoardP theBoard, int row, int col)
{
    int newRows = theBoard->_rows, newColomns = theBoard->_colomns;
    int i, j;
    BoardP tempBoard;
    if((row >= theBoard->_rows) && (col < theBoard->_colomns))
    {
        newRows = row * INCREASE_FACTOR;
    }
    else if((row < theBoard->_rows) && (col >= theBoard->_colomns))
    {
        newColomns = col * INCREASE_FACTOR;
    }
    else
    {
        newRows = row * INCREASE_FACTOR;
        newColomns = col * INCREASE_FACTOR;
    }
    tempBoard = duplicateBoard(theBoard);
    if(createNewArray(theBoard, newRows, newColomns) == NULL)
    {
        
        freeBoardHelper(tempBoard, tempBoard->_rows);
        reportError(MEM_OUT);
        return NULL;
    }
    
    for(i = 0; i < tempBoard->_rows; i++)
    {
        for(j = 0; j < tempBoard->_colomns; j++)
        {
            theBoard->_arr[i][j] = tempBoard->_arr[i][j];
        }
    }
    freeBoardHelper(tempBoard, tempBoard->_rows);
    return theBoard;
}

/**
 * Make a move: mark on location (row,col) the value 'val'.
 * If 'val' is not 'X' or 'O', report BAD_VAL and do nothing.
 * If row or col are negative report OUT_OF_BOUND and do nothing.
 * If square (row,col) is already full, report SQUARE_FULL and do nothing.
 * If val is 'X' but it's 'O' turn (or val is 'O' but it's 'X' turn) - report WRONG_TURN and do nothing.
 * If sqaure (row,col) is out of the current memory area - increase the size of the required dimension(s)
 * 	to make the move possible.
 * If run out of memory during the allocation, report MEM_OUT and do nothing
 *		(i.e. - the board should stay at the same situation as it was before the function call).
 * If everything is OK, return true. Otherwise (an error accure) return false.
 */
bool putBoardSquare(BoardP theBoard, int row, int col, char val)
{
    char squarePosition;
    if(theBoard == NULL)
    {
        return false;
    }
    else if((val != X_MOVE) && (val != O_MOVE))
    {
        reportError(BAD_VAL);
        return false;
    }

    else if( ((val == O_MOVE) && (theBoard->_curPlayer == X_PLAYER)) || ((val == X_MOVE) && (theBoard->_curPlayer == O_PLAYER)) )
    {
        reportError(WRONG_TURN);
        return false;
    }
    squarePosition = getBoardSquare(theBoard, row, col);
    if(squarePosition == ERROR)
    {
        return false;
    }
    else if(squarePosition != EMPTY_SQUARE)
    {
        reportError(SQUARE_FULL);
        return false;
    }
    else if((squarePosition == EMPTY_SQUARE) && ((row >= theBoard->_rows) || (col >= theBoard->_colomns)))
    {
        if(boardResizing(theBoard, row, col) == NULL)
        {
            return false;
        }
    }
    theBoard->_arr[row][col] = val;
    theBoard->_lastMove_X_Coordinate = row;
    theBoard->_lastMove_Y_Coordinate = col;
    changePlayersTurns(theBoard, theBoard->_curPlayer);
    return true;
}

/**
* Cancel a move (not necessarily the last move) - turn the square back to be empty.
* If X or Y are negative, report OUT_OF_BOUND and do nothing.
* If square (X,Y) is already empty, report ILLEGAL_CANCELLATION.
* If canceling the move will result with more 'O' than 'X'es on the board, or if cancelling the move will
* result with two more 'X'es on the board than 'O', report ILLEGAL_CANCELLATION and do nothing.
* If everything is OK, return true. Otherwise (an error accure) return false.
*/
bool cancelMove(BoardP theBoard, int x, int y)
{
    char squarePosition;
    if(theBoard == NULL)
    {
        return false;
    }

    squarePosition = getBoardSquare(theBoard, x, y);

    if(squarePosition == ERROR)
    {
        return false;
    }
    else if(squarePosition == EMPTY_SQUARE)
    {
        reportError(ILLEGAL_CANCELLATION);
        return false;
    }
    else if(theBoard->_curPlayer == squarePosition)
    {
        reportError(ILLEGAL_CANCELLATION);
        return false;
    }
    theBoard->_arr[x][y] = EMPTY_SQUARE;
    theBoard->_lastMove_X_Coordinate = x;
    theBoard->_lastMove_Y_Coordinate = y;
    changePlayersTurns(theBoard, theBoard->_curPlayer);
    return true;
}
/**
 * checks if the given row and col is in the bounds of the allocated memmory and if they are 
 * positives numbers 
 */
static bool inBounds(ConstBoardP theBoard, int row, int col)
{
    if(theBoard == NULL)
    {
        return false;
    }
	if(row < 0 || row >= theBoard->_rows || col < 0 || col >= theBoard->_colomns)
    {
        return false;
    }
	return true;
}

/**
 * checks if there is a winning sequance (a sequance of 5 square for the same player)
 */
static bool checkSequance(ConstBoardP board, int row, int col, int sequanceToCheck, char val)
{
    int i, sequanceCounter = 0, flag = 0, tempRow = row, tempCol = col;
    if(board == NULL)
    {
        return false;
    }
    for(i = 0; i < (SEQUANCE_LENGTH * 2) - 1; i++)
    {
        if(sequanceToCheck == VERTICAL)
        {
            if(inBounds(board, row, col) == false)
            {
                sequanceCounter = 0;
                flag = 1;
            }
            else
            {
                flag = 0;
            }
            tempRow = row;
            tempCol = col;
            row++;    
                                    
        }
        else if(sequanceToCheck == HORIZONAL)
        {
            if(inBounds(board, row, col) == false)
            {
                sequanceCounter = 0;
                flag = 1;
            }
            else
            {
                flag = 0;
            }
            tempRow = row;
            tempCol = col;    
            col++;
        }
        else if(sequanceToCheck == DIAGONAL_RIGHT)
        {
            if(inBounds(board, row, col) == false)
            {
                sequanceCounter = 0;
                flag = 1;
            }
            else
            {
                flag = 0;
            }
            tempRow = row;
            tempCol = col;
            row++;
            col--;
        }
        else if (sequanceToCheck == DIAGONAL_LEFT)
        {
            if(inBounds(board, row, col) == false)
            {
                sequanceCounter = 0;
                flag = 1;
            }
            else
            {
                flag = 0;
            }
                tempRow = row;
                tempCol = col;
                row++;
                col++;
        }
        if(flag != 1)
        {
            if(board->_arr[tempRow][tempCol] == val)
            {
                sequanceCounter++;
                if(sequanceCounter == SEQUANCE_LENGTH)
                {
                    return true;
                }
            }
            else
            {
                sequanceCounter = 0;
            }
        }
        flag = 0;
    }
    return false;
}

/**
 * Check if there's a winner on the board - a player that owns 5 squares in a line (vertical, horizontal or diagonal).
 * Return the player ('X' / 'O') is such exists, or ' ' (space) otherwise.
 * Should work in O(1) - use information provided by the putBoardSquare() function.
 * If row or col are negative, report an error OUT_OF_BOUND and return 'E'.
 */
char getWinner(ConstBoardP board)
{
    int lastMove_X = board->_lastMove_X_Coordinate;
    int lastMove_Y = board->_lastMove_Y_Coordinate;
    int newRow = lastMove_X, newColomn = lastMove_Y;
    int sequanceToCheck;
    char lastMove = getBoardSquare(board, lastMove_X, lastMove_Y);
    bool winner;
    if(lastMove != EMPTY_SQUARE)
    {
        for(sequanceToCheck = 0; sequanceToCheck < LEGAL_SEQUANCES; sequanceToCheck++)
        {
            if(sequanceToCheck == VERTICAL)
            {
                newRow = newRow - SEQUANCE_RADIUS;
            }
            else if (sequanceToCheck == HORIZONAL)
            {
                newColomn = newColomn - SEQUANCE_RADIUS;
            }
            else if (sequanceToCheck == DIAGONAL_RIGHT)
            {
                newRow = newRow - SEQUANCE_RADIUS;
                newColomn = newColomn + SEQUANCE_RADIUS;
            }

            else if (sequanceToCheck == DIAGONAL_LEFT)
            {
                newRow = newRow - SEQUANCE_RADIUS;
                newColomn = newColomn - SEQUANCE_RADIUS;
            }
            winner = checkSequance(board, newRow, newColomn, sequanceToCheck, lastMove);
            if(winner == true)
            {
                
                return(board->_arr[lastMove_X][lastMove_Y]);
            }
            
            newRow = lastMove_X;
            newColomn = lastMove_Y;
        }
    }
    return EMPTY_SQUARE;
}

/**
 * Print the board into stream  position (row,col).
 * If row or col are negative, report OUT_OF_BOUND and do nothing.
 * Squares outside of the current memory location should be printed as empty squares.
 */
void printBoard(FILE * stream, ConstBoardP board, int row, int col)
{
    int i, j;
    if(row < 0 || col < 0)
    {
        reportError(OUT_OF_BOUND);
    }
    else
    {
        fprintf(stream, "\nPrinting current state of the board for location (row,col)=(%d,%d)\n", row, col);
        fprintf(stream, "\n");
        for(i = row-1; i < row + COLOMNS_NUM; i++)
        {
            for(j = col-1; j < col + COLOMNS_NUM; j++)
            {
                if((i == row - 1) && (j == col - 1))
                {
                    fprintf(stream, "   ");
                }
                else if((i == row-1) && (j > col - 1))
                {
                    if(j == (col + COLOMNS_NUM) - 1)
                    {
                        fprintf(stream, "+%d", j - col);
                    }
                    else
                    {    
                        fprintf(stream, "+%d ", j - col);
                    }
                }
                else if((i > row-1) && (j == col - 1))
                {
                    fprintf(stream, "+%d ", i - row);
                }
                else if (((i > row - 1) && (i < board->_rows)) && ((j < board->_colomns) && (j > col - 1)))
                {
                    if(j == (col + COLOMNS_NUM) - 1)
                    {
                        fprintf(stream, " %c  ", board->_arr[i][j]);
                    }
                    else
                    {
                        fprintf(stream, " %c ", board->_arr[i][j]);
                    }
                }
                else
                {
                    if(j == (col + COLOMNS_NUM) - 1)
                    {
                        fprintf(stream, " %c  ", EMPTY_SQUARE);
                    }
                    else 
                    {
                        fprintf(stream, " %c ", EMPTY_SQUARE);
                    }
                }
            }
            fprintf(stream, "\n");
        }
        fprintf(stream, "\n");
    }
}


/**
 * return the actual memory size that was allocated for the game
 */
int getAllocatedSize(ConstBoardP board)
{
    int allocatedSize;
    if(board == NULL)
    {
        return 0;
    }
    allocatedSize = sizeof(board) + board->_rows * sizeof(char*) + board->_colomns * sizeof(char);
    return allocatedSize;
}
