#ifndef MGDVAPP_H
#define MGDVAPP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "MGDVVertex.h"

namespace ModernGDV {
	class App {
	public:
		App() {};
		virtual ~App() {};

		virtual void Render() = 0;
		virtual const char* GetWindowTitle() = 0;
	};
}

#endif