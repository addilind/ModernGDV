#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class Head {
		private:
			size_t* instanceCounter;

			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			ModernGDV::Textures::Texture* texture;
		public:
			explicit Head( ModernGDV::Driver* mgdv );
			Head( const Head& source );
			~Head();

			void Render();

		};
	}
}