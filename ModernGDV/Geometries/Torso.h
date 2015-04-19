#ifndef MGDV_TORSO_H
#define MGDV_TORSO_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../ModernGDV/MGDVVertex.h"

class Torso {
private:
	GLuint vertexBuffer;
public:
	Torso();
	~Torso();

	void Render();
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif