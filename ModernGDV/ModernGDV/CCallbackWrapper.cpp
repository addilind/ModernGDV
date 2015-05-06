#include "CCallbackWrapper.h"

#include "ModernGDV.h"

void ModernGDV::Callbacks::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	static_cast<Driver*>(glfwGetWindowUserPointer(window))->FramebufferSizeChanged( window, width, height );
}

void ModernGDV::Callbacks::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<Driver*>(glfwGetWindowUserPointer( window ))->KeyEvent( window, key, scancode, action, mods );
}