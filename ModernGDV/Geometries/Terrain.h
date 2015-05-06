#pragma once
#include "../ModernGDV/ModernGDV.h"
#include "../ModernGDV/MGDVVertex.h"

namespace Geometries
{
	class Terrain
	{
		GLuint vertexBuffer;
		ModernGDV::Driver* mgdv;
		size_t shader;
		unsigned int segs;
	public:
		Terrain(ModernGDV::Driver* mgdv, unsigned int segments);
		~Terrain();

		void Render();
	};
}