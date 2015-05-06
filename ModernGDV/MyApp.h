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

	Geometries::Robot::Robot robot;
	ModernGDV::Camera camera;
	GLuint lampvb;
	ModernGDV::Textures::Texture* lamptex;
	Geometries::Terrain terrain;

public:
	MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv );
	virtual ~MyApp();

	virtual void Update( float deltaT ) override;
	virtual void Render(  ) override;
};

#endif