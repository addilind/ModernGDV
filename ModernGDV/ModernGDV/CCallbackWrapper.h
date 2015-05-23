#pragma once

#include "OGLInc.h"

namespace ModernGDV
{
	class Driver;
	namespace Callbacks
	{
		void glfwFramebufferSizeCallback( GLFWwindow* window, int width, int height );
		void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );

		void glfwErrorCallback( int error, const char* description );
		void APIENTRY oglDebugMessage ( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam );
	}
};
