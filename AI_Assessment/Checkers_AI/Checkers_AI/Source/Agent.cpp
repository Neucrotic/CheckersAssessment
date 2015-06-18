#include <thread>
#include "Agent.h"

Agent::Agent(uint _difficulty, Board* _boardToPlayOn)
{
	difficulty = _difficulty;
	realBoard = _boardToPlayOn;
}

Move Agent::ChooseMoves(std::vector<Move> _validMoves, Board* _board)
{
	for (int i = 0; i < _validMoves.size(); i++)
	{
		Board* newBoard = _board->Clone();

		MakeMove(_validMoves[i], newBoard);
	}

	Move move;
	return move;
}

void Agent::MakeMove(Move _move, Board* _board)
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

	return true;
}

uint Agent::RunBranch(Move _move)
{
	uint score;

	Board* clone = realBoard->Clone();

	MakeMove(_move, clone);
	bool myTurn = false;

	while (!clone->gameOver)
	{
		uint randNumX = rand() % BOARD_LENGTH;
		uint randNumY = rand() % BOARD_LENGTH;

		clone->CountPieces();
		if (clone->numRed <= 0)
		{
			clone->gameOver = true;
		}
		else if (clone->numWhite <= 0)
		{
			clone->gameOver = true;
			score++;
		}
		clone->UpgradePieces();

		if (myTurn)
		{
			uint index = clone->GetRandomWhitePiece();
			glm::ivec2 pos = clone->GetPositionFromIndex(index);
			std::vector<Move> optionalMoves;

			optionalMoves = clone->GetValidMoves(pos.x, pos.y);
			uint someNum = rand() % 7;

			for (int i = 0; i < someNum; i++)
			{
				if (i == someNum)
				{
					Move myMove;
					myMove.X = optionalMoves[i].X;
					myMove.Y = optionalMoves[i].Y;
					myMove.jumpedIndex = optionalMoves[i].jumpedIndex;
					myMove.oldIndex = optionalMoves[i].oldIndex;

					MakeMove(myMove, clone);
					myTurn = false;
				}
			}
		}
		else
		{
			uint index = clone->GetRandomRedPiece();
			glm::ivec2 pos = clone->GetPositionFromIndex(index);
			std::vector<Move> optionalMoves;

			optionalMoves = clone->GetValidMoves(pos.x, pos.y);
			uint someNum = rand() % 7;

			for (int i = 0; i < someNum; i++)
			{
				if (i == someNum)
				{
					Move myMove;
					myMove.X = optionalMoves[i].X;
					myMove.Y = optionalMoves[i].Y;
					myMove.jumpedIndex = optionalMoves[i].jumpedIndex;
					myMove.oldIndex = optionalMoves[i].oldIndex;

					MakeMove(myMove, clone);
					myTurn = false;
				}
			}
		}
	}

	return score;
}