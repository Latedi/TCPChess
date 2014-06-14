#ifndef GAME_H
#define GAME_H

#define PLAYERS 2
#define COMMANDNUM 2
#define CHARMODIFIER 96
#define INTMODIFIER 48
#define G_SIZE 9

#include "board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <istream>
#include <vector>
 	
class Game
 {
private:
 	Board *board;
	Position stringToPosition(std::string word);
 public:
 	Game();
	~Game();
	void play();
	bool parse(std::string &input);
 };
 	
 #endif /* GAME_H */