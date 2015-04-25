#ifndef MGDV_SKYBOX_H
#define MGDV_SKYBOX_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../ModernGDV/MGDVVertex.h"
#include "../ModernGDV/ModernGDV.h"

class Skybox
{
	GLuint vertexBuffer;
	ModernGDV::Driver* mgdv;
	GLuint texture;
public:
	Skybox( ModernGDV::Driver* mgdv );
	~Skybox();

	void Render();
};

#endif