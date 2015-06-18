#pragma once
#include "App.h"

class InputHandler;
class Board;

class Game : public App
{
public:

	void Startup();
	void Shutdown();

	bool Update(double _dt);
	void Render();

private:

	Board* gameBoard;
	bool playersTurn;

	InputHandler* inputHandler;

	void RenderBoard(Board* _board);
};