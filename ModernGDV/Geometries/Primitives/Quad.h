#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"

namespace Geometries
{
	namespace Primitives
	{
		struct Quad
		{
			//ABCD sind die Eckpunkte im Uhrzeigersinn
			static inline void Create( std::vector<ModernGDV::Vertex>& vertices,
				const glm::vec3& posA, const glm::vec2& uvA,
				const glm::vec3& posB, const glm::vec2& uvB,
				const glm::vec3& posC, const glm::vec2& uvC,
				const glm::vec3& posD, const glm::vec2& uvD ) //uv Koordinaten für Textur
			{
				/*
				 *	A------B
				 *  |      |
				 *  D------C
				 */
				glm::vec3 normalA = glm::cross( posD - posA, posB - posA );
				glm::vec3 normalB = glm::cross( posB - posC, posD - posC );
				glm::vec3 normalMid = normalA + normalB; //doppelt so lang, Mittel zwischen den zwei Normalen
				vertices.push_back( ModernGDV::Vertex( posA.x, posA.y, posA.z, normalA.x, normalA.y, normalA.z, uvA.x, uvA.y ) );
				vertices.push_back( ModernGDV::Vertex( posB.x, posB.y, posB.z, normalMid.x, normalMid.y, normalMid.z, uvB.x, uvB.y ) );
				vertices.push_back( ModernGDV::Vertex( posD.x, posD.y, posD.z, normalMid.x, normalMid.y, normalMid.z, uvD.x, uvD.y ) );
				vertices.push_back( ModernGDV::Vertex( posC.x, posC.y, posC.z, normalB.x, normalB.y, normalB.z, uvC.x, uvC.y ) );
			}

			static inline unsigned char Draw( uint16_t startIndex )
			{
				glDrawArrays( GL_TRIANGLE_STRIP, startIndex, 4U );
				return startIndex + 4U;
			}
		};
	}
}
