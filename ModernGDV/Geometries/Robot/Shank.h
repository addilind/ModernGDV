#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"
#include "../../ModernGDV/ModernGDV.h"

class Shank {
private:
	GLuint vertexBuffer;
	ModernGDV::Driver* mgdv;
	GLuint texture;
public:
	Shank(ModernGDV::Driver* mgdv);
	~Shank();

	void Render();

};