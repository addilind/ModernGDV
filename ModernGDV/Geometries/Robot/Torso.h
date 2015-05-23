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
			size_t* instanceCounter;

			ModernGDV::Driver* mgdv;
			GLuint vertexBuffer;
			ModernGDV::Textures::Texture* texture;
		public:
			explicit Torso( ModernGDV::Driver* mgdv );
			Torso( const Torso& source );
			~Torso();

			void Render();
		};
	}
}
