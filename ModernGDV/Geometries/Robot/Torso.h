#pragma once

#include "../../ModernGDV/OGLInc.h"
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
