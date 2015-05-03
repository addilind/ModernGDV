#pragma once

#include "../ModernGDV/OGLInc.h"
#include "../ModernGDV/MGDVVertex.h"
#include "../ModernGDV/ModernGDV.h"

namespace Geometries
{
	class Skybox
	{
		GLuint vertexBuffer;
		ModernGDV::Driver* mgdv;
		ModernGDV::Textures::Texture* texture;
		size_t shaderID;
	public:
		Skybox( ModernGDV::Driver* mgdv );
		~Skybox();

		void Render();
	};
}
