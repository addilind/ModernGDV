#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class Shank {
		private:
			size_t* instanceCounter;

			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			ModernGDV::Textures::Texture* texture;
		public:
			explicit Shank( ModernGDV::Driver* mgdv );
			Shank( const Shank& source );
			~Shank();

			void Render();

		};
	}
}