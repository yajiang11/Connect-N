#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "win.h"
#include "board.h"
typedef char** board_tp; 

bool is_game_over(board_tp board, int rows, int cols, char blank_char, int winning_num) {
    /*
    checks if the game is over
    @board: the current board
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @return: true if the game is over and false otherwise
    */
    return (someone_won(rows, cols, board, blank_char, winning_num) || tie_game(board, rows, cols, blank_char, winning_num));
}

bool someone_won(int rows, int cols, board_tp board, char blank_char, int winning_num) {
    /*
    checks if someone won
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if someone won and false otherwise
    */
    return someone_won_horizontally(rows, cols, board, blank_char, winning_num) || someone_won_vertically(rows, cols, board, blank_char, winning_num) || someone_won_diagonally(rows, cols, board, blank_char, winning_num);
}

bool someone_won_horizontally(int rows, int cols, board_tp board, char blank_char, int winning_num) {
    /*
    checks if someone won horizontally
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if someone won horizontally and false otherwise
    */
    for (int i = 0; i < rows; i++) {
        if (winning_num_pieces_in_a_row(board[i], cols, blank_char, winning_num)) {
            return true;
        }
    }
    return false;
}

bool winning_num_pieces_in_a_row(char* pieces_array, int array_size, char blank_char, int winning_num){
    /*
    checks an array of any size to see if there are winning_num pieces in a row that is not the blank char
    @pieces_array: an array of characters representing the player pieces to check
    @array_size: the size of pieces_array
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if there is winning num pieces in a row in an array and false otherwise
    */
    int pieces_in_a_row = 1;
    for (int j = 0; j < array_size-1; j++){
        if ((pieces_array[j] == pieces_array[j+1]) && (!is_blank_space(pieces_array[j], blank_char))){
            pieces_in_a_row += 1;
            if (pieces_in_a_row == winning_num){
                return true;
            }
        } 
        else {
            pieces_in_a_row = 1;
        }
    }
    return false;
}

bool someone_won_vertically(int rows, int cols, board_tp board, char blank_char, int winning_num) {
    /*
    checks if someone won vertically
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if someone won vertically and false otherwise
    */
    for (int i = 0; i < cols; i++) {
        char* board_column = get_column(board, rows, i);
        if (winning_num_pieces_in_a_row(board_column, rows, blank_char, winning_num)) {
            free(board_column);
            return true;
        }
        free(board_column);
    }
    return false;
}

bool tie_game(board_tp board, int rows, int cols, char blank_char, int winning_num) {
    /*
    checks if it is a tie game
    @board: the current board
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if it is a tie game and false otherwise
    */
    return (is_board_full(board, rows, cols, blank_char) && !someone_won(rows, cols, board, blank_char, winning_num));
}

void announce_results(int rows, int cols, board_tp board, char blank_char, int winning_num, int cur_player_turn) {
    /*
    announces the results after the game has ended
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @cur_player_turn: the current player's turn
    @returns: nothing
    */
    print_board(board, rows, cols);
    if (someone_won(rows, cols, board, blank_char, winning_num)) {
        printf("Player %d Won!\n", cur_player_turn+1);
    }
    else {
        printf("Tie game!\n");
    }
}

bool someone_won_diagonally(int rows, int cols, board_tp board, char blank_char, int winning_num) {
    /*
    checks if someone won diagonally
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if someone won diagonally and false otherwise
    */
    return (someone_won_left_diagonal(rows, cols, board, blank_char, winning_num) || someone_won_right_diagonal(rows, cols, board, blank_char, winning_num));
}

bool someone_won_left_diagonal(int rows, int cols, board_tp board, char blank_char, int winning_num) {
    /*
        X
         X
          X
    make sure to check a diagonal of a fixed size (winning_num) each time

    checks if someone won the left diagonal
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if someone won left diagonally and false otherwise
    */
    if ((rows < winning_num) || (cols < winning_num)) {
        return false; // can't have a diagonal if the dimensions are too small
    }
    for (int i = 0; i <= (rows - winning_num); i++) { // only check rows that can have a valid diagonal
        for (int j = 0; j <= (cols - winning_num); j++) { // only checking cols that can have a valid diagonal
            if (!is_blank_space(board[i][j], blank_char)) {
                char* board_left_diagonal = get_left_diagonal(board, i , j, winning_num); 
                // gets the left diagonal starting from position (i, j) with a fixed size of winning_num
                if (all_the_same(board_left_diagonal, winning_num)) {
                    free(board_left_diagonal);
                    return true;
                }
                free(board_left_diagonal);
            }
        }
    }
    return false;
}

bool someone_won_right_diagonal(int rows, int cols, board_tp board, char blank_char, int winning_num) {
    /*
          X
         X
        X
    make sure to check a diagonal of a fixed size (winning_num) each time

    checks if someone won the right diagonal
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @board: the current board
    @blank_char: the blank character
    @winning_num: the number of pieces in a row to win
    @returns: true if someone won right diagonally and false otherwise
    */
    if ((rows < winning_num) || (cols < winning_num)) {
        return false;
    }
    for (int i = 0; i <= (rows - winning_num); i++) { // only check rows that can have a valid diagonal
        for (int j = (cols - 1); j >= (winning_num - 1); j--) { // TO-DO look for pattern for columns
            if (!is_blank_space(board[i][j], blank_char)) {
                char* board_right_diagonal = get_right_diagonal(board, i , j, winning_num); 
                // gets the right diagonal starting from position (i, j) with a fixed size of winning_num
                if (all_the_same(board_right_diagonal, winning_num)) {
                    free(board_right_diagonal);
                    return true;
                }
                free(board_right_diagonal);
            }
        }
    }
    return false;
}

bool all_the_same(char* array, int num_elements) {
    /*
    checks to see if every element of an array is the same
    @array: an array to check
    @num_elements: the number of elements in the array
    @returns: true if all elemnts are the same in the array and false otherwise
    */
    for (int i = 0; i < num_elements; i++) {
        if (array[i] != array[0]) {
            return false;
        }
    }
    return true;
}