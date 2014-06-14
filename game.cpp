#include "game.h"

Game::Game()
{
	board = new Board();
}

Game::~Game()
{
	delete board;
}

void Game::play()
{
	bool gameOver = false;
	std::string input = "";

	Position from(0,0);
	Position to(4,4);

	std::cout << "testing add/remove\n";
	board.movePiece(from, to);
	board.renderBoard();
	
	//keep prompting for input until the user quits or the game ends
	while(!gameOver)
	{
		std::cout << "Please enter a move (type 'quit' to exit)\n";
		std::getline(std::cin,input);
		gameOver = parse(input);
	}
	std::cout << "GG\n";
	return;
}
	
bool Game::parse(std::string &input)
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
		std::cout << "Moving from " << commandWords[1] << " to " << commandWords[2] << "\n";
		//replace cout with call to command execution
	}
	//parse castle command
	else if(commandWords[0] == "castle")
	{
		std::cout << "u gon castle son\n";
	}
	//quit the game
	else if(commandWords[0] == "quit")
	{
		return true;
	}
	else
	{
		std::cout << "Error: '" << commandWords[0] << "' is not a valid command\n";
	}
	return false;
}


