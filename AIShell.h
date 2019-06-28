#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include "Move.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int AI_PIECE = 1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE = 0;
	static const int NEG_INF = -2147483647;
	static const int POS_INF = 2147483647;


private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	int self; //which piece the ai is.
	int opponent; //which piece the opponent is.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	int winner; //winner of game
	int spacesLeft; //spaces left on board
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.

public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move minimax(int player, int depth, int alpha, int beta);
	Move makeMove(bool isFirstPlayer);
	int checkWinner();
	int inARow(int player);
	void block(std::vector<Move> &possibleMoves);
};

#endif //AISHELL_H
