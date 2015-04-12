#ifndef TEIL2_H
#define TEIL2_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>

class Teil2 : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

public:
	Teil2( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~Teil2();

	virtual void Render() override;
private:
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif