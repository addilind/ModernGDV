#pragma once

#include "../../ModernGDV/OGLInc.h"
#include <vector>

#include "../../ModernGDV/MGDVVertex.h"

namespace Geometries
{
	namespace Primitives
	{
		struct Tri
		{
			static inline void Create( std::vector<ModernGDV::Vertex>& vertices,
				const glm::vec3& posA, const glm::vec2& uvA,
				const glm::vec3& posB, const glm::vec2& uvB,
				const glm::vec3& posC, const glm::vec2& uvC )
			{
				glm::vec3 normal = glm::cross( posC - posA, posB - posA ); //Uhrzeigersinn, Normale nach auﬂen, 
				vertices.push_back( ModernGDV::Vertex( posA.x, posA.y, posA.z, normal.x, normal.y, normal.z, uvA.x, uvA.y ) );
				vertices.push_back( ModernGDV::Vertex( posB.x, posB.y, posB.z, normal.x, normal.y, normal.z, uvB.x, uvB.y ) );
				vertices.push_back( ModernGDV::Vertex( posC.x, posC.y, posC.z, normal.x, normal.y, normal.z, uvC.x, uvC.y ) );
			}

			static inline void Draw( unsigned char indexA, unsigned char indexB, unsigned char indexC )
			{
				unsigned char indices[3] = { indexA, indexB, indexC };
				glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices );
			}

			static inline unsigned char Draw( unsigned char startIndex )
			{
				Draw( startIndex, startIndex + 1U, startIndex + 2U );
				return startIndex + 3U;
			}
		};
	}
}