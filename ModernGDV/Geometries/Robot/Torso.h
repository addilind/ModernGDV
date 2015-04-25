#ifndef MGDV_TORSO_H
#define MGDV_TORSO_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

class Torso {
private:
	ModernGDV::Driver* mgdv;
	GLuint vertexBuffer;
	GLuint texture;
public:
	Torso(ModernGDV::Driver* mgdv);
	~Torso();

	void Render();
};

#endif