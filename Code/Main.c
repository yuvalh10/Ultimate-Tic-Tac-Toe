#include "Headers.h"

void main()
{
	int brd[N][N] = { {0} };
	int postion_in_sub = 0, inpt_check = 1, plyr = PLAYER1;
	int* PNxtSuBrd = &postion_in_sub, Pplyr = &plyr;
	int* PInptCheck = &inpt_check;
	int BrdWin[N][N] = { {0} };
	print_welcome_message();
	print_board(brd);
	first_move(Pplyr, brd, PNxtSuBrd, PInptCheck, BrdWin);
	while ((BrdWin[END_GAME][END_GAME] == 0) && (*PInptCheck != 0))
		next_move(Pplyr, brd, PNxtSuBrd, PInptCheck, BrdWin);
}
