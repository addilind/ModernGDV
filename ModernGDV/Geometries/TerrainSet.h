#pragma once
#include <string>
#include "../ModernGDV/ModernGDV.h"
#include "../ModernGDV/Textures/Texture.h"

namespace ModernGDV{
	class Driver;
}

namespace Geometries {
	class TerrainSet
	{
	private:
		const ModernGDV::Textures::Texture* difTex;
		const ModernGDV::Textures::Texture* heightTex;
		float fadeDist;
		ModernGDV::Driver* mgdv;
	public:
		TerrainSet(const std::string& difTexture, const std::string& heightTexture, float fadeDistance, ModernGDV::Driver* driver);
		~TerrainSet();

		void ApplyShaderSettings() const;
	};
}
