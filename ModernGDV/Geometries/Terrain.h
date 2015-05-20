#pragma once
#include "../ModernGDV/ModernGDV.h"
#include "../ModernGDV/MGDVVertex.h"
#include "TerrainSet.h"

namespace Geometries
{
	class TerrainSet;

	class Terrain
	{
		GLuint vertexBuffer;
		ModernGDV::Driver* mgdv;
		size_t shader;
		unsigned int segs;
	public:
		Terrain(ModernGDV::Driver* mgdv, unsigned int segments);
		~Terrain();

		void Render(const TerrainSet& set);
	private:
		void setLayout();
	};
}