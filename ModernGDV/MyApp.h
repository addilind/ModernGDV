#ifndef MYAPP_H
#define MYAPP_H

#include "ModernGDV/MGDVApp.h"

#include <vector>

class MyApp : public ModernGDV::App
{
private:
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLfloat* vertexBufferData;

public:
	MyApp( std::vector<std::string> commandline );
	virtual ~MyApp();

	virtual void Render();
private:
	GLuint createVertexArray();
	void createVertexBuffer();
};

#endif