#include "Headers.h"

char player_to_char(int plyr)
// a given function.
{
	switch (plyr)
	{
	case PLAYER1: return 'X';
	case PLAYER2: return 'O';
	case EMPTY: return ' ';
	}
	return '!';
}

void print_welcome_message()
{
	printf("Welcome to Ultimate Tic-Tac-Toe!\n");
}

void print_board(int brd[][N]) 
// prints the board every move
{
	print_numbers(MIN_INDEX);
	// print board line by line
	for (int i = 0; i < N; i++)
	{
		printf("%d", i - i % 3 + 1);
		for (int j = 0; j < SUB_NUM; j++)
		{
			for (int k = 0; k < SUB_SIZE; k++)
			{
				if (k > 0)
					printf("  ");
				printf("%c", player_to_char(brd[i][j * SUB_SIZE + k]));
			}
			if (j < SUB_NUM)
				printf("|");
		}
		printf("%d\n", i - i % 3 + 3);
		if (i % 3 == 2 && i != 8)
			print_hor_border();
	}
	print_numbers(MIN_INDEX + 2 * SUB_SIZE);
}

void print_numbers(int first_num) 
// print the numbers next to the borad, which define the sub-board number
{
	printf(" ");
	for (int i = first_num; i < first_num + SUB_NUM; i++)
	{
		for (int j = 0; j < SUB_SIZE; j++)
		{
			if (j > 0) printf("  ");
			printf("%d", i);
		}
		printf(" ");
	}
	printf("\n");
}

void print_hor_border()
// prints the horizontal border of the board
{
	printf(" ");
	for (int i = 1; i <= SUB_NUM; i++)
	{
		for (int j = 0; j < 2 * 2 + 3; j++)
		{
			printf("-");
		}
		printf(" ");
	}
	printf("\n");
}

void first_move(int* Pplyr, int brd[][N], int* PNxtSuBrd,
	int* PInptCheck, int BrdWin[][N])
	// gets the numbers in the first move.
{
	int SuBrdNum;
	printf("Player X, please enter the index of the wanted sub-board:\n");
	is_first_input_valid(PNxtSuBrd, PInptCheck);
	SuBrdNum = *PNxtSuBrd;
	if (*PInptCheck != 0)
	{
		is_input_valid(*Pplyr, PNxtSuBrd, PInptCheck);
		if (*PInptCheck != 0)
			position_status(*PNxtSuBrd, SuBrdNum, *Pplyr, brd, BrdWin);
	}
}

void next_move(int* Pplyr, int brd[][N], int* PNxtSuBrd,
	int* PInptCheck, int BrdWin[][N])
	// makes the next move in the game.
{
	*Pplyr = who_is_turn(*Pplyr);
	int SuBrdNum = *PNxtSuBrd, position_full;
	is_input_valid(*Pplyr, PNxtSuBrd, PInptCheck);
	if (*PInptCheck != 0)
		board_status(PNxtSuBrd, SuBrdNum, Pplyr, brd, PInptCheck, BrdWin);
}

void board_status(int* PNxtSuBrd, int SuBrdNum, int* Pplyr,
	int brd[][N], int* PInptCheck, int BrdWin[][N])
	/*checks the value which returned from the position status function,
	according to that value, directs to the proper functions.*/
{
	int position_full;
	position_full = position_status(*PNxtSuBrd, SuBrdNum, *Pplyr,
		brd, BrdWin);
	if (*PNxtSuBrd)
	{
		while (position_full == 1)
		{
			is_first_input_valid(PNxtSuBrd, PInptCheck);
			if (*PInptCheck == 0)
				break;
			position_full = position_status(*PNxtSuBrd, SuBrdNum, *Pplyr,
				brd, BrdWin);
		}
	}
	if (position_full == FULL)
	{
		tie_check(SuBrdNum, BrdWin);
		is_first_input_valid(PNxtSuBrd, PInptCheck);
		*Pplyr = who_is_turn(*Pplyr);
	}
}

void is_first_input_valid(int* PNxtSuBrd, int* PInptCheck)
// check if the input of the first move is valid.
{
	int inpt_valid = 0;
	do
	{
		inpt_valid = index_error(PNxtSuBrd);
		if (inpt_valid == 0)
		{
			printf("Input error!\n");
			*PInptCheck = 0;
			break;
		}
		inpt_valid += index_range(PNxtSuBrd);
	} while (inpt_valid != 1);
}

void is_input_valid(int Pplyr, int* PNxtSuBrd, int* PInptCheck)
// check if the input of the rest moves is valid.
{
	int inpt_valid = 0;
	print_next_player(Pplyr, PNxtSuBrd);
	do
	{
		inpt_valid = index_error(PNxtSuBrd);
		if (inpt_valid == 0)
		{
			printf("Input error!\n");
			*PInptCheck = 0;
			break;
		}
		inpt_valid += index_range(PNxtSuBrd);
	} while (inpt_valid != 1);
}

int index_error(int* PNxtSuBrd)
// check if the input is an integer.
{
	return scanf("%d", PNxtSuBrd);
}

int index_range(int* PNxtSuBrd)
// check if the input integer is in range.
{
	if ((*PNxtSuBrd > MAX_RANGE) || (*PNxtSuBrd < MIN_RANGE))
	{
		printf("Index out of range. Please enter a value between 1 and 9:\n");
		return -1;
	}
	return 0;
}

int position_status(int PNxtSuBrd, int SuBrdNum, int Pplyr,
	int brd[][N], int BrdWin[][N])
	// check the if the position or the sub-board is full or empty.
{
	int indx_row = calc_row_position(PNxtSuBrd, SuBrdNum);
	int indx_col = calc_col_position(PNxtSuBrd, SuBrdNum);
	int msg = position_is_taken(brd, indx_row, indx_col, Pplyr
		, SuBrdNum, BrdWin);
	if (msg == 0)
		return 0;
	else if (msg == FULL)
	{
		PNxtSuBrd = 0;
		return FULL;
	}
	else
		return 1;
}

int position_is_taken(int brd[][N], int indx_row, int indx_col, int Pplyr,
	int SuBrdNum, int BrdWin[][N])
	// print message position is taken and if there is a sequence in sub board.
{
	if (brd[indx_row][indx_col] == 0)
	{
		brd[indx_row][indx_col] = Pplyr;
		int row_BrdWinner = calc_row_position(SuBrdNum, 1);
		int col_BrdWinner = calc_col_position(SuBrdNum, 1);
		if (!BrdWin[row_BrdWinner][col_BrdWinner])
			sequence(brd, indx_row, indx_col, Pplyr, SuBrdNum, BrdWin);
		if (is_sub_board_full(brd, indx_row, indx_col) == 1)
			tie_check(SuBrdNum, BrdWin);
		print_board(brd);
		return 0;
	}
	else
	{
		if (is_sub_board_full(brd, indx_row, indx_col) == 0)
		{
			printf("Position is taken, please choose another one:\n");
			return 1;
		}
		printf("Sub-board %d is full. Please choose another one:\n", SuBrdNum);
		return FULL;
	}
}

void sequence(int brd[][N], int indx_row, int indx_col, int Pplyr,
	int SuBrdNum, int BrdWin[][N])
	// check a sequence in the sub board
{
	int seq = 0;
	int starting_col = starting_index_col(indx_col);
	int starting_row = starting_index_row(indx_row);
	seq += row_sequence(starting_row, starting_col, Pplyr, brd);
	seq += col_sequence(starting_row, starting_col, Pplyr, brd);
	seq += main_diag_sequence(starting_row, starting_col, Pplyr, brd);
	seq += second_diag_sequence(starting_row, starting_col, Pplyr, brd);
	if (seq)
	{
		int row_winner = calc_row_position(SuBrdNum, 1);
		int col_winner = calc_col_position(SuBrdNum, 1);
		BrdWin[row_winner][col_winner] = Pplyr;
		printf("Player %c has won in sub-board %d!\n",
			player_to_char(Pplyr), SuBrdNum);
		the_winner(BrdWin, Pplyr, row_winner, col_winner);
	}
}

int row_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N])
// check if there is a row sequence.
{
	int row_seq = 0;
	for (int i = StrtRow; i < StrtRow + SUB_SIZE; i++)
	{
		for (int k = StrtCol; k < StrtCol + SUB_SIZE; k++)
			row_seq += brd[i][k];
		if (row_seq == (Pplyr * SUB_SIZE))
			return 1;
		row_seq = 0;
	}
	return 0;
}

int col_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N])
// check if there is a colomn sequence.
{
	int col_seq = 0;
	for (int i = StrtCol; i < StrtCol + SUB_SIZE; i++)
	{
		for (int k = StrtRow; k < StrtRow + SUB_SIZE; k++)
			col_seq += brd[k][i];
		if (col_seq == (Pplyr * SUB_SIZE))
			return 1;
		col_seq = 0;
	}
	return 0;
}

int main_diag_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N])
// check if there is a sequence in the main diagonal.
{
	int main_diag_seq = 0, k = StrtRow;
	for (int i = StrtCol; i < StrtCol + SUB_SIZE; i++)
	{
		main_diag_seq += brd[k][i];
		k++;
	}
	if (main_diag_seq == (Pplyr * SUB_SIZE))
		return 1;
	return 0;
}

int second_diag_sequence(int StrtRow, int StrtCol, int Pplyr, int brd[][N])
// check if there is a sequence in the second diagonal.
{
	int sec_diag_seq = 0, k = StrtRow;
	for (int i = (StrtCol + 2); i > StrtCol - 1; i--)
	{
		sec_diag_seq += brd[k][i];
		k++;
	}
	if (sec_diag_seq == (Pplyr * SUB_SIZE))
		return 1;
	return 0;
}

int starting_index_col(int indx_col)
// calculate the starting index of colomn in the sub board.
{
	int i;
	for (i = indx_col; ; i--)
	{
		if (i % 3 == 0)
			break;
	}
	return i;
}

int starting_index_row(int indx_row)
// calculate the starting index of row in the sub board.
{
	int i;
	for (i = indx_row; ; i--)
	{
		if (i % 3 == 0)
			break;
	}
	return i;
}

void the_winner(int BrdWin[][N], int Pplyr, int row_winner, int col_winner)
// check a sequece in the whole board.
{
	int seq = 0;
	seq += row_sequence(0, 0, Pplyr, BrdWin);
	seq += col_sequence(0, 0, Pplyr, BrdWin);
	seq += main_diag_sequence(0, 0, Pplyr, BrdWin);
	seq += second_diag_sequence(0, 0, Pplyr, BrdWin);
	if (seq)
	{
		print_end_message(Pplyr);
		BrdWin[END_GAME][END_GAME] = 1;
	}
}

void print_end_message(int game_status)
// prints an end message if the game is over.
{
	if (game_status == TIE)
		printf("Game over, it's a tie!\n");
	else
		printf("Game over, %c is the winner!\n", player_to_char(game_status));
	return;
}

void print_next_player(int plyr, int* PNxtSuBrd)
// prints a message for the next player.
{
	switch (plyr)
	{
	case PLAYER1:
		printf("Player X, please enter the wanted position in sub-board %d:\n"
			, *PNxtSuBrd);
		break;
	case PLAYER2:
		printf("Player O, please enter the wanted position in sub-board %d:\n"
			, *PNxtSuBrd);
		break;
	}
}

int who_is_turn(int plyr)
// switch turns for each move.
{
	if (plyr == PLAYER1)
		plyr = PLAYER2;
	else
		plyr = PLAYER1;
	return plyr;
}

int calc_row_position(int PstnInSub, int SuBrdNum)
// calculate the row index in the whole board.
{
	int row_position = (get_sub_row(PstnInSub) / SUB_SIZE)
		+ get_sub_row(SuBrdNum);
	return row_position;
}

int calc_col_position(int PstnInSub, int SuBrdNum)
// calculate the colomn index in the whole board.
{
	int col_position = (get_sub_col(PstnInSub) / SUB_SIZE)
		+ get_sub_col(SuBrdNum);
	return col_position;
}

int get_sub_row(int sub_index)
// gets the sub-board row
{
	return ((sub_index - 1) / SUB_NUM) * SUB_SIZE;
}

int get_sub_col(int sub_index)
// gets the sub-board column
{
	return ((sub_index - 1) % SUB_NUM) * SUB_SIZE;
}

int is_sub_board_full(int brd[][N], int indx_row, int indx_col)
// check if the sub-board is full/
{
	int starting_col = starting_index_col(indx_col);
	int starting_row = starting_index_row(indx_row);
	for (int i = starting_row; i < starting_row + SUB_SIZE; i++)
	{
		for (int j = starting_col; j < starting_col + SUB_SIZE; j++)
		{
			if (brd[i][j] == EMPTY)
				return 0;
		}
	}
	return 1;
}

void tie_check(int SuBrdNum, int BrdWin[][N])
// check if the is a tie in the game.
{
	int sum = 0;
	int row = calc_row_position(SuBrdNum, 3);
	int col = calc_col_position(SuBrdNum, 3);
	BrdWin[row][col] = TIE;
	for (int i = SUB_SIZE + SUB_SIZE; i < SUB_SIZE * SUB_SIZE; i++)
	{
		for (int j = 0; j < SUB_SIZE; j++)
			sum += BrdWin[j][i];
	}
	if (sum == SUB_SIZE * SUB_SIZE)
	{
		print_end_message(TIE);
		BrdWin[END_GAME][END_GAME] = 1;
	}
}