#ifndef MGDV_QUAD_H
#define MGDV_QUAD_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"

namespace Quad
{
	//ABCD sind die Eckpunkte im Uhrzeigersinn
	inline void Create( std::vector<ModernGDV::Vertex>& vertices,
		const glm::vec3& posA, const glm::vec2& uvA,
		const glm::vec3& posB, const glm::vec2& uvB,
		const glm::vec3& posC, const glm::vec2& uvC,
		const glm::vec3& posD, const glm::vec2& uvD )
	{
		/*
		 *	A------B
		 *  |      |
		 *  D------C
		 */
		glm::vec3 normalA = glm::cross( posD - posA, posB - posA );
		glm::vec3 normalB = glm::cross( posB - posC, posD - posC );
		glm::vec3 normalMid = normalA + normalB;
		vertices.push_back( ModernGDV::Vertex( posA.x, posA.y, posA.z, normalA.x, normalA.y, normalA.z, uvA.x, uvA.y ) );
		vertices.push_back( ModernGDV::Vertex( posB.x, posB.y, posB.z, normalMid.x, normalMid.y, normalMid.z, uvB.x, uvB.y ) );
		vertices.push_back( ModernGDV::Vertex( posC.x, posC.y, posC.z, normalB.x, normalB.y, normalB.z, uvC.x, uvC.y ) );
		vertices.push_back( ModernGDV::Vertex( posD.x, posD.y, posD.z, normalMid.x, normalMid.y, normalMid.z, uvD.x, uvD.y ) );
	}

	inline void Draw( unsigned char indexA, unsigned char indexB, unsigned char indexC, unsigned char indexD )
	{
		unsigned char indices[4] = { indexA, indexB, indexD, indexC };
		glDrawElements( GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices );
	}

	inline void Draw( unsigned char startIndex)
	{
		Draw( startIndex, startIndex + 1U, startIndex + 2U, startIndex + 3U );
	}
}

#endif