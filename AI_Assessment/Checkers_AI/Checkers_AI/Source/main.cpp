#include <iostream>
#include "Gizmos.h"
#include "gl_core_4_4.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "App.h"
#include "Game.h"

int main(int argc, char** argv)
{

	App* app = new Game();
	app->Run();

	return 0;
}