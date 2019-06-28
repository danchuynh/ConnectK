#include "AIShell.h"
#include <iostream>


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove){
	this->deadline = 0;
	this->numRows = numRows;
	this->numCols = numCols;
	this->gravityOn = gravityOn;
	this->gameState = gameState;
	this->lastMove = lastMove;
	this->spacesLeft = numRows * numCols - 1;
	this->winner = -2;
	this->self = 0;
	this->opponent = 0;
}


AIShell::~AIShell(){
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;
}


int AIShell::checkWinner(){
	//Checks for and returns a winner if there is one
	int width = numCols;
	int height = numRows;
	int count;
	bool uncached = false;
	if (winner == -2){
		for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				std::cout.flush();
				if(gameState[i][j] == 0){
					if(gravityOn)
						break;
					else
						continue;
				}
				//check horizontal
				if(i - 1 < 0 || (gameState[i-1][j] != gameState[i][j])){
					count = 1;
					while((i + count < width) && (gameState[i][j] == gameState[i + count][j])){
						count += 1;
						if(count >= k){
							winner = gameState[i][j];
							uncached = true;
							break;
						}

					if (uncached)
						break;
					}
				}
				//diagonal
				if(i - 1 < 0 || j - 1 < 0 || (gameState[i-1][j-1] != gameState[i][j])){
					count = 1;
					while((i + count < width) && (j + count < height) && (gameState[i][j] == gameState[i+count][j+count])){
						count += 1;
						if(count >= k){
							winner = gameState[i][j];
							uncached = true;
							break;
						}

					if (uncached)
						break;
					}
				}
				//diagonal
				if((i - 1 < 0) || (j + 1 >= height) || (gameState[i-1][j+1] != gameState[i][j])){
					count = 1;
					while((i + count < width) && (j - count >= 0) && (gameState[i][j] == gameState[i+count][j-count])){
						count += 1;
						if(count >= k){
							winner = gameState[i][j];
							uncached = true;
							break;
						}

					if (uncached)
						break;
					}
				}
				//vertical
				if(j - 1 < 0 || (gameState[i][j-1] != gameState[i][j])){
					count = 1;
					while((j + count < height) && (gameState[i][j] == gameState[i][j+count])){
						count += 1;
						if(count >= k){
							winner = gameState[i][j];
							uncached = true;
							break;
						}

					if (uncached)
						break;
					}
				}
			}

			if (uncached)
				break;
		}

		if (!uncached){
			//std::cout<< "spaces left: " << spacesLeft << std::endl;
			if(spacesLeft > 0)
				winner = -2;
			else
				winner = 0; //tie
		}
	}
	return winner;
}

int AIShell::inARow(int player){
	//give points for being in a row
	int width = numCols;
	int height = numRows;
	int count = 0; //count also works as score

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			std::cout.flush();
			if(gameState[i][j] == 0){
				if(gravityOn)
					break;
				else
					continue;
			}
			//check horizontal
			if(i - 1 < 0 || (gameState[i-1][j] != player)){
				//count = 1;
				while((i + count < width) && (player == gameState[i + count][j])){
					count += 1;
				}
			}
			//diagonal
			if(i - 1 < 0 || j - 1 < 0 || (gameState[i-1][j-1] != player)){
				//count = 1;
				while((i + count < width) && (j + count < height) && (player == gameState[i+count][j+count])){
					count += 1;
				}
			}
			//diagonal
			if((i - 1 < 0) || (j + 1 >= height) || (gameState[i-1][j+1] != player)){
				//count = 1;
				while((i + count < width) && (j - count >= 0) && (player == gameState[i+count][j-count])){
					count += 1;
				}
			}
			//vertical
			if(j - 1 < 0 || (gameState[i][j-1] != player)){
				//count = 1;
				while((j + count < height) && (player == gameState[i][j+count])){
					count += 1;
				}
			}
		}
	}
	return count;
}

void AIShell::block(std::vector<Move> &possibleMoves){
	//tries to block opponent by giving more points to space that does the blocking
	int width = numCols;
	int height = numRows;
	int count = 0; //count also works as score

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			std::cout.flush();
			if(gameState[i][j] == 0){
				if(gravityOn)
					break;
				else
					continue;
			}
			//check horizontal
			if(i - 1 < 0 || (gameState[i-1][j] != opponent)){
				//count = 1;
				while((i + count < width) && (opponent == gameState[i + count][j])){
					count += 1;
					if(count >= k-2){
						for(std::vector<Move>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
						    if(it->col == i+count && it->row == j){
						    	it->score += 100;
						    }
						}
						break;
					}
				}
			}
			//diagonal forward slash
			if(i - 1 < 0 || j - 1 < 0 || (gameState[i-1][j-1] != opponent)){
				//count = 1;
				while((i + count < width) && (j + count < height) && (opponent == gameState[i+count][j+count])){
					count += 1;
					if(count >= k-2){
						for(std::vector<Move>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
							if(it->col == i+count && it->row == j+count){
								it->score += 100;
							}
						}
						break;
					}
				}
			}
			//diagonal backward slash
			if((i - 1 < 0) || (j + 1 >= height) || (gameState[i-1][j+1] != opponent)){
				//count = 1;
				while((i + count < width) && (j - count >= 0) && (opponent == gameState[i+count][j-count])){
					count += 1;
					if(count >= k-2){
						for(std::vector<Move>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
							if(it->col == i+count && it->row == j-count){
								it->score += 100;
							}
						}
						break;
					}
				}
			}
			//vertical
			if(j - 1 < 0 || (gameState[i][j-1] != opponent)){
				//count = 1;
				while((j + count < height) && (opponent == gameState[i][j+count])){
					count += 1;
					if(count >= k-2){
						for(std::vector<Move>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
							if(it->col == i && it->row == j+count){
								it->score += 100;
							}
						}
						break;
					}
				}
			}
		}
	}
}

//Move AIShell::oldminimax(int player, int depth, int alpha, int beta){
//	//depth++;
//	int winner = checkWinner(); //checks for winner. modified from python source
//	if(winner == self){ //if winner is AI, we give the move 10 points
//		//std::cout << "ai wins\n" << std::endl;
//		return Move(0,0,100);
//	}
//	else if(winner == opponent){ //if winner is other player, we give the move -10 points
//		//std::cout << "human wins\n" << std::endl;
//		return Move(0,0,-100);
//	}
//	else if(winner == 0){ //if there is no winner, we get 0 points.
//		//std::cout << "no winner\n" << std::endl;
//		return Move(0,0,0);
//	}
//
//	std::vector<Move> moves; //holds all the moves
//
//	for(int i = 0; i < numCols; i++){
//		for(int j = 0; j < numRows; j++){
//			if(gameState[i][j] == NO_PIECE){ //if no piece then make move and traverse down tree via recursion
//				std::cout.flush();
//				Move m(i, j, 0);
//				gameState[i][j] = player;
//				spacesLeft--; //minus one from total spaces left on board
//				if(player == self){
//					m.score += inARow(self);
//					m.score += minimax(opponent, depth, alpha, beta).score;
//				}
//				else{
//					m.score += inARow(opponent) * -1;
//					m.score += minimax(self, depth, alpha, beta).score;
//				}
//
//				moves.push_back(m); //puts move into list
//				spacesLeft++; //plus one to total spaces left
//				gameState[i][j] = NO_PIECE; //set piece back to normal
//			}
//		}
//	}
//
//	int bestMoveIndex = 0;
//	int bestScore = 0;
//
//	//min max part to check for best score in list of moves
//	if(player == self){
//		bestScore = NEG_INF;
//		for(int i = 0; i < moves.size(); i++){
//			if(moves[i].score > bestScore){
//				bestMoveIndex = i;
//				bestScore = moves[i].score;
//			}
//		}
//	}else{
//		bestScore = POS_INF;
//		for(int i = 0; i < moves.size(); i++){
//			if(moves[i].score < bestScore){
//				bestMoveIndex = i;
//				bestScore = moves[i].score;
//			}
//		}
//	}
//
//	for(int i = 0; i < moves.size(); i++){
//		std::cout << moves[i].col << " " << moves[i].row << " " << moves[i].score << std::endl;
//	}
//	std::cout << "best move: " << moves[bestMoveIndex].col << " " << moves[bestMoveIndex].row << " " << moves[bestMoveIndex].score << std::endl;
//	spacesLeft--; //minus one to total spaces left
//
//	return moves[bestMoveIndex];
//}

Move AIShell::minimax(int player, int depth, int alpha, int beta){
	//depth++;
	int winner = checkWinner(); //checks for winner. modified from python source
	if(winner == self){ //if winner is AI, we give the move 100 points
		return Move(0,0,10);
	}
	else if(winner == opponent){ //if winner is other player, we give the move -100 points
		return Move(0,0,-10);
	}
	else if(winner == 0){ //if there is no winner, we get 0 points.
		return Move(0,0,0);
	}

	std::vector<Move> possibleMoves; //holds all the moves
	for(int i = 0; i < numCols; i++){
		for(int j = 0; j < numRows; j++){
			if(gameState[i][j] == NO_PIECE)
				possibleMoves.push_back(Move(i,j,NEG_INF));
		}
	}

	if (player == self){
		Move best(0,0,NEG_INF); //best move
		for(int i = 0; i < possibleMoves.size(); i++){
			gameState[possibleMoves[i].col][possibleMoves[i].row] = self;
			spacesLeft--;
			possibleMoves[i].score = minimax(opponent,depth,alpha,beta).score;
			possibleMoves[i].score += inARow(self);
			block(possibleMoves);
			best = (possibleMoves[i].score > best.score ? best = possibleMoves[i] : best = best);

			alpha = (alpha > possibleMoves[i].score ? alpha = alpha : alpha = possibleMoves[i].score);
			if(beta <= alpha){
				gameState[possibleMoves[i].col][possibleMoves[i].row] = NO_PIECE;
				spacesLeft++;
				break;
			}

			gameState[possibleMoves[i].col][possibleMoves[i].row] = NO_PIECE;
			spacesLeft++;
		}
		return best;
	}else{
		Move best(0,0,POS_INF); //best move
		for(int i = 0; i < possibleMoves.size(); i++){
			gameState[possibleMoves[i].col][possibleMoves[i].row] = opponent;
			spacesLeft--;
			possibleMoves[i].score = minimax(self,depth,alpha,beta).score;
			possibleMoves[i].score += inARow(opponent) * -1;
			best = (possibleMoves[i].score < best.score ? best = possibleMoves[i] : best = best);

			beta = (beta < possibleMoves[i].score ? beta = beta : beta = possibleMoves[i].score);
			if(beta <= alpha){
				gameState[possibleMoves[i].col][possibleMoves[i].row] = NO_PIECE;
				spacesLeft++;
				break;
			}

			gameState[possibleMoves[i].col][possibleMoves[i].row] = NO_PIECE;
			spacesLeft++;
		}
		return best;
	}
}

Move AIShell::makeMove(bool isFirstPlayer){
	if(isFirstPlayer){
		self = AI_PIECE;
		opponent = HUMAN_PIECE;
		return minimax(AI_PIECE,0,NEG_INF,POS_INF);
	}else{
		self = HUMAN_PIECE;
		opponent = AI_PIECE;
		return minimax(HUMAN_PIECE,0,NEG_INF,POS_INF);
	}
}
