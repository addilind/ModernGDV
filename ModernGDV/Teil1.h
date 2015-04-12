#ifndef TEIL1_H
#define TEIL1_H

#include "ModernGDV/MGDVApp.h"
#include "ModernGDV/ModernGDV.h"

#include <vector>

class Teil1 : public ModernGDV::App
{
private:
	ModernGDV::ModernGDV* mgdv;

	GLuint shaderTransform;

	GLuint vertexBuffer;

public:
	Teil1( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv );
	virtual ~Teil1();

	virtual void Render() override;
private:
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif