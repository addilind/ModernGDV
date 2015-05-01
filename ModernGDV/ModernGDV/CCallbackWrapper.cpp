#include "CCallbackWrapper.h"

#include "ModernGDV.h"

ModernGDV::Driver* ModernGDV::Callbacks::mgdvDriverInstance;

void ModernGDV::Callbacks::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	mgdvDriverInstance->FramebufferSizeChanged( window, width, height );
}