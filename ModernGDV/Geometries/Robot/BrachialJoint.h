#ifndef MGDV_BrachialJoint_H
#define MGDV_BrachialJoint_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

class BrachialJoint {
private:
	GLuint vertexBuffer;
	ModernGDV::Driver* mgdv;
	GLuint texture;
public:
	BrachialJoint(ModernGDV::Driver* mgdv);
	~BrachialJoint();

	void Render();

};

#endif