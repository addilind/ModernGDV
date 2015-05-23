#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

namespace Geometries
{
	namespace Robot
	{
		class ShoulderJoint {
		private:
			size_t* instanceCounter;

			GLuint vertexBuffer;
			ModernGDV::Driver* mgdv;
			ModernGDV::Textures::Texture* texture;
		public:
			explicit ShoulderJoint( ModernGDV::Driver* mgdv );
			ShoulderJoint( const ShoulderJoint& source );
			~ShoulderJoint();

			void Render();

		};
	}
}
