#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"

#include <vector>

class MyApp : public ModernGDV::App
{
private:
	GLuint vertexBuffer;

public:
	MyApp( std::vector<std::string> commandline );
	virtual ~MyApp();

	virtual void Render();
private:
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif