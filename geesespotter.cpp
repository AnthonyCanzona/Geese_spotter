#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim)
{
	char *a_boardSetup {new char[xdim*ydim]{}};
	for (std::size_t x = 0; x < xdim*ydim; x++)
		{
			a_boardSetup[x] = 0;
		}
	return a_boardSetup;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
	for (std::size_t x = 0; x < (xdim*ydim); x++)
	{
		if (board[x] != 9)
		{
			if (board[x + 1] == 9 && (x + 1)%xdim != 0)
			{
				board[x]++;
			}
			if (board[x - 1] == 9 && x%xdim != 0)
			{
				board[x]++;
			}
			if (board[x + xdim] == 9 && x < xdim*ydim - xdim)
			{
				board[x]++;
			}
			if (board[x - xdim] == 9 && x >= xdim)
			{
				board[x]++;
			}
			if (board[x + xdim + 1] == 9 && (x + xdim + 1)%xdim != 0 &&  (x + 1) < xdim*ydim - xdim)
			{
				board[x]++;
			}
			if (board[x + xdim - 1] == 9 && x%xdim != 0 && x < xdim*ydim - xdim)
			{
				board[x]++;
			}
			if (board[x - xdim + 1] == 9 && (x + 1)%xdim != 0 && x >= xdim)
			{
				board[x]++;
			}
			if (board[x - xdim - 1] == 9 && x%xdim != 0 && (x - xdim - 1) >= 0)
			{
				board[x]++;
			}
		}
	}
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
	for (std::size_t x = 0; x < xdim*ydim; x++)
	{
		board[x] += hiddenBit();
	}

}

void cleanBoard(char *board)
{
	delete[] board;
	board = nullptr;

}

void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{
	for (std::size_t x = 0; x < xdim*ydim; x++)
	{
		if (x%xdim == 0)
		{
			std::cout << std::endl;
		}
		if (board [x] < hiddenBit())
		{
			char revealedChar {board[x] + 48};
			std::cout << revealedChar;
		}
		else if (board [x] >= hiddenBit() && board [x] < hiddenBit() + markedBit())
		{
			std::cout << '*';
		}
		else if (board [x] >= markedBit() + hiddenBit())
		{
			std::cout << 'M';
		}
	}
	std::cout << std::endl;
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
	if (board[xloc + yloc*xdim] >= hiddenBit() && board[xloc + yloc*xdim] < hiddenBit() + markedBit())
	{
		board [xloc + yloc*xdim] -= hiddenBit();
		if (board [xloc + yloc*xdim] == 9)
		{
			return 9;
		}
		if (board [xloc + yloc*xdim] == 0)
		{
			if ((xloc + yloc*xdim + 1)%xdim != 0 && board[xloc + yloc*xdim + 1] >= hiddenBit())
			{
				board [xloc + yloc*xdim + 1] -= hiddenBit();
			}
			if ((xloc + yloc*xdim)%xdim != 0 && board[xloc + yloc*xdim - 1] >= hiddenBit())
			{
				board [xloc + yloc*xdim - 1] -= hiddenBit();
			}
			if ((xloc + (yloc - 1)*xdim) >= 0 && board[xloc + (yloc - 1)*xdim] >= hiddenBit())
			{
				board [xloc + (yloc - 1)*xdim] -= hiddenBit();
			}
			if ((xloc + (yloc + 1)*xdim) < xdim*ydim && board[xloc + (yloc + 1)*xdim] >= hiddenBit())
			{
				board [xloc + (yloc + 1)*xdim] -= hiddenBit();
			}
			if ((xloc + (yloc - 1)*xdim )%xdim != 0 && (xloc + (yloc - 1)*xdim - 1) >= 0 && board[xloc + (yloc - 1)*xdim - 1] >= hiddenBit())
			{
				board [xloc + (yloc - 1)*xdim - 1] -= hiddenBit();
			}
			if ((xloc + (yloc - 1)*xdim + 1)%xdim != 0 && (xloc + (yloc - 1)*xdim + 1) >= 0 && board[xloc + (yloc - 1)*xdim + 1] >= hiddenBit())
			{
				board [xloc + (yloc - 1)*xdim + 1] -= hiddenBit();
			}
			if ((xloc + (yloc + 1)*xdim + 1)%xdim != 0 && (xloc + (yloc + 1)*xdim + 1) < xdim*ydim && board[xloc + (yloc + 1)*xdim + 1] >= hiddenBit())
			{
				board [xloc + (yloc + 1)*xdim + 1] -= hiddenBit();
			}
			if ((xloc + (yloc + 1)*xdim)%xdim != 0 && (xloc + (yloc + 1)*xdim - 1) < xdim*ydim && board[xloc + (yloc + 1)*xdim - 1] >= hiddenBit())
			{
				board [xloc + (yloc + 1)*xdim - 1] -= hiddenBit();
			}
		}
	}
	else if (board[xloc + yloc*xdim] >= markedBit() + hiddenBit())
	{
		return 1;
	}
	else if (board[xloc + yloc*xdim] < hiddenBit())
	{
		return 2;
	}
	return 0;
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
	if (board [xloc + yloc*xdim] < hiddenBit())
	{
		return 2;
	}
	else if (board[xloc + yloc*xdim] < markedBit() + hiddenBit() && board[xloc + yloc*xdim] >= hiddenBit())
	{
		board [xloc + yloc*xdim] += markedBit();
	}
	else if (board[xloc + yloc*xdim] >= markedBit() + hiddenBit())
	{
		board [xloc + yloc*xdim] -= markedBit();
	}
	return 0;
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
	std::size_t winCondition {0};
	for (std::size_t x = 0; x < xdim*ydim; x++)
	{
		if (board[x] < hiddenBit() || board[x] == 0x29 || board[x] == 0x39)
		{
			winCondition++;
		}
	}
	if (winCondition == xdim*ydim)
	{
		return true;
	}
	else
	{
	return false;
	}
}
