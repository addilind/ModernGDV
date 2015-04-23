#ifndef MGDV_TRIANGLE_H
#define MGDV_TRIANGLE_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"

namespace Tri
{
	void Create( std::vector<ModernGDV::Vertex>& vertices,
		const glm::vec3& posA, const glm::vec2& uvA,
		const glm::vec3& posB, const glm::vec2& uvB,
		const glm::vec3& posC, const glm::vec2& uvC );
}

#endif