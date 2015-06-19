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
	bool jumpMade;
	glm::ivec2 movedPiecePos;

	glm::vec2 selectorXZ;
	glm::vec4 selectorColour;

	void Update(double _dt);

private:

	GLFWwindow* myWindow;
	Board* myBoard;
	std::vector<Move> myValidMoves;

	//information used to move around pieces
	uint selector;
	SquareType selectedPiece;
	glm::vec2 selectedPosition;

	float keyCD;
	bool secondEnter;

	void OnEnter();
	void OnSecondEnter(SquareType _type, glm::vec2 _oldPos);

	bool IsSelectorInColumn(uint* _columns);
};