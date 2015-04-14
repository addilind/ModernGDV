#ifndef TEIL3_H
#define TEIL3_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>

class Teil3 : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

public:
	Teil3( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~Teil3();

	virtual void Render() override;
private:
	void transform(const glm::mat4& transform);
	void drawCube();
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif