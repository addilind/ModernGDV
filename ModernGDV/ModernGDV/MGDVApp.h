#ifndef MGDVAPP_H
#define MGDVAPP_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "MGDVVertex.h"

namespace ModernGDV {
	class App {
	public:
		App() {};
		virtual ~App() {};

		virtual void Render(float deltaT) = 0;
	};
}

#endif