#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class Neck {
		private:
			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			GLuint texture;
		public:
			Neck(ModernGDV::Driver* mgdv);
			~Neck();

			void Render();

		};
	}
}