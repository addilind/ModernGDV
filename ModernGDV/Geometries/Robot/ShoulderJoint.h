#pragma once

#include "../../ModernGDV/OGLInc.h"
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
