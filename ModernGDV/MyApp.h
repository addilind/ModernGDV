#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>
#include "Geometries/Robot/Robot.h"
#include "ModernGDV/Camera.h"

class MyApp : public ModernGDV::App
{
private:
	ModernGDV::Driver* mgdv;

	Geometries::Robot::Robot robot;
	ModernGDV::Camera camera;
	GLuint lampvb;
	GLuint lamptex;

public:
	MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv );
	virtual ~MyApp();

	virtual void Render( float deltaT ) override;
};

#endif