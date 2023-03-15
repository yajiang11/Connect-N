#ifndef INPUT_VALIDATION_H
	#define INPUT_VALIDATION_H
	#include <stdbool.h>
    typedef char** board_tp; 
	void get_valid_move_from_player(board_tp board, int board_rows, int board_cols, char blank_char, int* user_col);
    bool inbetween(int val, int lowerBound, int upperBound);
	bool isValidFormat(const int numArgsRead, const int numArgsNeed);
	int getValidInt(int col);
#endif