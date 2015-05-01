#pragma once

#include "OGLInc.h"

#include "MGDVVertex.h"

namespace ModernGDV {
	class App {
	public:
		App() {};
		virtual ~App() {};

		virtual void Render(float deltaT) = 0;
	};
}
