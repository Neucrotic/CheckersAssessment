#pragma once
#include "Board.h"

class Agent
{
public:

	Agent(uint _difficulty, Board* _boardToPlayOn);
	~Agent(){}

	void Update(double _dt);

private:

	uint difficulty;
	Board* realBoard;

	Move ChooseMoves(std::vector<Move> _validMoves, Board* _board);
	void MakeMove(Move _move, Board* _board);
	bool PlayGame(Board* _board);

	uint RunBranch(Move _move);
};