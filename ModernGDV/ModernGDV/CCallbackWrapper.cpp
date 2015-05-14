#include "CCallbackWrapper.h"

#include "ModernGDV.h"
#include <iostream>

void ModernGDV::Callbacks::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	static_cast<Driver*>(glfwGetWindowUserPointer(window))->FramebufferSizeChanged( window, width, height );
}

void ModernGDV::Callbacks::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Driver*>(glfwGetWindowUserPointer( window ))->KeyEvent( window, key, scancode, action, mods );
}

void APIENTRY ModernGDV::Callbacks::oglDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	if (id == GL_INVALID_OPERATION)
		Log( "OGL!", std::string( message, message + length ) );
	else
		Log( "OGLE", std::string( message, message + length ) );
}