#include "TerrainSet.h"

Geometries::TerrainSet::TerrainSet( const std::string& difTexture, const std::string& heightTexture,
	float fadeDistance, ModernGDV::Driver* driver) : difTex(driver->GetTexture(difTexture)),
	heightTex(driver->GetTexture(heightTexture)), fadeDist(fadeDistance), mgdv(driver)
{
}


Geometries::TerrainSet::~TerrainSet()
{
}

void Geometries::TerrainSet::ApplyShaderSettings() const
{
	mgdv->ShaderLib.SetDiffuseTex( difTex );
	mgdv->ShaderLib.SetHeightTex( heightTex );
	mgdv->ShaderLib.SetTerrainFadeDistance( fadeDist );
}