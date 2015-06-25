#pragma once
#include <vector>
//#include <string>
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
	int oldIndex;

	bool operator==(const Move& _rhs)
	{
		return X == _rhs.X						&&
			   Y == _rhs.Y						&&
			   jumpedIndex == _rhs.jumpedIndex	&&
			   oldIndex == _rhs.oldIndex;
	}
};

class Board
{
public:

	Board();
	~Board();

	SquareType layout[BOARD_SIZE];
	int offset1 = BOARD_LENGTH + 1;
	int offset2 = BOARD_LENGTH - 1;

	uint rightColumn[BOARD_LENGTH];
	uint leftColumn[BOARD_LENGTH];
	uint topRow[BOARD_LENGTH];
	uint bottomRow[BOARD_LENGTH];

	bool gameOver;
	uint numRed;
	uint numWhite;

	inline uint* GetTopRow()
	{
		return &topRow[0];
	}
	inline uint* GetBottomRow()
	{
		return &bottomRow[0];
	}

	void SetPiece(uint _x, uint _y, SquareType _eType);
	SquareType GetPieceAt(uint _x, uint _y);
	int GetIndexAtPosition(uint _x, uint _y);
	SquareType GetPieceFromIndex(uint _index);
	glm::vec2 GetPositionFromIndex(uint _index);

	SquareType GetOpponentsType(SquareType _myType);
	SquareType GetOtherOpponentType(SquareType _opponentType);
	uint GetRandomWhitePiece();
	uint GetRandomRedPiece();

	std::vector<Move> GetValidMoves(uint _x, uint _y);
	std::vector<Move> GetPossibleMovesFromPos(glm::vec2 _pos);
	std::vector<Move> GetPossibleJumpsFromPos(glm::vec2 _pos);
	std::vector<Move> GetAllPossibleMoves();

	std::vector<Move> GetAllPossibleWhiteMoves();
	std::vector<Move> GetAllPossibleRedMoves();

	Board* Clone();

	bool IsIndexInColumn(uint* _columns, uint _index);
	bool IsInBounds(glm::vec2 _pos);

	void UpgradePieces();
	void CountPieces();

	glm::ivec2 CalculatePossibleSquaresForMoves(uint _index);
	glm::ivec2 CalculatePossibleSquaresForJumps(uint _index, int &_xJumpSpace, int &_yJumpSpace);

private:
	std::vector<Move> GetAllPossibleMovesForColour(SquareType _pieceType, SquareType _kingType); //make sure that the pieces are of same team
};