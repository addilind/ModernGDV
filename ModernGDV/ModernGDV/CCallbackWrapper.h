#pragma once

#include "OGLInc.h"

namespace ModernGDV
{
	class Driver;
	namespace Callbacks
	{
		extern Driver* mgdvDriverInstance;

		void glfwFramebufferSizeCallback( GLFWwindow* window, int width, int height );
	}
};
