#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class Torso {
		private:
			ModernGDV::Driver* mgdv;
			GLuint vertexBuffer;
			ModernGDV::Textures::Texture* texture;
		public:
			Torso( ModernGDV::Driver* mgdv );
			~Torso();

			void Render();
		};
	}
}
