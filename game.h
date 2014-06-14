#ifndef GAME_H
#define GAME_H

#define PLAYERS 2
#define COMMANDNUM 2

#include "board.h"
#include "position.h"

#include <string>
#include <iostream>
#include <sstream>
#include <istream>
#include <vector>

class Game
 {
private:
 	Board *board;
	int xOffset;
	int yOffset;
	bool parse(std::string &input, int team);
	bool executeMove(std::string p1, std::string p2, int team);
	void printHelp();
	//Position inputToPosition(std::string coordinate);
	void changeTeam(int &team);
	Position stringToPosition(std::string word);
 public:
 	Game();
	~Game();
	void play();
 };
 	
 #endif /* GAME_H */