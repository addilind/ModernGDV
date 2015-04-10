#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>

class MyApp : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

public:
	MyApp( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~MyApp();

	virtual void Render();
private:
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif