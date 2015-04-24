#ifndef MGDV_TORSO_H
#define MGDV_TORSO_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../ModernGDV/MGDVVertex.h"
#include "../ModernGDV/ModernGDV.h"

class Torso {
private:
	ModernGDV::ModernGDV* mgdv;
	GLuint vertexBuffer;
	GLuint texture;
public:
	Torso(ModernGDV::ModernGDV* mgdv);
	~Torso();

	void Render();
	void createVertexBuffer(const std::vector<ModernGDV::Vertex>& vertexBufferData);
};

#endif