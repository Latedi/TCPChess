#include "board.h"

Board::Board()
{
	initialize();
}

//Delete all existing pieces
Board::~Board()
{
	for(int i = 0; i < B_SIZE; i++)
	{
		for(int j = 0; j < B_SIZE; j++)
		{
			if(!isTileEmpty(Position(i, j)))
				delete tiles[i][j];
		}
	}
}

//Place all the pieces on the board
void Board::initialize()
{
	for(int i = 0; i < B_SIZE; i++)
	{
		for(int j = 0; j < B_SIZE; j++)
		{
			tiles[i][j] = NULL;
		}
	}
	
	//Place pawns
	for(int i = 0; i < B_SIZE; i++)
	{
		Pawn *blackPawn = new Pawn(BLACK);
		Pawn *whitePawn = new Pawn(WHITE);
		tiles[1][i] = blackPawn;
		tiles[B_SIZE-2][i] = whitePawn;
	}
	
	//Place rooks
	Rook *blackRook1 = new Rook(BLACK);
	Rook *blackRook2 = new Rook(BLACK);
	Rook *whiteRook1 = new Rook(WHITE);
	Rook *whiteRook2 = new Rook(WHITE);
	tiles[0][0] = blackRook1;
	tiles[0][B_SIZE-1] = blackRook2;
	tiles[B_SIZE-1][0] = whiteRook1;
	tiles[B_SIZE-1][B_SIZE-1] = whiteRook2;
	
	//Place knights
	Knight *blackKnight1 = new Knight(BLACK);
	Knight *blackKnight2 = new Knight(BLACK);
	Knight *whiteKnight1 = new Knight(WHITE);
	Knight *whiteKnight2 = new Knight(WHITE);
	tiles[0][1] = blackKnight1;
	tiles[0][B_SIZE-2] = blackKnight2;
	tiles[B_SIZE-1][1] = whiteKnight1;
	tiles[B_SIZE-1][B_SIZE-2] = whiteKnight2;
	
	//Place bishops
	Bishop *blackBishop1 = new Bishop(BLACK);
	Bishop *blackBishop2 = new Bishop(BLACK);
	Bishop *whiteBishop1 = new Bishop(WHITE);
	Bishop *whiteBishop2 = new Bishop(WHITE);
	tiles[0][2] = blackBishop1;
	tiles[0][B_SIZE-3] = blackBishop2;
	tiles[B_SIZE-1][2] = whiteBishop1;
	tiles[B_SIZE-1][B_SIZE-3] = whiteBishop2;
	
	//Place kings
	King *blackKing = new King(BLACK);
	King *whiteKing = new King(WHITE);
	tiles[0][4] = blackKing;
	tiles[B_SIZE-1][4] = whiteKing;
	
	//Place queens
	Queen *blackQueen = new Queen(BLACK);
	Queen *whiteQueen = new Queen(WHITE);
	tiles[0][3] = blackQueen;
	tiles[B_SIZE-1][3] = whiteQueen;
}

//See if there is a already a piece on the tile or not.
bool Board::isTileEmpty(Position position) const
{
	if(tiles[position.getY()][position.getX()] == NULL)
		return true;
	return false;
}

//Check if the tile exists on the board. ie a tile with index -1 2 doesn't exist.
bool Board::doesTileExist(Position position) const
{
	int x = position.getX();
	int y = position.getY();
	if(y >= 0 && y < B_SIZE && x >= 0 && x < B_SIZE)
		return true;
	return false;
}

//Check if a tile belongs to a team
bool Board::isTileTeam(Position pos, int team) const
{
	if(doesTileExist(pos) && !isTileEmpty(pos))
	{
		if(tiles[pos.getY()][pos.getX()]->getTeam() == team)
			return true;
	}
	
	return false;
}

//See if there's a checkmate
bool Board::gameOver() const
{
	return false;
}

//Return the positions a piece can move to.
std::vector<Position> Board::getMovable(Position position) const
{
	int x = position.getX();
	int y = position.getY();
	std::vector<Position> res;
	
	if(doesTileExist(position) && !isTileEmpty(position))
	{
		res = tiles[y][x]->getMovableTiles(position, this);
	}
	
	return res;
}

//Helpful when debugging
void Board::printPositionVector(std::vector<Position> positions) const
{
	std::cout << "Printing position vector of size " << positions.size() << ":" << std::endl;
	
	for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
	{
		if(doesTileExist(*it))
		{
			std::cout << it->toString() << std::endl;
		}
	}
}

//Render a list of positions visually. Makes it a lot more readable where a piece can move etc.
void Board::renderHighlightedPosiotions(std::vector<Position> positions) const
{
	resetConsoleColor();
	std::cout << " abcdefgh" << std::endl;
	
	for(int i = 0; i < B_SIZE; i++)
	{
		std::cout << B_SIZE - i;
		
		for(int j = 0; j < B_SIZE; j++)
		{
			Position thisPosition = Position(j, i);
			
			int bgColor = (i + j) % 2;
			for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
			{
				if(*it == thisPosition)
					bgColor = HIGHLIGHT;
			}
			
			tiles[i][j]->printEmpty(bgColor);
		}
		
		resetConsoleColor();
		std::cout << std::endl;
	}
	
	resetConsoleColor();
}

//Print the entire board. Pieces are responsible for printing themselves
void Board::renderBoard() const
{
	resetConsoleColor();
	std::cout << " abcdefgh" << std::endl;
	
	for(int i = 0; i < B_SIZE; i++)
	{
		std::cout << B_SIZE - i;
		
		for(int j = 0; j < B_SIZE; j++)
		{
			int bgColor = (i + j) % 2;
			if(tiles[i][j] != NULL)
			{
				tiles[i][j]->printMe(bgColor);
			}
			else
			{
				tiles[i][j]->printEmpty(bgColor);
			}
		}
		
		resetConsoleColor();
		std::cout << std::endl;
	}
	
	resetConsoleColor();
}

//Reset the console color so we don't get a funky looking command line
void Board::resetConsoleColor() const
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

Piece* Board::getPiece(Position position) const
{
	return tiles[position.getY()][position.getX()];
}

int Board::getB_SIZE() const
{
	return B_SIZE;
}

//Add a piece to position
void Board::addPiece(Piece* piece, Position newPos, Position oldPos)
{
	tiles[newPos.getY()][newPos.getX()] = piece;
	tiles[oldPos.getY()][oldPos.getX()] = NULL;
		
	return;
}

//If there is a piece at the given position, then that piece is removed
void Board::removePiece(Position position)
{
	delete tiles[position.getY()][position.getX()];
	
	return;
}

//Moves a piece from one location to another
bool Board::movePiece(Position from, Position to, int team)
{
	Piece* piece = tiles[from.getY()][from.getX()];
	
	if(piece == NULL)
	{
		std::cout << "Cannot move because there is nothing at this location\n";
		return false;
	}
	else
	{
		//Check if the tiles exist and if the player owns the piece on the from Position
		if(doesTileExist(from) && doesTileExist(to) && !isTileEmpty(from) && isTileTeam(from, piece->getTeam()))
		{
			std::vector<Position> movable = getMovable(from);
			
			//If the player is checked after having made a move, we will need to reverse the move.
			//So we save the piece which might exist at the destination tile in a variable instead
			//of deleting it.
			bool beforeCheck = isCheck(team);
			Piece *p;
			if(!isTileEmpty(to))
				p = tiles[to.getY()][to.getX()];
			else
				p = NULL;
			
			//Make sure that the piece can actually move to that tile
			for(std::vector<Position>::iterator it = movable.begin(); it != movable.end(); it++)
			{
				if(*it == to)
				{
					//Move the piece and remove pieces from the destination tile
					if(!isTileEmpty(to) && !isTileTeam(to, piece->getTeam()))
					{
						//We will delete the piece later if checked
						if(!beforeCheck)
							removePiece(to);
					}
					addPiece(piece, to, from);
					
					//Try to exchange pawns for queens if possible
					if(piece->getRepresentation() == 'P')
					{
						//If the transformation is successful, we need to see if the opponent is checked
						//so that we can alert them.
						bool res = pawnToQueen(to);
						if(res)
						{
							/*bool opponentChecked = isCheck(getEnemyTeam(team));
							if(opponentChecked)
							{
								std::cout << "Player " << getEnemyTeam(team) << " has been checked\n";
							}*/
						}
					}
						
					//If the player is not checked after the move, complete the move. Otherwise reverse it and return false.
					bool afterCheck = isCheck(team);
					if(afterCheck)
					{
						addPiece(piece, from, to);
						tiles[to.getY()][to.getX()] = p;
						return false;
					}
					else
					{
						if(!isTileEmpty(to) && !isTileTeam(to, piece->getTeam()))
							delete p;
					}
					
					bool opponentChecked = isCheck(getEnemyTeam(team));
					if(opponentChecked)
					{
						std::cout << "Player " << getEnemyTeam(team) << " has been checked\n";
					}
					
					//Mark pieces which has moved. Used for castelling and pawns moving two steps.
					if(!piece->hasMoved())
						piece->setMoved(true);
					
					return true;
				}
			}
		}
	}
	
	return false;
}

//Exchange a pawn for a queen if it has reached the other side of the board
//Return true if the transformation was successful
bool Board::pawnToQueen(Position position)
{
	if(doesTileExist(position) && !isTileEmpty(position))
	{
		int team = tiles[position.getY()][position.getX()]->getTeam();
		
		if((team == WHITE && position.getY() == 0) || (team == BLACK && position.getY() == B_SIZE - 1))
		{
			removePiece(position);
			Queen *newQueen = new Queen(team);
			tiles[position.getY()][position.getX()] = newQueen;
			return true;
		}
	}
	
	return false;
}

//See if a player is checked
bool Board::isCheck(int team, bool printDebug) const
{
	Position kingPos;
	bool kingFound = false;
	
	//Find the king
	for(int i = 0; i < B_SIZE; i++)
	{
		for(int j = 0; j < B_SIZE; j++)
		{
			Position pos = Position(j, i);
			if(!isTileEmpty(pos) && tiles[i][j]->getRepresentation() == 'K' && tiles[i][j]->getTeam() == team)
			{
				kingPos = pos;
				kingFound = true;
				break;
			}
		}
		if(kingFound)
			break;
	}
	
	//No king found
	if(!kingFound)
		return false;
	else if(printDebug)
		std::cout << "King found for team " << team << " at position " << kingPos.toString() << std::endl;
	
	//See if the king is threatened and checked
	std::vector<Position> threatenedPositions = getThreatenedPositions(team);
	for(std::vector<Position>::iterator it = threatenedPositions.begin(); it != threatenedPositions.end(); it++)
	{
		if(*it == kingPos)
		{
			return true;
		}
	}
	
	if(printDebug)
	{
		std::cout << "King not found in area:\n";
		renderHighlightedPosiotions(threatenedPositions);
		
	}
	
	//THIS AINT GONNA WORK :V
	
	//If all tiles near the king is either friendly or threatened the king is checkmate
	//This will be problematic as we also need to check what pieces the king can kill to stay safe.
	//Will add that... some other time.
	/*std::vector<Position> deniedPositions;
	for(int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for(int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if(xOffset != 0 || yOffset != 0)
			{
				Position p = Position(kingPos.getX() + xOffset, kingPos.getY() + yOffset);
				
				//Is the tile on the board
				if(!doesTileExist(p))
				{
					deniedPositions.push_back(p);
				}
				//If the piece at the tile is friendly, 
				else if(isTileTeam(p, team))
				{
					deniedPositions.push_back(p);
				}
				//Check if tiles the king can move to are threatened
				else if(isTileEmpty(p))
				{
					for(std::vector<Position>::iterator it; it != threatenedPositions.end(); it++)
					{
						if(*it == p)
						{
							deniedPositions.push_back(p);
							break;
						}
					}
				}
				//TODO
				//Else if tile is enemy team, check if the king can kill that piece and move there.
				//This will probably require either a copy of the board to be made, or changes made and then reverted
				//since enemy pieces will not move onto another enemy piece.
			}
		}
	}
	
	//If all positions around the king are denied, and the king is check, the king is instead put in checkmate
	if(res == 1  && deniedPositions.size() == 8)
		res = 2;*/
		
	return false;
}

//Find all threatened positions for a team.
std::vector<Position> Board::getThreatenedPositions(int team) const
{
	int enemyTeam = getEnemyTeam(team);
		
	std::vector<Position> enemyMovable;
		
	//Get all tiles the enemy team can move to
	for(int i = 0; i < B_SIZE; i++)
	{
		for(int j = 0; j < B_SIZE; j++)
		{
			Position currentPos = Position(j, i);
			if(!isTileEmpty(currentPos) && tiles[i][j]->getTeam() == enemyTeam)
			{
				std::vector<Position> thisMovable;
				if(tiles[i][j]->getRepresentation() == 'P')
				{
					thisMovable = ((Pawn *) tiles[i][j])->getAttackableTiles(currentPos, this);
				}
				else
					thisMovable = getMovable(currentPos);

				enemyMovable.insert(enemyMovable.end(), thisMovable.begin(), thisMovable.end());
			}
		}
	}
	
	//Remove duplicates
	std::sort(enemyMovable.begin(), enemyMovable.end());
	enemyMovable.erase(unique(enemyMovable.begin(), enemyMovable.end()), enemyMovable.end());
	
	return enemyMovable;
}

//Return the other team
int Board::getEnemyTeam(int team) const
{
	int enemyTeam = WHITE;
	if(team == WHITE)
		enemyTeam = BLACK;
	return enemyTeam;
}