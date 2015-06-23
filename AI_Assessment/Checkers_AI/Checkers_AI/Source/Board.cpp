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

#pragma region Setting_Columns
	uint index = 0;
	for (int l = 0; l < 8; l++)
	{
		rightColumn[l] = index;

		index += 8;
	}
	index = 7;
	for (int r = 0; r < 8; r++)
	{
		leftColumn[r] = index;

		index += 8;
	}
	index = 56;
	for (int t = 0; t < 8; t++)
	{
		topRow[t] = index;

		index++;
	}
	index = 0;
	for (int b = 0; b < 8; b++)
	{
		bottomRow[b] = index;

		index++;
	}
#pragma endregion


	gameOver = false;
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

	return SquareType::EMPTY;
}

uint Board::GetRandomWhitePiece()
{
	bool condition = false;
	uint pieceIndex;

	while (!condition)
	{
		uint randNum = rand() % BOARD_SIZE;

		if (GetPieceFromIndex(randNum) == SquareType::WHITE_KING || GetPieceFromIndex(randNum) == SquareType::WHITE_PIECE)
		{
			pieceIndex = randNum;
			condition = true;
		}
	}

	return pieceIndex;
}

uint Board::GetRandomRedPiece()
{
	bool condition = false;
	uint pieceIndex;

	while (!condition)
	{
		uint randNum = rand() % BOARD_SIZE;

		if (GetPieceFromIndex(randNum) == SquareType::RED_KING || GetPieceFromIndex(randNum) == SquareType::RED_PIECE)
		{
			pieceIndex = randNum;
			condition = true;
		}
	}

	return pieceIndex;
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

	//setting the index of the squares we could possibly move to
	int index = GetIndexAtPosition(_pos.x, _pos.y);
	int possibleSquareA = -1;
	int possibleSquareB = -1;

	if (myPiece == SquareType::EMPTY)
	{
		return moveList;
	}

	//if checking for a white side peice, invert the offsets
	if (myPiece == SquareType::WHITE_PIECE || myPiece == SquareType::WHITE_KING)
	{
		offset1 *= -1;
		offset2 *= -1;

		//cull left/right movements
		if (IsIndexInColumn(rightColumn, index))
		{
			possibleSquareB = index + offset2;
		}
		if (IsIndexInColumn(leftColumn, index))
		{
			possibleSquareA = index + offset1;
		}
		if (!IsIndexInColumn(rightColumn, index) && !IsIndexInColumn(leftColumn, index))
		{
			possibleSquareA = index + offset1;
			possibleSquareB = index + offset2;
		}
	}
	else
	{
		//cull left/right movements
		if (IsIndexInColumn(rightColumn, index))
		{
			possibleSquareB = index + offset1;
		}
		if (IsIndexInColumn(leftColumn, index))
		{
			possibleSquareA = index + offset2;
		}
		if (!IsIndexInColumn(rightColumn, index) && !IsIndexInColumn(leftColumn, index))
		{
			possibleSquareA = index + offset1;
			possibleSquareB = index + offset2;
		}
	}
	
	//make sure in appropriate row
	if (IsIndexInColumn(topRow, index) && (possibleSquareA >= 56 || possibleSquareB >= 56))
	{
		return moveList;
	}
	if (IsIndexInColumn(bottomRow, index) && (possibleSquareA <= 0 || possibleSquareB <= 0))
	{
		return moveList;
	}

	if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
	{
		glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
		Move move;
		move.X = newPos.x;
		move.Y = newPos.y;
		move.jumpedIndex = -1;
		move.oldIndex = index;

		moveList.push_back(move);
	}
	if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
	{
		glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
		Move move;
		move.X = newPos.x;
		move.Y = newPos.y;
		move.jumpedIndex = -1;
		move.oldIndex = index;

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

		//cull left/right movements
		if (IsIndexInColumn(rightColumn, offset1))
		{
			possibleSquareB = index + offset2;
		}
		if (IsIndexInColumn(leftColumn, offset2))
		{
			possibleSquareA = index + offset1;
		}
		if (!IsIndexInColumn(rightColumn, offset1) && !IsIndexInColumn(leftColumn, offset2))
		{
			int possibleSquareA = index + offset1;
			int possibleSquareB = index + offset2;
		}
		//make sure in appropriate row
		if (IsIndexInColumn(topRow, index) && (possibleSquareA >= 56 || possibleSquareB >= 56))
		{
			return moveList;
		}
		if (IsIndexInColumn(bottomRow, index) && (possibleSquareA <= 0 || possibleSquareB <= 0))
		{
			return moveList;
		}

		if (GetPieceFromIndex(possibleSquareA) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = -1;
			move.oldIndex = index;

			moveList.push_back(move);
		}
		if (GetPieceFromIndex(possibleSquareB) == SquareType::EMPTY)
		{
			glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = -1;
			move.oldIndex = index;

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
	int jumpSpacingX = 2;
	int jumpSpacingY = 2;

	//assign offsets for our piece
	int offset1 = BOARD_LENGTH + 1;
	int offset2 = BOARD_LENGTH - 1;

	//setting the index of the squares we could possibly move to
	int index = GetIndexAtPosition(_pos.x, _pos.y);
	int possibleSquareA = -1;
	int possibleSquareB = -1;

	//if checking for a white side peice, invert the offsets
	if (myPiece == SquareType::WHITE_PIECE || myPiece == SquareType::WHITE_KING)
	{
		offset1 *= -1;
		offset2 *= -1;

		jumpSpacingY *= -1;

		glm::vec2 jumpPos1 = _pos + glm::vec2(jumpSpacingX, jumpSpacingY);
		glm::vec2 jumpPos2 = _pos + glm::vec2(-jumpSpacingX, jumpSpacingY);

		//cull left/right movements
		if (IsInBounds(jumpPos1))
		{
			possibleSquareA = index + offset1;
		}
		if (IsInBounds(jumpPos2))
		{
			possibleSquareB = index + offset2;
		}
		else
		{
			possibleSquareA = index + offset1;
			possibleSquareB = index + offset2;
		}
	}
	else
	{
		glm::vec2 jumpPos1 = _pos + glm::vec2(jumpSpacingX, jumpSpacingY);
		glm::vec2 jumpPos2 = _pos + glm::vec2(-jumpSpacingX, jumpSpacingY);

		//cull left/right movements
		if (IsInBounds(jumpPos1))
		{
			possibleSquareA = index + offset1;
		}
		if (IsInBounds(jumpPos2))
		{
			possibleSquareB = index + offset2;
		}
		if (!IsInBounds(jumpPos1) && !IsInBounds(jumpPos2))
		{
			possibleSquareA = index + offset1;
			possibleSquareB = index + offset2;
		}
	}


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
			move.oldIndex = index;

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
			move.oldIndex = index;
		
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

		jumpSpacingY *= -1;

		glm::vec2 jumpPos1 = _pos + glm::vec2(-jumpSpacingX, jumpSpacingY);
		glm::vec2 jumpPos2 = _pos + glm::vec2(jumpSpacingX, jumpSpacingY);

		//cull left/right movements
		if (IsInBounds(jumpPos1))
		{
			possibleSquareA = index + offset1;
		}
		if (IsInBounds(jumpPos2))
		{
			possibleSquareB = index + offset2;
		}
		if (!IsInBounds(jumpPos1) && !IsInBounds(jumpPos2))
		{
			possibleSquareA = index + offset1;
			possibleSquareB = index + offset2;
		}

		if (GetPieceFromIndex(possibleSquareA) == opponentsPiece || GetPieceFromIndex(possibleSquareA) == GetOtherOpponentType(opponentsPiece))
		{
			int jumpedPiece = possibleSquareA;

			offset1 *= 2;
			offset2 *= 2;

			possibleSquareA = index + offset1;

			glm::vec2 newPos = GetPositionFromIndex(possibleSquareA);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = jumpedPiece;
			move.oldIndex = index;

			moveList.push_back(move);

			offset1 /= 2;
			offset2 /= 2;
		}
		if (GetPieceFromIndex(possibleSquareB) == opponentsPiece || GetPieceFromIndex(possibleSquareB) == GetOtherOpponentType(opponentsPiece))
		{
			int jumpedPiece = possibleSquareB;

			offset1 *= 2;
			offset2 *= 2;

			possibleSquareB = index + offset2;

			glm::vec2 newPos = GetPositionFromIndex(possibleSquareB);
			Move move;
			move.X = newPos.x;
			move.Y = newPos.y;
			move.jumpedIndex = jumpedPiece;
			move.oldIndex = index;

			moveList.push_back(move);

			offset1 /= 2;
			offset2 /= 2;
		}
	}
	
	return moveList;
}

std::vector<Move> Board::GetAllPossibleMoves()
{
	std::vector<Move> allValidMoves;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		glm::ivec2 pos = GetPositionFromIndex(i);

		if (GetPieceAt(pos.x, pos.y) != SquareType::EMPTY)
		{
			std::vector<Move> validMoves;
			validMoves = GetValidMoves(pos.x, pos.y);

			if (validMoves.size() > 0)
			{
				for (int j = 0; j < validMoves.size(); j++)
				{
					allValidMoves.push_back(validMoves[j]);
				}
			}
		}		
	}

	return allValidMoves;
}

std::vector<Move> Board::GetAllPossibleWhiteMoves()
{
	std::vector<Move> allValidMoves;
	std::vector<Move> allJumpMoves;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		glm::ivec2 pos = GetPositionFromIndex(i);
		SquareType piece = GetPieceAt(pos.x, pos.y);

		if (piece != SquareType::EMPTY)
		{
			if (piece != SquareType::RED_KING && piece != SquareType::RED_PIECE)
			{
				std::vector<Move> validMoves;
				validMoves = GetValidMoves(pos.x, pos.y);

				if (validMoves.size() > 0)
				{
					for (int j = 0; j < validMoves.size(); j++)
					{
						if (validMoves[j].jumpedIndex != -1)
						{
							allJumpMoves.push_back(validMoves[j]);
						}
						else
						{
							allValidMoves.push_back(validMoves[j]);
						}
					}
				}
			}
		}
	}

	if (allJumpMoves.size() > 0)
	{
		return allJumpMoves;
	}

	return allValidMoves;
}

Board* Board::Clone()
{
	Board* clone = new Board();

	size_t layoutSize = sizeof(this->layout);
	memcpy(clone->layout, this->layout, layoutSize);

	size_t arraySize = sizeof(this->bottomRow);
	memcpy(clone->bottomRow, this->bottomRow, arraySize);

	arraySize = sizeof(this->topRow);
	memcpy(clone->topRow, this->topRow, arraySize);

	arraySize = sizeof(this->leftColumn);
	memcpy(clone->leftColumn, this->leftColumn, arraySize);

	arraySize = sizeof(this->rightColumn);
	memcpy(clone->rightColumn, this->rightColumn, arraySize);

	return clone;
}

bool Board::IsIndexInColumn(uint* _columns, uint _index)
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		if (_index == _columns[i])
		{
			return true;
		}
	}

	return false;
}

bool Board::IsInBounds(glm::vec2 _pos)
{
	if (_pos.x > 8 || _pos.x < 0 || _pos.y > 8 || _pos.y < 0)
	{
		return false;
	}

	return true;
}

void Board::UpgradePieces()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		uint* top;
		uint* bot;

		top = GetTopRow();
		bot = GetBottomRow();

		if (IsIndexInColumn(top, i))
		{
			if (layout[i] == SquareType::RED_PIECE)
			{
				layout[i] = SquareType::RED_KING;
			}
		}
		else if (IsIndexInColumn(bot, i))
		{
			if (layout[i] == SquareType::WHITE_PIECE)
			{
				layout[i] = SquareType::WHITE_KING;
			}
		}
	}
}

void Board::CountPieces()
{
	numRed = 0;
	numWhite = 0;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		SquareType piece = layout[i];

		if (piece == SquareType::RED_KING || piece == SquareType::RED_PIECE)
		{
			numRed++;
		}
		if (piece == SquareType::WHITE_PIECE || piece == SquareType::WHITE_KING)
		{
			numWhite++;
		}
	}
}