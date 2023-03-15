#ifndef BOARD_H 
    #define BOARD_H
    #include <stdbool.h>
    typedef char** board_tp;
    board_tp make_empty_board(int rows, int cols, char blank_char);
    void print_board(char** board, int rows, int cols);
    bool empty_space_at_col_on_board(int user_col, board_tp board, int board_rows, char blank_char);
    void place_piece(int board_rows, board_tp board, int user_col, char blank_char, char cur_player_piece);
    bool is_blank_space(char spot_to_check, char blank_char);
    char* get_column(board_tp board, int rows, int col);
    bool is_board_full(board_tp board, int rows, int cols, char blank_char);
    char* get_left_diagonal(board_tp board, int starting_i, int starting_j, int winning_num);
    char* get_right_diagonal(board_tp board, int starting_i, int starting_j, int winning_num);
    void delete_board(board_tp* board, int rows);
#endif