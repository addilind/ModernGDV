#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>
#include "Geometries\Robot.h"
#include "Geometries/Skybox.h"

class MyApp : public ModernGDV::App
{
private:
	ModernGDV::Driver* mgdv;
	
	Robot robot;
	Skybox sky;
	GLuint lampvb;
	GLuint lamptex;

public:
	MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv );
	virtual ~MyApp();

	virtual void Render() override;
};

#endif