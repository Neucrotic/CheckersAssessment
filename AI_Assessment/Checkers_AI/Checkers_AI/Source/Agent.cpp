#include <thread>
#include <iostream>
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

	if (_move.jumpedIndex != -1)
	{
		glm::ivec2 posJ = _board->GetPositionFromIndex(_move.jumpedIndex);
		_board->SetPiece(posJ.x, posJ.y, SquareType::EMPTY);
	}
}

bool Agent::PlayGame(Board* _board)
{
	while (_board->gameOver != true)
	{
		uint randIndex = rand() % BOARD_SIZE;
	}

	return true;
}

void Agent::PlayTurn(double _dt)
{
	std::vector<Move> myMoves;
	std::vector<uint> moveScores;
	std::vector<Move> bestMoves;
	uint bestIndex = 0;

	myMoves = realBoard->GetAllPossibleWhiteMoves();

	for (int j = 0; j < myMoves.size(); j++)
	{
		moveScores.push_back(RunBranch(myMoves[j], _dt));
		bestMoves.push_back(myMoves[j]);
	}

	for (int s = 0; s < moveScores.size(); s++)
	{
		if (moveScores[bestIndex] < moveScores[s])
		{
			bestIndex = s;
		}
	}

	MakeMove(bestMoves[bestIndex], realBoard);
}

uint Agent::RunBranch(Move _move, double _dt)
{
	uint score = 0;
	float timer = 1;

	Board* clone = realBoard->Clone();

	MakeMove(_move, clone);
	bool myTurn = false;

	for (int d = 0; d < difficulty; d++)
	{
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
				std::cout << "AI TURN" << std::endl;
				uint index = clone->GetRandomWhitePiece();
				glm::ivec2 pos = clone->GetPositionFromIndex(index);
				std::vector<Move> optionalMoves;

				optionalMoves = clone->GetValidMoves(pos.x, pos.y);

				if (optionalMoves.size() > 0)
				{
					int someNum = rand() % optionalMoves.size();

					for (int i = -1; i < someNum + 1; i++)
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
			else
			{
				std::cout << "PLAYER TURN" << std::endl;
				uint index = clone->GetRandomRedPiece();
				glm::ivec2 pos = clone->GetPositionFromIndex(index);
				std::vector<Move> optionalMoves;

				optionalMoves = clone->GetValidMoves(pos.x, pos.y);

				if (optionalMoves.size() > 0)
				{
					int someNum = rand() % optionalMoves.size();

					for (int i = -1; i < someNum + 1; i++)
					{
						if (i == someNum)
						{
							Move myMove;
							myMove.X = optionalMoves[i].X;
							myMove.Y = optionalMoves[i].Y;
							myMove.jumpedIndex = optionalMoves[i].jumpedIndex;
							myMove.oldIndex = optionalMoves[i].oldIndex;

							MakeMove(myMove, clone);
							myTurn = true;
						}
					}
				}
			}

			if (timer <= 0)
			{
				clone->CountPieces();
				if (clone->numRed < clone->numWhite)
				{
					score++;
				}
				break;
			}

			timer -= _dt;
		}
	}

	return score;
}