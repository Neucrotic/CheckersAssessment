#include <typeinfo>
#include <iostream>
#include "InputHandler.h"

InputHandler::InputHandler(GLFWwindow* _window, Board* _board)
{
	moveMade = false;

	selector = 0;
	selectorXZ = glm::vec2(0, 0);
	selectorColour = glm::vec4(0, 0, 1, 1);
	
	myWindow = _window;
	myBoard = _board;

	keyCD = 0.15f;
	secondEnter = false;
}

InputHandler::~InputHandler()
{
	delete myWindow;
}

void InputHandler::Update(double _dt)
{

#pragma region Keys_Input
	if (glfwGetKey(myWindow, GLFW_KEY_UP) == GLFW_PRESS && keyCD <= 0)
	{
		if (IsSelectorInColumn(myBoard->topRow))
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
		if (IsSelectorInColumn(myBoard->bottomRow))
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
		if (IsSelectorInColumn(myBoard->rightColumn))
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
		if (IsSelectorInColumn(myBoard->leftColumn))
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

		keyCD = 0.15f;
	}
#pragma endregion

	keyCD -= _dt;

	if (secondEnter)
	{
		std::cout << "true" << std::endl;

		if (myBoard->GetPieceFromIndex(selector) != SquareType::EMPTY)
		{
			selectorColour = glm::vec4(0, 1, 0, 1);
		}
	}	
	else
	{
		selectorColour = glm::vec4(0, 0, 1, 1);

		std::cout << "false" << std::endl;
	}
}

void InputHandler::OnEnter()
{
	if (!secondEnter)
	{
		selectedPiece = myBoard->GetPieceFromIndex(selector);

		if (selectedPiece != SquareType::EMPTY || selectedPiece != SquareType::WHITE_KING || selectedPiece != SquareType::WHITE_PIECE)
		{
			selectedPosition = myBoard->GetPositionFromIndex(selector);

			myValidMoves = myBoard->GetValidMoves(selectedPosition.x, selectedPosition.y);

			secondEnter = true;
			return;
		}
	}
	
	if (selectedPiece == SquareType::EMPTY)
	{
		secondEnter = false;
		return;
	}

	if (secondEnter)
	{
		if (myValidMoves.size() > 0 && typeid(selectedPiece) == typeid(SquareType))
		{
			OnSecondEnter(selectedPiece, selectedPosition);
		}

		secondEnter = false;
	}
}

void InputHandler::OnSecondEnter(SquareType _type, glm::vec2 _oldPos)
{
	SquareType piece;
	glm::vec2 position;

	for (auto i = 0; i < myValidMoves.size(); i++)
	{
		piece = myBoard->GetPieceFromIndex(selector);

		if (piece == SquareType::EMPTY)
		{
			position = myBoard->GetPositionFromIndex(selector);

			//making sure the move is in the validMoves list
			if (position.x == myValidMoves[i].X && position.y == myValidMoves[i].Y)
			{
				myBoard->SetPiece(myValidMoves[i].X, myValidMoves[i].Y, _type);
				myBoard->SetPiece(_oldPos.x, _oldPos.y, SquareType::EMPTY);

				if (myValidMoves[i].jumpedIndex != -1)
				{
					glm::vec2 pos = myBoard->GetPositionFromIndex(myValidMoves[i].jumpedIndex);
					
					myBoard->SetPiece(pos.x, pos.y, SquareType::EMPTY);
				}

				moveMade = true;
			}
		}
	}
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