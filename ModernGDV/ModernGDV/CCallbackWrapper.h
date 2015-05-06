#pragma once

#include "OGLInc.h"

namespace ModernGDV
{
	class Driver;
	namespace Callbacks
	{
		void glfwFramebufferSizeCallback( GLFWwindow* window, int width, int height );
		void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
	}
};
