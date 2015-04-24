#ifndef MGDV_Thigh_H
#define MGDV_Thigh_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../ModernGDV/MGDVVertex.h"
#include "../ModernGDV/ModernGDV.h"

class Thigh {
private:
	GLuint vertexBuffer;
	ModernGDV::Driver* mgdv;
	GLuint texture;
public:
	Thigh(ModernGDV::Driver* mgdv);
	~Thigh();

	void Render();

};

#endif