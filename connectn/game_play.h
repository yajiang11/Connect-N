#ifndef GAME_PLAY_H
    #define GAME_PLAY_H
    typedef char** board_tp; 
    void set_up_game(int rows, int cols, board_tp* board, char blank_char);
    void play_game(int rows, int cols, int num_to_win, board_tp board, char* player_pieces, 
                    int starting_player_turn, char blank_char);
    void cur_player_take_turn(char**board, int board_rows, int board_cols, char blank_char, char cur_player_piece);
    void change_turns(int* cur_player_turn, int number_of_players);
#endif