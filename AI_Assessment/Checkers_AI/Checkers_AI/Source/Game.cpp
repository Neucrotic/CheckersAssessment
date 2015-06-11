#include "Game.h"
#include "Camera\MobileCamera.h"
#include "Board.h"
#include "InputHandler.h"

void Game::Startup()
{
	MobileCamera* camera = new MobileCamera();
	camera->SetInputWindow(window);
	camera->SetupPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 10000.0f);
	camera->LookAt(glm::vec3(5, 10, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	m_camera = camera;	

	gameBoard = new Board();

	inputHandler = new InputHandler(window, gameBoard);

	playersTurn = true;
}

void Game::Shutdown()
{

}

bool Game::Update(double _dt)
{
	m_camera->Update(_dt);

	if (playersTurn)
	{
		inputHandler->Update(_dt);
	}
	else
	{

	}

	//here to test function
	gameBoard->GetValidMoves(4, 7);

	return true;
}

void Game::Render()
{
	Gizmos::addTransform(glm::mat4(1));

	//drawing the game board
	RenderBoard(gameBoard);

	//rendering the peice selector
	Gizmos::addSphere(glm::vec3(inputHandler->selectorXZ.x, 1.0f, inputHandler->selectorXZ.y), 0.5f, 5, 5, glm::vec4(inputHandler->selectorColour), nullptr);

	/*glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}*/
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
				default:
					break;
				}
				layoutIter++;
			}			
		}
	}
}