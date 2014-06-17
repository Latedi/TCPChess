#include "board.h"
#include "position.h"

Position stringToPosition(std::string word)
{
	int xOffset = (int) 'a';
	int yOffset = (int) '1';
	int x = (int) word.at(0) - xOffset;
	int y = (int) word.at(1) - yOffset;

	y = B_SIZE - y - 1;
	Position position(x, y);
	
	return position;
}

void executeMove(std::string p1, std::string p2, int team, Board *board)
{
	Position from = stringToPosition(p1);
	Position to = stringToPosition(p2);
	
	bool res = board->movePiece(from, to, team);
	
	if(!res) {
		std::cout << "Failed to move from " << p1 << " to " << p2 << ". Existing\n";
		board->renderBoard();
		exit(-1);
	}
	
	return;
}

void generalTest(Board *board)
{
	executeMove("e2", "e4", WHITE, board);
	executeMove("e7", "e6", BLACK, board);
	executeMove("f1", "b5", WHITE, board);
	executeMove("a7", "a5", BLACK, board);
	return;
	
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e2", "e4", BLACK, board);
}

void pawnTest(Board *board)
{
	executeMove("a2", "a4", WHITE, board);
	executeMove("a7", "a6", BLACK, board);
	executeMove("b2", "b3", WHITE, board);
	executeMove("b7", "b5", BLACK, board);
	executeMove("c2", "c4", WHITE, board);
	executeMove("c7", "c6", BLACK, board);
	executeMove("d2", "d3", WHITE, board);
	executeMove("d7", "d5", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("e7", "e6", BLACK, board);
	executeMove("f2", "f3", WHITE, board);
	executeMove("f7", "f5", BLACK, board);
	executeMove("g2", "g4", WHITE, board);
	executeMove("g7", "g6", BLACK, board);
	executeMove("h2", "h3", WHITE, board);
	executeMove("h7", "h5", BLACK, board);
	
	executeMove("a4", "b5", WHITE, board);
	executeMove("a6", "b5", BLACK, board);
	executeMove("c4", "b5", WHITE, board);
	executeMove("c6", "b5", BLACK, board);
	executeMove("e4", "d5", WHITE, board);
	executeMove("f5", "g4", BLACK, board);
	executeMove("d5", "e6", WHITE, board);
	executeMove("g4", "f3", BLACK, board);
	executeMove("e6", "e7", WHITE, board);
	executeMove("e8", "d7", BLACK, board);
	executeMove("e7", "e8", WHITE, board);
	executeMove("d7", "c7", BLACK, board);
	executeMove("f1", "e2", WHITE, board);
	executeMove("f3", "f2", BLACK, board);
	executeMove("e1", "d2", WHITE, board);
	executeMove("f2", "f1", BLACK, board);
}

int main(int argc, char* argv[])
{
	Board *board = new Board();
	pawnTest(board);
	board->renderBoard();
	delete board;
	
	board = new Board();
	generalTest(board);
	board->renderBoard();
	delete board;
	
 	return 0;
}