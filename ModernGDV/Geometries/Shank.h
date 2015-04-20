#ifndef MGDV_Shank_H
#define MGDV_Shank_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../ModernGDV/MGDVVertex.h"

class Shank {
private:
	GLuint vertexBuffer;
public:
	Shank();
	~Shank();

	void Render();
	void createVertexBuffer(const std::vector<ModernGDV::ColorVertex>& vertexBufferData);
};

#endif