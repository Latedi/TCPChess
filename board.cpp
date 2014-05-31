#include "board.h"

Board::Board()
{
	initialize();
}

void Board::initialize()
{
	Position pos = {1, 1};
	
	//Place pawns
	for(int i = 0; i < SIZE; i++)
	{
		tiles[1][i] = Pawn(pos, BLACK);
		tiles[SIZE-2][i] = Pawn(pos, WHITE);
	}
	
	//Place rooks
	tiles[0][0] = Rook(pos, BLACK);
	tiles[0][SIZE-1] = Rook(pos, BLACK);
	tiles[SIZE-1][0] = Rook(pos, WHITE);
	tiles[SIZE-1][SIZE-1] = Rook(pos, WHITE);
	
	renderBoard();
}

void Board::renderBoard()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			//if(tiles[i][j] == NULL)
			std::cout << tiles[i][j].getChar();
			//else
			//std::cout << "-";
		}
		
		std::cout << std::endl;
	}
}