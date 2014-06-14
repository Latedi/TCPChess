#include "game.h"

Game::Game()
{
	board = new Board();
}

Game::~Game()
{
	delete board;
}

//Start the game. main loop
void Game::play()
{
	bool gameOver = false;
	bool validInput;
	int currentPlayer = WHITE;
	std::string input = "";
	
	//keep prompting for input until the user quits or the game ends
	while(!gameOver)
	{
		validInput = false;
		board->renderBoard();
		while(!validInput)
		{
			std::cout << "Please enter a move player " << currentPlayer + 1 << " (type 'quit' to exit)\n";
			std::getline(std::cin,input);
			validInput = parse(input, currentPlayer);
		}
		changeTeam(currentPlayer);
		gameOver = board->gameOver();
	}
	std::cout << "GG\n";
	return;
}

//Parse input and execute if valid
bool Game::parse(std::string &input, int team)
{
	std::vector<std::string> commandWords;
	std::stringstream ss(input);
	char delim = ' ';
    std::string token;
	
	//break the inputted command in to separate words
    while (std::getline(ss, token, delim)) {
        commandWords.push_back(token);
    }
	//parse move command
	if(commandWords[0] == "move")
	{
		//check that we have the correct number of arguments
		//valid move command format is "move <co> <co>" where <co> is a co-ordinate e.g. "c4"
		if(commandWords.size() != 3) 
		{
			std::cout << "Error: incorrect number of arguments.\n";
			return false;
		}
		//check that both arguments take a valid form
		for(int i = 1; i <= 2; i++)
		{
			if(commandWords[i].length() != 2)
			{
				std::cout << "Error: '" << commandWords[i] << "' is not a valid co-ordinate\n";
				return false;
			}
			if((commandWords[i].at(0) < 'a') || (commandWords[i].at(0) > 'h'))
			{
				std::cout << "Error: '" << commandWords[i] << "' is not a valid co-ordinate\n";
				return false;
			}
			if((commandWords[i].at(1) < '1') || (commandWords[i].at(1) > '8'))
			{
				std::cout << "Error: '" << commandWords[i] << "' is not a valid co-ordinate\n";
				return false;
			}
		}
		
		//The input is valid, try to execute the move
		return executeMove(commandWords[1], commandWords[2], team);
	}
	//parse castle command
	else if(commandWords[0] == "castle")
	{
		std::cout << "u gon castle son\n";
		return true;
	}
	//get help
	else if(commandWords[0] == "help")
	{
		printHelp();
		return false;
	}
	//quit the game
	else if(commandWords[0] == "quit")
	{
		exit(0);
	}
	else
	{
		std::cout << "Error: '" << commandWords[0] << "' is not a valid command\n";
		return false;
	}
	
	return true;
}

//Try to move a piece from one tile to another
bool Game::executeMove(std::string p1, std::string p2, int team)
{
	Position origin = inputToPosition(p1);
	Position destination = inputToPosition(p2);
	
	if(board->isTileTeam(origin, team))
	{
		std::vector<Position> movable = board->getMovable(origin);
		board->printPositionVector(movable);
	}
	
	return true;
}

//Change player who gets to input commands
void Game::changeTeam(int &team)
{
	if(team == WHITE)
		team = BLACK;
	else
		team = WHITE;
}

//Display available commands
void Game::printHelp()
{
	std::cout << "lul tough luck son\n";
}

//Translate input to a board position
Position Game::inputToPosition(std::string coordinate)
{
	int xOffset = (int) 'a';
	int x = (int) coordinate[0] - xOffset;
	int yOffset = (int) '1';
	int y = (int) 7 - (coordinate[1] - yOffset);
	return Position(x, y);
}

std::string Game::PositionToString(Position position)
{
	char x = (char) (position.getX() + (int) 'a');
	char y = (char) (7 + position.getY() + (int) '1');
	std::stringstream ss;
	std::string res;
	ss << x << y;
	ss >> res;
	return res;
}