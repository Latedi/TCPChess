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

//If the expectedOutcome parameter is passed as false, the input command is meant to fail. For example this
//can be used to test if pieces can attack allied pieces or move to a position they should not be able to.
void executeMove(std::string p1, std::string p2, int team, Board *board, bool expectedOutcome = true)
{
	Position from = stringToPosition(p1);
	Position to = stringToPosition(p2);
	
	bool res = board->movePiece(from, to, team);
	
	if(res != expectedOutcome) {
		std::cout << "Move from " << p1 << " to " << p2 << " did not get expected outcome.\n";
		board->renderBoard();
		exit(-1);
	}
	
	return;
}

//Tests the king and check
void kingTest(Board *board)
{
	executeMove("e2", "e3", WHITE, board);
	executeMove("e7", "e5", BLACK, board);
	executeMove("e1", "e2", WHITE, board);
	executeMove("e8", "e7", BLACK, board);
	executeMove("e2", "d3", WHITE, board);
	executeMove("e7", "d6", BLACK, board);
	executeMove("e2", "d3", WHITE, board, false);
	executeMove("d3", "c4", WHITE, board);
	executeMove("d6", "d5", BLACK, board, false);
	executeMove("b7", "b5", BLACK, board);
	executeMove("c4", "b5", WHITE, board);
	executeMove("b8", "a6", BLACK, board);
	executeMove("b5", "c4", WHITE, board);
	executeMove("a8", "b8", BLACK, board);
	executeMove("c4", "c3", WHITE, board);
	executeMove("c8", "b7", BLACK, board);
	executeMove("c3", "b3", WHITE, board);
	executeMove("b7", "c6", BLACK, board);
	executeMove("b3", "b4", WHITE, board, false);
	executeMove("f1", "b5", WHITE, board);
	executeMove("c6", "b7", BLACK, board);
	executeMove("b5", "f1", WHITE, board);
	executeMove("b7", "d5", BLACK, board);
	executeMove("f1", "b5", WHITE, board, false);
	executeMove("f1", "c4", WHITE, board, false);
	executeMove("b3", "b4", WHITE, board, false);
	executeMove("b3", "c4", WHITE, board, false);
	executeMove("b3", "a3", WHITE, board);
}

//Also tests pawns which turned into queens
void queenTest(Board *board)
{
	executeMove("e2", "e3", WHITE, board);
	executeMove("e7", "e6", BLACK, board);
	executeMove("d1", "g4", WHITE, board);
	executeMove("d8", "g5", BLACK, board);
	executeMove("g4", "b4", WHITE, board);
	executeMove("g5", "g2", BLACK, board);
	executeMove("b4", "b7", WHITE, board);
	executeMove("g2", "d2", BLACK, board, false);
	executeMove("g2", "g7", BLACK, board, false);
	executeMove("g2", "g8", BLACK, board, false);
	executeMove("g2", "g1", BLACK, board);
	executeMove("b7", "b8", WHITE, board);
	executeMove("g1", "h1", BLACK, board);
	executeMove("b8", "a8", WHITE, board);
	
	executeMove("g7", "g5", BLACK, board);
	executeMove("b2", "b4", WHITE, board);
	executeMove("g5", "g4", BLACK, board);
	executeMove("b4", "b5", WHITE, board);
	executeMove("g4", "g3", BLACK, board);
	executeMove("b5", "b6", WHITE, board);
	executeMove("g3", "g2", BLACK, board);
	executeMove("b6", "b7", WHITE, board);
	executeMove("g2", "g1", BLACK, board);
	executeMove("b7", "b8", WHITE, board);
	
	executeMove("h1", "a8", BLACK, board);
	executeMove("b8", "a8", WHITE, board);
	executeMove("g1", "g4", BLACK, board);
	executeMove("a8", "a7", WHITE, board);
	executeMove("g4", "a4", BLACK, board);
	executeMove("a7", "a4", WHITE, board);
	executeMove("c7", "c6", BLACK, board);
	executeMove("a4", "b5", WHITE, board);
	executeMove("c6", "b5", BLACK, board);
	
	return;
}

void bishopTest(Board *board)
{
	executeMove("e2", "e4", WHITE, board);
	executeMove("e7", "e5", BLACK, board);
	executeMove("d2", "d4", WHITE, board);
	executeMove("b7", "b6", BLACK, board);
	executeMove("c1", "g5", WHITE, board);
	executeMove("f8", "c5", BLACK, board);
	executeMove("g5", "d8", WHITE, board);
	executeMove("c5", "d4", BLACK, board);
	executeMove("f1", "a6", WHITE, board);
	executeMove("c8", "a6", BLACK, board);
	executeMove("d8", "f6", WHITE, board);
	executeMove("d4", "b2", BLACK, board);
	executeMove("f6", "b2", WHITE, board, false);
	executeMove("f6", "e5", WHITE, board);
	executeMove("a6", "e2", BLACK, board);
	executeMove("e5", "b2", WHITE, board);
	executeMove("e2", "f3", BLACK, board);
	executeMove("b2", "a1", WHITE, board, false);
	executeMove("g2", "f3", WHITE, board);
	
	return;
}

void rookTest(Board *board)
{
	executeMove("a2", "a4", WHITE, board);
	executeMove("a7", "a5", BLACK, board);
	executeMove("h2", "h4", WHITE, board);
	executeMove("h7", "h5", BLACK, board);
	executeMove("a1", "a3", WHITE, board);
	executeMove("a8", "a6", BLACK, board);
	executeMove("h1", "h3", WHITE, board);
	executeMove("h8", "h6", BLACK, board);
	executeMove("a3", "b3", WHITE, board);
	executeMove("a6", "c6", BLACK, board);
	executeMove("h3", "f3", WHITE, board);
	executeMove("h6", "g6", BLACK, board);
	executeMove("b3", "b7", WHITE, board);
	executeMove("c6", "c2", BLACK, board);
	executeMove("f3", "f7", WHITE, board);
	executeMove("g6", "g2", BLACK, board);
	executeMove("b7", "c7", WHITE, board);
	executeMove("c2", "c7", BLACK, board);
	executeMove("e2", "e4", WHITE, board);
	executeMove("g2", "d2", BLACK, board, false);
	executeMove("g2", "g7", BLACK, board, false);
	executeMove("g2", "g3", BLACK, board);
	executeMove("f7", "g7", WHITE, board);
	executeMove("g3", "g4", BLACK, board);
	executeMove("g7", "g4", WHITE, board);
	executeMove("h5", "g4", BLACK, board);
	
	return;
}

void knightTest(Board *board)
{
	executeMove("b1", "c3", WHITE, board);
	executeMove("b8", "a6", BLACK, board);
	executeMove("g1", "h3", WHITE, board);
	executeMove("g8", "f6", BLACK, board);
	executeMove("c3", "a4", WHITE, board);
	executeMove("a6", "c5", BLACK, board);
	executeMove("h3", "f4", WHITE, board);
	executeMove("f6", "e4", BLACK, board);
	executeMove("a4", "c5", WHITE, board);
	executeMove("e4", "d2", BLACK, board);
	executeMove("c5", "b3", WHITE, board);
	executeMove("d2", "b3", BLACK, board);
	executeMove("a2", "b3", WHITE, board);
	
	return;
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
	
	return;
}

int main(int argc, char* argv[])
{
	std::cout << "\nTesting pawns:\n";
	Board *board = new Board();
	pawnTest(board);
	board->renderBoard();
	delete board;
	
	std::cout << "\nTesting Knights:\n";
	board = new Board();
	knightTest(board);
	board->renderBoard();
	delete board;
	
	std::cout << "\nTesting Rooks:\n";
	board = new Board();
	rookTest(board);
	board->renderBoard();
	delete board;
	
	std::cout << "\nTesting Bishops:\n";
	board = new Board();
	bishopTest(board);
	board->renderBoard();
	delete board;
	
	std::cout << "\nTesting Queens:\n";
	board = new Board();
	queenTest(board);
	board->renderBoard();
	delete board;
	
	std::cout << "\nTesting Kings:\n";
	board = new Board();
	kingTest(board);
	board->renderBoard();
	delete board;
	
 	return 0;
}