#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>
#include "Geometries\Primitives\Primitive.h"
#include "Geometries\Primitives\Cube.h"
#include "Geometries\Torso.h"
#include "Geometries\Thigh.h"
#include "Geometries\Shank.h"

class MyApp : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	//std::vector<Primitive> primitives;
	Torso testtorso;
	Thigh testthigh;
	Shank testshank;
public:
	MyApp( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~MyApp();

	virtual void Render() override;
private:
	void transform(const glm::mat4& transform);
};

#endif