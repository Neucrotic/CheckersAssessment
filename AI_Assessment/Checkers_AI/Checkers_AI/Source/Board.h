#pragma once
#include <vector>

typedef unsigned int uint;
//USE THESE THEY ARE BETTA
glm::u32vec2;
uint32_t;

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
	uint X;
	uint Y;
	bool isJump;
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

	//will return an array 0 = X 1 = Y
	uint* GetPositionFromIndex(uint _index);
	
	std::vector<Move> GetValidMoves(uint _x, uint _y);
};