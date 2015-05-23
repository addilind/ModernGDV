#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class Ski {
		private:
			size_t* instanceCounter;

			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			ModernGDV::Textures::Texture* texture;
		public:
			explicit Ski( ModernGDV::Driver* mgdv );
			Ski(const Ski& source);
			~Ski();

			void Render();

		};
	}
}