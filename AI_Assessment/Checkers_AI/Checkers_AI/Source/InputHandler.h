#pragma once
#include "GLFW\glfw3.h"
#include "glm\common.hpp"

#include "Board.h"

class InputHandler
{
public:

	InputHandler(GLFWwindow* _window, Board* _board);
	~InputHandler();

	glm::vec2 selectorXZ;
	glm::vec4 selectorColour;

	void Update(double _dt);

private:

	static const uint POS_X = 0;
	static const uint POS_Y = 1;

	GLFWwindow* myWindow;
	Board* myBoard;

	uint selector;

	uint rightColumn[BOARD_LENGTH];
	uint leftColumn[BOARD_LENGTH];
	uint topRow[BOARD_LENGTH];
	uint bottomRow[BOARD_LENGTH];

	float keyCD;
	int enterCount;

	void OnEnter();
	void OnSecondEnter(SquareType _piece, uint* _position, std::vector<Move> _moveList);

	bool IsSelectorInColumn(uint* _columns);
};