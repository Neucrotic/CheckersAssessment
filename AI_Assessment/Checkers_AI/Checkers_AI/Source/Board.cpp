#include "Board.h"

Board::Board()
{
	//first initialize loop setting squares
	for (auto i = 0; i < BOARD_SIZE; i++)
	{
		layout[i] = SquareType::EMPTY;
	}

	//setting red pieces
	SetPiece(0, 0, SquareType::RED_PIECE);
	SetPiece(2, 0, SquareType::RED_PIECE);
	SetPiece(4, 0, SquareType::RED_PIECE);
	SetPiece(6, 0, SquareType::RED_PIECE);
	SetPiece(1, 1, SquareType::RED_PIECE);
	SetPiece(3, 1, SquareType::RED_PIECE);
	SetPiece(5, 1, SquareType::RED_PIECE);
	SetPiece(7, 1, SquareType::RED_PIECE);
	SetPiece(0, 2, SquareType::RED_PIECE);
	SetPiece(2, 2, SquareType::RED_PIECE);
	SetPiece(4, 2, SquareType::RED_PIECE);
	SetPiece(6, 2, SquareType::RED_PIECE);

	//setting white pieces
	SetPiece(1, 5, SquareType::WHITE_PIECE);
	SetPiece(3, 5, SquareType::WHITE_PIECE);
	SetPiece(5, 5, SquareType::WHITE_PIECE);
	SetPiece(7, 5, SquareType::WHITE_PIECE);
	SetPiece(0, 6, SquareType::WHITE_PIECE);
	SetPiece(2, 6, SquareType::WHITE_PIECE);
	SetPiece(4, 6, SquareType::WHITE_PIECE);
	SetPiece(6, 6, SquareType::WHITE_PIECE);
	SetPiece(1, 7, SquareType::WHITE_PIECE);
	SetPiece(3, 7, SquareType::WHITE_PIECE);
	SetPiece(5, 7, SquareType::WHITE_PIECE);
	SetPiece(7, 7, SquareType::WHITE_PIECE);
}

Board::~Board()
{

}

void Board::SetPiece(uint _x, uint _y, SquareType _eType)
{
	unsigned int index = _y * BOARD_LENGTH + _x;
	layout[index] = _eType;
}

SquareType Board::GetPieceAt(uint _x, uint _y)
{
	unsigned int index = _y * BOARD_LENGTH + _x;

	return layout[index];
}

int Board::GetIndexAtPosition(uint _x, uint _y)
{
	unsigned int index = _y * BOARD_LENGTH + _x;

	return index;
}

SquareType Board::GetPieceFromIndex(uint _index)
{
	int x = _index % BOARD_LENGTH;
	int y = _index / BOARD_LENGTH;

	SquareType piece = GetPieceAt(x, y);

	return piece;
}

glm::vec2 Board::GetPositionFromIndex(uint _index)
{
	glm::vec2 pos;

	pos.x = _index % BOARD_LENGTH;
	pos.y = _index / BOARD_LENGTH;

	return pos;
}

SquareType Board::GetOpponentsType(SquareType _myType)
{
	SquareType returnType;

	if (_myType == SquareType::RED_PIECE)
	{
		returnType = SquareType::WHITE_PIECE;
	}
	else if (_myType == SquareType::RED_KING)
	{
		returnType = SquareType::WHITE_KING;
	}
	else if (_myType == SquareType::WHITE_PIECE)
	{
		returnType = SquareType::RED_PIECE;
	}
	else if (_myType == SquareType::WHITE_KING)
	{
		returnType = SquareType::RED_KING;
	}
	else if (_myType == SquareType::EMPTY)
	{
		returnType = SquareType::EMPTY;
	}

	return returnType;
}

SquareType Board::GetOtherOpponentType(SquareType _opponentsType)
{
	if (_opponentsType == SquareType::RED_KING)
	{
		return SquareType::RED_PIECE;
	}
	if (_opponentsType == SquareType::RED_PIECE)
	{
		return SquareType::RED_KING;
	}
	if (_opponentsType == SquareType::WHITE_KING)
	{
		return SquareType::WHITE_PIECE;
	}
	if (_opponentsType == SquareType::WHITE_PIECE)
	{
		return SquareType::WHITE_KING;
	}
}

std::vector<Move> Board::GetValidMoves(uint _x, uint _y)
{
	std::vector<Move> validMoves;
	SquareType myPieceType = GetPieceAt(_x, _y);
	SquareType opponentsType = GetOpponentsType(myPieceType);
	

	if (myPieceType == SquareType::EMPTY)
	{
		return validMoves;
	}

	if (GetPossibleJumpsFromPos(glm::vec2(_x, _y)).size() > 0)
	{
		validMoves = GetPossibleJumpsFromPos(glm::vec2(_x, _y));
	}
	else
	{
		validMoves = GetPossibleMovesFromPos(glm::vec2(_x, _y));
	}

	return validMoves;
}

std::vector<Move> Board::GetPossibleMovesFromPos(glm::vec2 _pos)
{
	std::vector<Move> moveList;

	SquareType myPiece = GetPieceAt(_pos.x, _pos.y);

	//assign offsets for our piece
	int offset1 = BOARD_LENGTH + 1;
	int offset2 = BOARD_LENGTH - 1;

	//if checking for a white side peice, invert the offsets
	if (myPiece == SquareType::WHITE_PIECE || myPiece == SquareType::WHITE_KING)
	{
		offset1 *= -1;
		offset2 *= -1;
	}

	//setting the index of the squares we could possibly move to
	int index = GetIndexAtPosition(_pos.x, _pos.y);
	int possibleSquareA = index + offset1;
	int possibleSquareB = index + offset2;

	if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
	{
		glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
		Move move;
		move.X = newPos.x;
		move.Y = newPos.y;
		move.jumpedIndex = -1;

		moveList.push_back(move);
	}
	if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
	{
		glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
		Move move;
		move.X = newPos.x;
		move.Y = newPos.y;
		move.jumpedIndex = -1;

		moveList.push_back(move);
	}

	//checking if our piece is a king, if so, do futher checks
	if (myPiece == SquareType::RED_KING || myPiece == SquareType::WHITE_KING)
	{
		//invert the offsets
		offset1 *= -1;
		offset2 *= -1;

		possibleSquareA = index + offset1;
		possibleSquareB = index + offset2;

		if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = -1;

			moveList.push_back(move);
		}
		if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = -1;

			moveList.push_back(move);
		}
	}

	return moveList;
}

std::vector<Move> Board::GetPossibleJumpsFromPos(glm::vec2 _pos)
{
	std::vector<Move> moveList;
	SquareType myPiece = GetPieceAt(_pos.x, _pos.y);
	SquareType opponentsPiece = GetOpponentsType(myPiece);

	//assign offsets for our piece
	int offset1 = BOARD_LENGTH + 1;
	int offset2 = BOARD_LENGTH - 1;

	//if checking for a white side peice, invert the offsets
	if (myPiece == SquareType::WHITE_PIECE || myPiece == SquareType::WHITE_KING)
	{
		offset1 *= -1;
		offset2 *= -1;
	}

	//setting the index of the squares we could possibly move to
	int index = GetIndexAtPosition(_pos.x, _pos.y);
	int possibleSquareA = index + offset1;
	int possibleSquareB = index + offset2;

	if (GetPieceFromIndex(possibleSquareA) == opponentsPiece || GetPieceFromIndex(possibleSquareA) == GetOtherOpponentType(opponentsPiece))
	{
		int jumpedPiece = possibleSquareA;

		//double our offsets and resetting our possible squares
		offset1 *= 2;
		offset2 *= 2;
		possibleSquareA = index + offset1;

		if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = jumpedPiece;

			moveList.push_back(move);
		}

		//ressetting offset for possible calculations
		offset1 /= 2;
		offset2 /= 2;

	}
	if (GetPieceFromIndex(possibleSquareB) == opponentsPiece || GetPieceFromIndex(possibleSquareB) == GetOtherOpponentType(opponentsPiece))
	{
		int jumpedPiece = possibleSquareB;

		//double our offsets and resetting our possible squares
		offset1 *= 2;
		offset2 *= 2;
		possibleSquareB = index + offset2;

		if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = jumpedPiece;
		
			moveList.push_back(move);
		}

		//ressetting offset for possible calculations
		offset1 /= 2;
		offset2 /= 2;
	}

	//checking if our piece is a king, if so, do futher checks
	if (myPiece == SquareType::RED_KING || myPiece == SquareType::WHITE_KING)
	{
		//invert the offsets
		offset1 *= -1;
		offset2 *= -1;

		possibleSquareA = index + offset1;
		possibleSquareB = index + offset2;

		if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = false;

			moveList.push_back(move);
		}
		if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = false;

			moveList.push_back(move);
		}
	}
	
	return moveList;
}