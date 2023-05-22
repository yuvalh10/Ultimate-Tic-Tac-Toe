#ifndef _Headers_H
#define _Headers_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define EMPTY 0
#define N 9
#define SUB_SIZE 3
#define SUB_NUM 3
#define TIE 1
#define PLAYER1 2
#define PLAYER2 5
#define FULL -1
#define MIN_INDEX 1
#define MIN_RANGE 1
#define MAX_RANGE 9
#define END_GAME 8

void print_welcome_message();

void print_board(int brd[][N]);

void print_numbers(int first_num);

void print_hor_border();

char player_to_char(int plyr);

void first_move(int* Pplyr, int brd[][N], int* PNxtSuBrd,

	int* PInptCheck, int BrdWin[][N]);

void next_move(int* Pplyr, int brd[][N], int* PNxtSuBrd,
	int* PInptCheck, int BrdWin[][N]);

int position_status(int PNxtSuBrd, int SuBrdNum, int Pplyr,
	int brd[][N], int BrdWin[][N]);

void print_next_player(int plyr, int* PNxtSuBrd);

void is_first_input_valid(int* PNxtSuBrd, int* PInptCheck);

void is_input_valid(int Pplyr, int* PNxtSuBrd, int* PInptCheck);

void board_status(int* PNxtSuBrd, int SuBrdNum, int* Pplyr,
	int brd[][N], int* PInptCheck, int BrdWin[][N]);

int position_is_taken(int brd[][N], int indx_row, int indx_col, int Pplyr,
	int SuBrdNum, int BrdWin[][N]);

int index_error(int* PNxtSuBrd);

int index_range(int* PNxtSuBrd);

int starting_index_col(int indx_col);

int starting_index_row(int indx_row);

int who_is_turn(int plyr);

int get_sub_row(int sub_index);

int get_sub_col(int sub_index);

int calc_row_position(int PstnInSub, int SuBrdNum);

int calc_col_position(int PstnInSub, int SuBrdNum);

void sequence(int brd[][N], int indx_row, int indx_col, int Pplyr,
	int SuBrdNum, int BrdWin[][N]);

int row_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N]);

int col_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N]);

int main_diag_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N]);

int second_diag_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N]);

void the_winner(int BrdWin[][N], int Pplyr, int row_winner, int col_winner);

void print_end_message(int game_status);

int is_sub_board_full(int brd[][N], int indx_row, int indx_col);

void tie_check(int SuBrdNum, int BrdWin[][N]);

#endif
