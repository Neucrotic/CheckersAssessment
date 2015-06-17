#pragma once
#include "GLFW\glfw3.h"
#include "glm\common.hpp"

#include "Board.h"

class InputHandler
{
public:

	InputHandler(GLFWwindow* _window, Board* _board);
	~InputHandler();

	bool moveMade;

	glm::vec2 selectorXZ;
	glm::vec4 selectorColour;

	void Update(double _dt);

	inline uint* GetTopRow()
	{
		return &topRow[0];
	}
	inline uint* GetBottomRow()
	{
		return &bottomRow[0];
	}

	bool IsIndexInColumn(uint* _columns, uint _index);

private:

	GLFWwindow* myWindow;
	Board* myBoard;
	std::vector<Move> myValidMoves;

	//information used to move around pieces
	uint selector;
	SquareType selectedPiece;
	glm::vec2 selectedPosition;

	uint rightColumn[BOARD_LENGTH];
	uint leftColumn[BOARD_LENGTH];
	uint topRow[BOARD_LENGTH];
	uint bottomRow[BOARD_LENGTH];

	float keyCD;
	bool secondEnter;

	void OnEnter();
	void OnSecondEnter(SquareType _type, glm::vec2 _oldPos);

	bool IsSelectorInColumn(uint* _columns);
};