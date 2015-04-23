#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>
#include "Geometries\Robot.h"
class MyApp : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;
	
	Robot robot;

public:
	MyApp( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~MyApp();

	virtual void Render() override;
};

#endif