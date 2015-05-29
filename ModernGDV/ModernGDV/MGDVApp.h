#pragma once

#include "OGLInc.h"

#include "MGDVVertex.h"

namespace ModernGDV {
	class App {
	public:
		App() {};
		virtual ~App() {};

		virtual void Update( float deltaT ) = 0;
		virtual void Render(  ) = 0;
		virtual void KeyEvent( GLFWwindow* window, int key, int scancode, int action, int mods ) = 0;
	};
}
