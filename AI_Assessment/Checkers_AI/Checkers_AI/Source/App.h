#pragma once
#include "Gizmos.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera\Camera.h"

typedef unsigned int uint;

class App
{
public:

	int Run();

	virtual void Startup() = 0;
	virtual void Shutdown() = 0;

	virtual bool Update(double _dt) = 0;
	virtual void Render() = 0;

protected:

	GLFWwindow* window;
	Camera* m_camera;
	double deltaTime;

	bool Init();
	bool Deinit();

};