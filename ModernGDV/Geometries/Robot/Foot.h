#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class Foot {
		private:
			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			GLuint texture;
		public:
			Foot( ModernGDV::Driver* mgdv );
			~Foot();

			void Render();

		};
	}
}