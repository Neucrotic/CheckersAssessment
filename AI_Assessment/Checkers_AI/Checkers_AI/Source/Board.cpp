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
	SetPiece(0, 5, SquareType::WHITE_PIECE);
	SetPiece(2, 5, SquareType::WHITE_PIECE);
	SetPiece(4, 5, SquareType::WHITE_PIECE);
	SetPiece(6, 5, SquareType::WHITE_PIECE);
	SetPiece(1, 6, SquareType::WHITE_PIECE);
	SetPiece(3, 6, SquareType::WHITE_PIECE);
	SetPiece(5, 6, SquareType::WHITE_PIECE);
	SetPiece(7, 6, SquareType::WHITE_PIECE);
	SetPiece(0, 7, SquareType::WHITE_PIECE);
	SetPiece(2, 7, SquareType::WHITE_PIECE);
	SetPiece(4, 7, SquareType::WHITE_PIECE);
	SetPiece(6, 7, SquareType::WHITE_PIECE);
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

std::vector<Move> Board::GetValidMoves(uint _x, uint _y)
{
	std::vector<Move> validMoves;
	std::vector<int> possibleMoves;
	SquareType myPieceType = GetPieceAt(_x, _y);

	if (myPieceType == SquareType::EMPTY)
	{
		return validMoves;
	}
	else
	{
		//assign offsets for our piece
		int offset1 = BOARD_LENGTH + 1;
		int offset2 = BOARD_LENGTH - 1;

		//if checking for a white side peice, invert the offsets
		if (myPieceType == SquareType::WHITE_PIECE || myPieceType == SquareType::WHITE_KING)
		{
			offset1 *= -1;
			offset2 *= -1;
		}

		int index = GetIndexAtPosition(_x, _y);
		int possibleSquareA = index + offset1;
		int possibleSquareB = index + offset2;

		//if possible squares are valid moves add them to list
		if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
		{
			possibleMoves.push_back(possibleSquareA);
		}
		if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
		{
			possibleMoves.push_back(possibleSquareB);
		}

		//check backwards moves if king
		if (myPieceType == SquareType::RED_KING || myPieceType == SquareType::WHITE_KING)
		{
			offset1 *= -1;
			offset2 *= -1;

			possibleSquareA = index + offset1;
			possibleSquareB = index + offset2;

			if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
			{
				possibleMoves.push_back(possibleSquareA);
			}
			if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
			{
				possibleMoves.push_back(possibleSquareB);
			}
		}

		for (auto i = possibleMoves.begin(); i != possibleMoves.end(); i++)
		{
			uint* index = GetPositionFromIndex(*i);
			//int posX = *i % BOARD_LENGTH;
			//int posY = *i / BOARD_LENGTH;

			Move move;
			move.X = index[0];
			move.Y = index[1];
			move.isJump = false;

			validMoves.push_back(move);
		}

		return validMoves;
	}
}

uint* Board::GetPositionFromIndex(uint _index)
{
	uint index[2];

	int posX = _index % BOARD_LENGTH;
	int posY = _index / BOARD_LENGTH;

	index[0] = posX;
	index[1] = posY;

	return index;
}