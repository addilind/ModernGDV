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
			size_t* instanceCounter;

			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			ModernGDV::Textures::Texture* texture;
		public:
			Foot( ModernGDV::Driver* mgdv );
			Foot( const Foot& source );
			~Foot();

			void Render();

		};
	}
}