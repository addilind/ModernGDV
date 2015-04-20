#ifndef MGDV_Thigh_H
#define MGDV_Thigh_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../ModernGDV/MGDVVertex.h"

class Thigh {
private:
	GLuint vertexBuffer;
public:
	Thigh();
	~Thigh();

	void Render();
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif