#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>
#include "Geometries/Robot/Robot.h"
#include "ModernGDV/Camera.h"
#include "Geometries/Terrain.h"

class MyApp : public ModernGDV::App
{
private:
	ModernGDV::Driver* mgdv;

	std::vector<Geometries::Robot::Robot> robots;
	ModernGDV::Camera camera;
	GLuint lampvb;
	ModernGDV::Textures::Texture* lamptex;
	Geometries::Terrain terrain;
	Geometries::Terrain lowsegterrain;
	Geometries::TerrainSet terrain_slope;
	Geometries::TerrainSet terrain_bgmountain;
	Geometries::TerrainSet terrain_glacier;

public:
	MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv );
	virtual ~MyApp();

	virtual void Update( float deltaT ) override;
	virtual void Render(  ) override;
private:
	void drawSlope();
	void drawSceneryTerrain();
};

#endif