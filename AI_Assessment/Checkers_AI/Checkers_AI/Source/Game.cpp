#include <iostream>
#include "Game.h"
#include "Camera\MobileCamera.h"
#include "Board.h"
#include "InputHandler.h"

void Game::Startup()
{
	MobileCamera* camera = new MobileCamera();
	camera->SetInputWindow(window);
	camera->SetupPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 10000.0f);
	camera->LookAt(glm::vec3(4, 9, -4), glm::vec3(4, 0, 4), glm::vec3(0, 1, 0));
	m_camera = camera;	

	gameBoard = new Board();
	Board* pTest = gameBoard->Clone();

	inputHandler = new InputHandler(window, gameBoard);

	playersTurn = true;
	gameOver = false;
}

void Game::Shutdown()
{

}

bool Game::Update(double _dt)
{
	m_camera->Update(_dt);

	if (playersTurn)
	{

		gameBoard->GetAllPossibleMoves();
		inputHandler->Update(_dt);
		if (inputHandler->moveMade != false)
		{
			
		}
	}
	else
	{

	}

	gameBoard->CountPieces();
	if (gameBoard->numRed <= 0)
	{
		gameBoard->gameOver = true;
		std::cout << "Player Wins" << std::endl;
	}
	else if (gameBoard->numWhite <= 0)
	{
		gameBoard->gameOver = true;
		std::cout << "Computer Wins" << std::endl;
	}

	gameBoard->UpgradePieces();

	return true;
}

void Game::Render()
{
	Gizmos::addTransform(glm::mat4(1));

	//drawing the game board
	RenderBoard(gameBoard);

	//rendering the peice selector
	Gizmos::addSphere(glm::vec3(inputHandler->selectorXZ.x, 1.0f, inputHandler->selectorXZ.y), 0.5f, 5, 5, glm::vec4(inputHandler->selectorColour), nullptr);
}

void Game::RenderBoard(Board* _board)
{
	float offsetX = 0;
	float offsetZ = 0;

	int layoutIter = 0;
	bool bIsBlack = false;

	//loop for rows
	for (int i = 0; i < 8; i++)
	{		
		bIsBlack = (i % 2) ? true : false;

		//loop for columns
		for (int j = 0; j < 8; j++)
		{
			if (layoutIter < BOARD_SIZE)
			{
				//drawing the board by default	
				glm::vec4 colour = (bIsBlack) ? glm::vec4(0, 0, 0, 1) : glm::vec4(1, 0, 0, 1);
				bIsBlack = !bIsBlack;

				Gizmos::addAABBFilled(glm::vec3(j, 0, i), glm::vec3(0.5f, 0.1f, 0.5f), colour, nullptr);

				//drawing the pieces at their found locations
				switch (_board->layout[layoutIter])
				{
				case SquareType::RED_PIECE:
					Gizmos::addCylinderFilled(glm::vec3(j, 0, i), 0.5f, 0.3f, 10, glm::vec4(1, 0, 0, 1), nullptr);
					break;
				case SquareType::WHITE_PIECE:
					Gizmos::addCylinderFilled(glm::vec3(j, 0, i), 0.5f, 0.3f, 10, glm::vec4(1, 1, 1, 1), nullptr);
					break;
				case SquareType::RED_KING:
					Gizmos::addCylinderFilled(glm::vec3(j, 0, i), 0.5f, 0.3f, 5, glm::vec4(1, 0, 0, 1), nullptr);
					break;
				case SquareType::WHITE_KING:
					Gizmos::addCylinderFilled(glm::vec3(j, 0, i), 0.5f, 0.3f, 5, glm::vec4(1, 1, 1, 1), nullptr);
					break;
				default:
					break;
				}
				layoutIter++;
			}			
		}
	}
}