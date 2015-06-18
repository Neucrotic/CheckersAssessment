#pragma once
#include "Board.h"

class Agent
{
public:

	Agent(uint _difficulty);
	~Agent(){}

	void Update(double _dt);

private:

	uint difficulty;

	Move ChooseMoves(std::vector<Move> _validMoves, Board* _board);
	void MakeMove(Move _move, Board* _board);
	bool PlayGame(Board* _board);
};