#ifndef TEIL4_H
#define TEIL4_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>

class Teil4 : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

public:
	Teil4( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~Teil4();

	virtual void Render() override;
private:
	void transform(const glm::mat4& transform);
	void drawCube();
	void drawWireCube();
	void drawSquare();
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif