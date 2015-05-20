#pragma once
//inkludiert alle Bibs

#define GLFW_INCLUDE_NONE
#include "OGL/wgl_core_3_3.h"
#include "OGL/gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <string>
#include <future>
#include <iostream>

namespace ModernGDV
{
	void Log( const std::string& source, const std::string& message );
}
