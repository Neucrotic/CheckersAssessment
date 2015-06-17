#pragma once
#include <vector>
#include "glm\common.hpp"

typedef unsigned int uint;
//USE THESE THEY ARE BETTA
//glm::u32vec2;
//uint32_t;

const int BOARD_SIZE = 64;
const int BOARD_LENGTH = 8;

enum class SquareType
{
	EMPTY,
	RED_PIECE,
	WHITE_PIECE,
	RED_KING,
	WHITE_KING
};

struct Move
{
	uint32_t X;
	uint32_t Y;
	int jumpedIndex;
};

class Board
{
public:

	SquareType layout[BOARD_SIZE];

	Board();
	~Board();

	void SetPiece(uint _x, uint _y, SquareType _eType);
	SquareType GetPieceAt(uint _x, uint _y);
	int GetIndexAtPosition(uint _x, uint _y);
	SquareType GetPieceFromIndex(uint _index);
	glm::vec2 GetPositionFromIndex(uint _index);

	SquareType GetOpponentsType(SquareType _myType);
	SquareType GetOtherOpponentType(SquareType _opponentType);

	std::vector<Move> GetValidMoves(uint _x, uint _y);
	std::vector<Move> GetPossibleMovesFromPos(glm::vec2 _pos);
	std::vector<Move> GetPossibleJumpsFromPos(glm::vec2 _pos);
};