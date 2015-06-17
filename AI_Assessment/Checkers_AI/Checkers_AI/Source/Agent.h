#pragma once
#include "Board.h"

class Agent
{
public:

	Agent(int _difficulty);
	~Agent(){}

private:

	Move ChooseMoves(std::vector<Move> _validMoves);

};