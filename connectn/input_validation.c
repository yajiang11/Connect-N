#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "input_validation.h"
#include "board.h" 
typedef char** board_tp;

void get_valid_move_from_player(board_tp board, int board_rows, int board_cols, char blank_char, int* user_col) {
    /*
    gets a valid move from the player that is between 0 to the number of cols-1
    @board: the current board
    @board_rows: the number of rows on the board
    @board_cols: the number of columns on the board
    @blank_char: the blank character
    @user_col: the valid user column that the user inputs
    @returns: nothing
    @modifies: user_col
    */
    do {
        *user_col = getValidInt(board_cols-1);
    } while (!inbetween(*user_col, 0, board_cols - 1) || !empty_space_at_col_on_board(*user_col, board, board_rows, blank_char));
}

bool inbetween(int val, int lowerBound, int upperBound){
    /*
    this function checks if a number is in between two other numbers
    @val: the value to check
    @lowerBound: the lower bound to check if the value is in between of
    @upperBound: the upper bound to check if the value is in between of
    @returns: true if the value is in between the lower and upper bounds and false otherwise
    */
    return val >= lowerBound && val <= upperBound;
}

bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
    /*
    checks if format is valid, taken from class close
    @numArgsRead: number of args scanf read
    @numArgsNeed: number of args scanf was intended to read
    @returns: true if format is valid and false otherwise
    */
    bool formatIsGood = numArgsRead == numArgsNeed;
    char character;
    do {
        scanf("%c", &character); 
		    if(!isspace(character)){ 
			  formatIsGood = false;
		    }
	  } while(character != '\n');
    return formatIsGood;
}


int getValidInt(int col){
    /*
    gets a valid int that is greater than or equal to 0
    @col: the column to use when prompting the user for input
    @returns: the valid int
    */
    int num;
    const int numArgsNeeded = 1;
    int numArgsRead;
    do{
        printf("Enter a column between 0 and %d to play in: ", col);
        numArgsRead = scanf(" %d", &num); 
    } while(!isValidFormat(numArgsRead, numArgsNeeded));

    return num;
}