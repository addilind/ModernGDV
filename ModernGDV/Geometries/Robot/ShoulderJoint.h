#ifndef MGDV_SHOULDERJOINT_H
#define MGDV_SHOULDERJOINT_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

class ShoulderJoint {
private:
	GLuint vertexBuffer;
	ModernGDV::Driver* mgdv;
	GLuint texture;
public:
	ShoulderJoint(ModernGDV::Driver* mgdv);
	~ShoulderJoint();

	void Render();

};

#endif