#ifndef WIN_H
    #define WIN_H
    #include <stdbool.h>
    typedef char** board_tp; 
    bool is_game_over(board_tp board, int rows, int cols, char blank_char, int winning_num);
    bool someone_won(int rows, int cols, board_tp board, char blank_char, int winning_num);
    bool someone_won_horizontally(int rows, int cols, board_tp board, char blank_char, int winning_num);
    bool winning_num_pieces_in_a_row(char* pieces_array, int cols, char blank_char, int winning_num);
    bool someone_won_vertically(int rows, int cols, board_tp board, char blank_char, int winning_num);
    bool tie_game(board_tp board, int rows, int cols, char blank_char, int winning_num);
    void announce_results(int rows, int cols, board_tp board, char blank_char, int winning_num, int cur_player_turn);
    bool someone_won_diagonally(int rows, int cols, board_tp board, char blank_char, int winning_num);
    bool someone_won_left_diagonal(int rows, int cols, board_tp board, char blank_char, int winning_num);
    bool someone_won_right_diagonal(int rows, int cols, board_tp board, char blank_char, int winning_num);
    bool all_the_same(char* array, int winning_num);
#endif
