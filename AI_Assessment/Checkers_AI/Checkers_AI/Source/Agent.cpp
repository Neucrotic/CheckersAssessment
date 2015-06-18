#include <thread>
#include "Agent.h"

Agent::Agent(uint _difficulty)
{
	difficulty = _difficulty;
}

Move Agent::ChooseMoves(std::vector<Move> _validMoves, Board* _board)
{
	for (int i = 0; i < _validMoves.size(); i++)
	{
		Board* newBoard = _board->Clone();

		MakeMove(_validMoves[i], newBoard);
	}
}

void MakeMove(Move _move, Board* _board)
{
	SquareType piece = _board->GetPieceFromIndex(_move.oldIndex);
	_board->SetPiece(_move.X, _move.Y, piece);

	glm::ivec2 pos = _board->GetPositionFromIndex(_move.oldIndex);
	_board->SetPiece(pos.x, pos.y, SquareType::EMPTY);
}

bool Agent::PlayGame(Board* _board)
{
	while (_board->gameOver != true)
	{
		uint randIndex = rand() % BOARD_SIZE;
	}
}