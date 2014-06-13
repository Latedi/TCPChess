#ifndef GAME_H
#define GAME_H

#define PLAYERS 2
#define COMMANDNUM 2

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
 public:
 	Game();
	~Game();
	void play();
	bool parse(std::string &input);
 };
 	
 #endif /* GAME_H */