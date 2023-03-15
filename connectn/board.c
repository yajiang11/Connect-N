#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
typedef char** board_tp;

board_tp make_empty_board(int rows, int cols, char blank_char) {
    /* 
    this makes an empty board of dimension rows x cols filled with the blank character
    @rows: number of rows of the board
    @cols: number of columns of the board
    @blank_char: the blank character to fill the board with
    @returns: the empty board of rows x cols size filled with the blank char
    */
    board_tp empty_board = (board_tp)calloc(rows, sizeof(char*));
    for (int i = 0; i < rows; i++) {
        empty_board[i] = (char*)calloc(cols, sizeof(char));
        for (int j = 0; j < cols; j++) {
            empty_board[i][j] = blank_char;
        }
    }
    return empty_board;
}

bool is_blank_space(char spot_to_check, char blank_char) {
    /*
    checks if the spot on the board is empty
    @spot_to_check: the char at the spot on the board to check
    @blank_char: the blank character
    @returns: true if the character at that spot is the blank char and false otherwise
    */
    if (spot_to_check == blank_char) {
        return true;
    }
    return false;
}

void print_board(char** board, int rows, int cols){
    /*
    this function prints the board with the current format
    @board: the current board
    @rows: the number of rows on the board
    @cols: the number of columsn on the board
    @returns: nothing
    */
    for (int i = 0; i < rows; i++) {
        printf("%d ", (rows - 1 - i));
        for (int j = 0; j < cols; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for (int j = 0; j < cols; j++) {
        printf("%d ", j);
    }
    printf("\n");
}

bool empty_space_at_col_on_board(int user_col, board_tp board, int board_rows, char blank_char){
    /*
    checks if there is an empty space anywhere in the column
    @user_col: the column to check for an empty space at
    @board: the current board
    @board_rows: the number of rows on the board
    @blank_char: the blank character to represent empty space
    @returns: true if there is empty space somewhere in the column and false otherwise
    */
    for (int i = 0; i < board_rows; i++) {
        if (is_blank_space(board[i][user_col], blank_char)) {
            return true;
        }
    }
    return false;
}

void place_piece(int board_rows, board_tp board, int user_col, char blank_char, char cur_player_piece) {
    /*
    this function places the current player's piece on the board
    @board_rows: the number of rows on the board
    @board: the current board
    @user_col: the column the user wants to put their piece on
    @blank_char: the blank character
    @cur_player_piece: the character of the current player's piece
    @returns: nothing
    */
    for (int i = board_rows-1; i >= 0; i--) {
        if (is_blank_space(board[i][user_col], blank_char)) {
            board[i][user_col] = cur_player_piece;
            break;
        }
    }
}

char* get_column(board_tp board, int rows, int col) {
    /*
    gets the whoel column of the specified column on the board
    @board: the current board
    @rows: the number of rows on the board
    @col: the column to get the values at
    @returns: a list of characters of every piece in that column
    */
    char* the_column = (char*)calloc(rows, sizeof(char));
	for(int i = 0; i < rows; i++){
		the_column[i] = board[i][col];
	}
	return the_column;
}

bool is_board_full(board_tp board, int rows, int cols, char blank_char) {
    /*
    checks if the board is full
    @board: the current board
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @blank_char: the blank character
    @returns: true if the board is full and false otherwise
    */
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (is_blank_space(board[i][j], blank_char)) {
                return false;
            }
        }
    }
    return true;
}

char* get_left_diagonal(board_tp board, int starting_i, int starting_j, int winning_num) {
    /*
    gets the left diagonal of winning_num size starting at a starting pos (i, j)
    @board: the current board
    @starting_i: the starting row position to form the diagonal at
    @starting_j: the starting column position to form the diagonal at
    @winning_num: the number of pieces in a row to win
    @returns: a list of characters of every piece in that diagonal
    */
    char* left_diagonal = (char*)calloc(winning_num, sizeof(char));
	for(int i = 0; i < winning_num; i++){
        left_diagonal[i] = board[starting_i + i][starting_j + i];
	}
	return left_diagonal;
}

char* get_right_diagonal(board_tp board, int starting_i, int starting_j, int winning_num) {
    /*
    gets the right diagonal of winning_num size starting at a starting pos (i, j)
    @board: the current board
    @starting_i: the starting row position to form the diagonal at
    @starting_j: the starting column position to form the diagonal at
    @winning_num: the number of pieces in a row to win
    @returns: a list of characters of every piece in that diagonal
    */
    char* right_diagonal = (char*)calloc(winning_num, sizeof(char));
	for(int i = 0; i < winning_num; i++){
        right_diagonal[i] = board[starting_i + i][starting_j - i];
	}
	return right_diagonal;
}

void delete_board(board_tp* board, int rows) {
    /*
    deletes the board
    @board: the current board
    @rows: the number of rows on the board
    @returns: nothing
    @modifies: board
    */
    for (int i = 0; i < rows; i++) {
        free((*board)[i]);
    }
    free(*board);
    *board = NULL;
}