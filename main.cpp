#include <iostream>

#include "game.h"

//Prompt the user for an IP address to connect to
std::string getIP()
{
	std::cout << "Input the IP address you want to connect to:\n";
	std::string input;
	std::getline(std::cin, input);
	
	return input;
}

//Prompt the user for a port to use
int getPort()
{
	std::cout << "Input what port you want to host at or connect to:\n";
	std::string input;
	std::getline(std::cin, input);
	int port = atoi(input.c_str());
	
	std::cout << "Port set to: " << port << std::endl;
	return port;
}

//To make things simpler, the host will always be white and the client will always be black
int main(int argc, char* argv[])
{
	std::string input;
	Game *game = NULL;
	Networking *network = NULL;
	
	while(input != "quit")
	{
		std::cout << "Welcome to TCP Chess. Input 'host' to host a game or 'connect' to"
			" connect to a game. You can also exit by typing 'quit'.\n";
		std::getline(std::cin, input);
			
		if(input == "host")
		{
			network = new Networking(getPort());
			network->host();
			game = new Game(network, WHITE);
			game->play();
		}
		else if(input == "connect")
		{
			network = new Networking(getPort());
			network->connect(getIP());
			game = new Game(network, BLACK);
			game->play();
		}
	}

	delete game;
	delete network;
	
 	return 0;
}