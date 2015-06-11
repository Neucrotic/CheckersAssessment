#include <iostream>
#include "InputHandler.h"

InputHandler::InputHandler(GLFWwindow* _window, Board* _board)
{
	selector = 0;
	selectorXZ = glm::vec2(0, 0);
	selectorColour = glm::vec4(0, 0, 1, 1);
	
	myWindow = _window;
	myBoard = _board;

	//setting column arrays
	uint index = 0;
	for (int l = 0; l < 8; l++)
	{
		leftColumn[l] = index;

		index += 8;
	}
	index = 7;
	for (int r = 0; r < 8; r++)
	{
		rightColumn[r] = index;

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

	keyCD = 0.15f;
	enterCount = 0;
}

InputHandler::~InputHandler()
{
	delete myWindow;
}

void InputHandler::Update(double _dt)
{
	if (glfwGetKey(myWindow, GLFW_KEY_UP) == GLFW_PRESS && keyCD <= 0)
	{
		if (IsSelectorInColumn(topRow))
		{
			selector -= 56;
			selectorXZ = glm::vec2(selectorXZ.x, selectorXZ.y - 7);
		}
		else
		{
			selector += 8;
			selectorXZ = glm::vec2(selectorXZ.x, selectorXZ.y + 1);
		}

		keyCD = 0.15f;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_DOWN) == GLFW_PRESS && keyCD <= 0)
	{
		if (IsSelectorInColumn(bottomRow))
		{
			selector += 56;
			selectorXZ = glm::vec2(selectorXZ.x, selectorXZ.y + 7);
		}
		else
		{
			selector -= 8;
			selectorXZ = glm::vec2(selectorXZ.x, selectorXZ.y - 1);
		}

		keyCD = 0.15f;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_RIGHT) == GLFW_PRESS && keyCD <= 0)
	{
		if (IsSelectorInColumn(leftColumn))
		{
			selector += 7;
			selectorXZ = glm::vec2(selectorXZ.x + 7, selectorXZ.y);
		}
		else
		{
			selector--;
			selectorXZ = glm::vec2(selectorXZ.x - 1, selectorXZ.y);
		}

		keyCD = 0.15f;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_LEFT) == GLFW_PRESS && keyCD <= 0)
	{
		if (IsSelectorInColumn(rightColumn))
		{
			selector -= 7;
			selectorXZ = glm::vec2(selectorXZ.x - 7, selectorXZ.y);
		}
		else
		{
			selector++;
			selectorXZ = glm::vec2(selectorXZ.x + 1, selectorXZ.y);
		}

		keyCD = 0.15f;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_ENTER) == GLFW_PRESS && keyCD <= 0)
	{
		OnEnter();
		
		enterCount++;

		keyCD = 0.15f;
	}

	keyCD -= _dt;
	std::cout << "Key Cooldown: " << keyCD << std::endl;
	std::cout << "Selector: " << selector << std::endl;
	std::cout << "Selector Co-ord: " << selectorXZ.x << selectorXZ.y << std::endl;
}

bool InputHandler::IsSelectorInColumn(uint* _columns)
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		if (selector == _columns[i])
		{
			return true;
		}
	}

	return false;
}

void InputHandler::OnEnter()
{
	SquareType piece;
	uint* position;
	std::vector<Move> myValidMoves;

	if (enterCount < 1)
	{
		//error is that the variables are in local scope
		piece = myBoard->GetPieceFromIndex(selector);

		if (piece != SquareType::EMPTY || piece != SquareType::WHITE_KING || piece != SquareType::WHITE_PIECE)
		{
			position = myBoard->GetPositionFromIndex(selector);

			myValidMoves = myBoard->GetValidMoves(position[POS_X], position[POS_Y]);
		}
	}
	else
	{
		OnSecondEnter(piece, position, myValidMoves);

		enterCount = 0;
	}
}

void InputHandler::OnSecondEnter(SquareType _piece, uint* _position, std::vector<Move> _moveList)
{
	SquareType piece = _piece;
	uint* position = _position;
	std::vector<Move> myValidMoves = _moveList;

	for (auto i = 0; i < myValidMoves.size(); i++)
	{
		piece = myBoard->GetPieceFromIndex(selector);

		if (piece == SquareType::EMPTY)
		{
			position = myBoard->GetPositionFromIndex(selector);

			//making sure the move is in the validMoves list
			if (position[POS_X] == myValidMoves[i].X && position[POS_Y] == myValidMoves[i].Y)
			{
				myBoard->SetPiece(myValidMoves[i].X, myValidMoves[i].Y, piece);
			}
		}
	}
}