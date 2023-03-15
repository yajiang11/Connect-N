#include <stdbool.h>
#include "game_play.h"
#include "board.h"
#include "win.h" 
#include "input_validation.h"
typedef char** board_tp;

void set_up_game(int rows, int cols, board_tp* board, char blank_char) {
    /*
    sets up the game by making an empty board with the specified rows, cols, and blnak char
    @rows: the number of rows of the board
    @cols: the number of columns of the board
    @blank_char: the blank character
    @returns: nothing
    @modifies: board
    */
    *board = make_empty_board(rows, cols, blank_char);
}

void play_game(int rows, int cols, int num_to_win, board_tp board, char* player_pieces, int starting_player_turn, char blank_char) {
    /*
    this function includes everything involving playing the game and announcing results
    @rows: the number of rows on the board
    @cols: the number of columns on the board
    @num_to_win: the number of pieces in a row to win
    @board: the current board
    @player_pieces: the list of the player pieces
    @starting_player_turn: a number representing the starting player's turn
    @blank_char: the blank character
    @returns: nothing
    */
    int cur_player_turn = starting_player_turn;
    const int num_players = 2;
    while(true) {
        cur_player_take_turn(board, rows, cols, blank_char, player_pieces[cur_player_turn]);
        if (is_game_over(board, rows, cols, blank_char, num_to_win)) {
            break;
        }
        change_turns(&cur_player_turn, num_players);
    }
    announce_results(rows, cols, board, blank_char, num_to_win, cur_player_turn);
    delete_board(&board, rows);
}

void cur_player_take_turn(char**board, int board_rows, int board_cols, char blank_char, char cur_player_piece){
    /*
    the current players takes their turn
    @board: the current board
    @board_rows: the number of rows on the board
    @board_cols: the number of columns on the board
    @blank_char: the blank character
    @cur_player_piece: the piece of the current player
    @returns: nothing
    */
	int user_col;
	print_board(board, board_rows, board_cols);
	get_valid_move_from_player(board, board_rows, board_cols, blank_char, &user_col);
	place_piece(board_rows, board, user_col, blank_char, cur_player_piece);
}

void change_turns(int* cur_player_turn, int number_of_players) {
    /*
    this function switches the turn from the current player to the next player
    @cur_player_turn: the current player turn
    @number_of_players: the number of players
    @returns: nothing
    @modifies: cur_player_turn
    */
    *cur_player_turn = (*cur_player_turn + 1 ) % number_of_players;
}
