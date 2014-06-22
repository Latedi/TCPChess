#include "game.h"

Game::Game(Networking *network, int myTeam)
{
	this->network = network;
	this->myTeam = myTeam;
	board = new Board();
	xOffset = (int) 'a';
	yOffset = (int) '1';
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
		
		if(currentPlayer == myTeam)
		{
			//If it's this player's turn, get input, process it and if valid, send to the other player
			while(!validInput)
			{
				std::cout << "Please enter a move (type 'help' for a list of commands)\n";
				std::getline(std::cin,input);
				validInput = parse(input, currentPlayer);
				if(validInput)
					network->sendData(input);
			}
		}
		else
		{
			//If it's the other player's turn, receive input until it is valid
			while(!validInput)
			{
				input = network->receiveData();
				if(input == "")
				{
					std::cout << "Your opponent disconnected\n";
					exit(0);
				}
				validInput = parse(input, currentPlayer);
			}
		}
		
		//Change player and see if there's a checkmate
		changeTeam(currentPlayer);
		gameOver = board->isChekmate(currentPlayer);
		if(gameOver)
		{
			std::cout << "Checkmate. Player " << board->getEnemyTeam(currentPlayer) << " wins!\n";
			network->disconnect();
			exit(0);
		}
	}
	
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
	else if(commandWords[0] == "0-0" || commandWords[0] == "O-O" || commandWords[0] == "0-0-0" || commandWords[0] == "O-O-O")
	{
		return executeMove(commandWords[0], "", team);
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
		if(team == myTeam)
			network->sendData("quit");
		else
			std::cout << "Your opponent disconnected\n";
		network->disconnect();
		exit(0);
	}
	else
	{
		std::cout << "Error: '" << commandWords[0] << "' is not a valid command\n";
		return false;
	}
	
	return false;
}

//Try to move a piece from one tile to another
bool Game::executeMove(std::string p1, std::string p2, int team)
{
	//We use different commands for moving and castling to both sides
	bool res = false;
	if(p2 != "")
	{
		Position from = stringToPosition(p1);
		Position to = stringToPosition(p2);
		res = board->movePiece(from, to, team);
	}
	else if(p1 == "0-0" || p1 == "O-O")
	{
		res = board->castle(team, true);
	}
	else if(p1 == "0-0-0" || p1 == "O-O-O")
	{
		res = board->castle(team, false);
	}
	
	return res;
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
	std::cout << "Available commands\n'Move <c1> <c2>' where <c1> is a valid tile with a piece you own and <c2> is a valid"
				"tile to which <c1> can move.\nCastling is done with either '0-0' (kingside) or '0-0-0' (queenside). 'O' can"
				" be used instead of zeros.\n'quit' to exit the game.\n'help' to print this message.\n";
}

//Translate input to a board position. Keep this in comments if something goes wrong.
/* Position Game::inputToPosition(std::string coordinate)
{
	int xOffset = (int) 'a';
	int x = (int) coordinate[0] - xOffset;
	int yOffset = (int) '1';
	int y = (int) 7 - (coordinate[1] - yOffset);
	return Position(x, y);
} */ 

//translates inputted string to position. e.g. string "a1" becomes Position(0,0)
Position Game::stringToPosition(std::string word)
{
	//change chars from ASCII values to the correct int value
	int x = (int) word.at(0) - xOffset;
	int y = (int) word.at(1) - yOffset;

	//reverse the y co-ordinate because the array is stored in reverse order to the way the board is labelled
	y = B_SIZE - y - 1;
	Position position(x, y);
	return position;
}