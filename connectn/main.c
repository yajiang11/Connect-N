/*
This program is a game of connect n where the user can choose the board size and number of pieces
in a row to win.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "game_play.h"
typedef char** board_tp;

int main(int argc, char** argv) {
    int num_rows, num_cols, num_to_win;
    board_tp board = NULL;
    char* player_pieces = "XO";
    char blank_char = '*';
    int starting_player_turn = 0;
    if (argc < 4) {
        printf("Not enough arguments entered\nUsage connectn.out num_rows num_columns\nnumber_of_pieces_in_a_row_needed_to_win");
        return 0;
    }
    else if (argc > 4) {
        printf("Too many arguments entered\nUsage connectn.out num_rows num_columns\nnumber_of_pieces_in_a_row_needed_to_win");
        return 0;
    }
    else {
        num_rows = atoi(argv[1]);
        num_cols = atoi(argv[2]);
        num_to_win = atoi(argv[3]);
    }
    set_up_game(num_rows, num_cols, &board, blank_char);
    play_game(num_rows, num_cols, num_to_win, board, player_pieces, starting_player_turn, blank_char);
}




