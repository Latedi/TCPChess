#include "board.h"

Board::Board()
{
	initialize();
}

void Board::initialize()
{	
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			tiles[i][j] = NULL;
		}
	}
	
	//Place pawns
	for(int i = 0; i < SIZE; i++)
	{
		Pawn *blackPawn = new Pawn(BLACK);
		Pawn *whitePawn = new Pawn(WHITE);
		tiles[1][i] = blackPawn;
		tiles[SIZE-2][i] = whitePawn;
	}
	
	//Place rooks
	Rook *blackRook1 = new Rook(BLACK);
	Rook *blackRook2 = new Rook(BLACK);
	Rook *whiteRook1 = new Rook(WHITE);
	Rook *whiteRook2 = new Rook(WHITE);
	tiles[0][0] = blackRook1;
	tiles[0][SIZE-1] = blackRook2;
	tiles[SIZE-1][0] = whiteRook1;
	tiles[SIZE-1][SIZE-1] = whiteRook2;
	
	//Place knights
	Knight *blackKnight1 = new Knight(BLACK);
	Knight *blackKnight2 = new Knight(BLACK);
	Knight *whiteKnight1 = new Knight(WHITE);
	Knight *whiteKnight2 = new Knight(WHITE);
	tiles[0][1] = blackKnight1;
	tiles[0][SIZE-2] = blackKnight2;
	tiles[SIZE-1][1] = whiteKnight1;
	tiles[SIZE-1][SIZE-2] = whiteKnight2;
	
	//Place bishops
	Bishop *blackBishop1 = new Bishop(BLACK);
	Bishop *blackBishop2 = new Bishop(BLACK);
	Bishop *whiteBishop1 = new Bishop(WHITE);
	Bishop *whiteBishop2 = new Bishop(WHITE);
	tiles[0][2] = blackBishop1;
	tiles[0][SIZE-3] = blackBishop2;
	tiles[SIZE-1][2] = whiteBishop1;
	tiles[SIZE-1][SIZE-3] = whiteBishop2;
	
	//Place kings
	King *blackKing = new King(BLACK);
	King *whiteKing = new King(WHITE);
	tiles[0][4] = blackKing;
	tiles[SIZE-1][4] = whiteKing;
	
	//Place queens
	Queen *blackQueen = new Queen(BLACK);
	Queen *whiteQueen = new Queen(WHITE);
	tiles[0][3] = blackQueen;
	tiles[SIZE-1][3] = whiteQueen;
	
	renderBoard();
}

void Board::renderBoard()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(tiles[i][j] != NULL)
			{
				tiles[i][j]->printMe();
			}
			else
			{
				std::cout << "-";
			}
		}
		
		std::cout << std::endl;
	}
}

int Board::getSize()
{
	return SIZE;
}