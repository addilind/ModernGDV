#include "Terrain.h"
#include "Primitives/Quad.h"

using glm::vec2;
using glm::vec3;
using Geometries::Primitives::Quad;
using ModernGDV::UVVertex;

Geometries::Terrain::Terrain( ModernGDV::Driver* mgdv, unsigned int segments )
	:mgdv(mgdv), shader(0U), segs(segments)
{
	shader = mgdv->ShaderLib.GetShaderID( "terrain" );

	std::vector<UVVertex> vertices;

	float space = 2.f / segments;
	float uvspace = 1.f / segments;

	for (unsigned int i = 0U; i <= segments; ++i)
	{
		vertices.push_back(UVVertex( -1.f, 0.f, -1.f + (i * space), 0.f, i*uvspace ) );
		vertices.push_back(UVVertex( -1.f + space, 0.f, -1.f + (i * space), uvspace, i*uvspace ) );
	}

	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( UVVertex ), &vertices[0], GL_STATIC_DRAW );
}

Geometries::Terrain::~Terrain()
{
}

void Geometries::Terrain::Render( const TerrainSet& set )
{
	mgdv->ShaderLib.UseShader( shader );
	set.ApplyShaderSettings();
	mgdv->ShaderLib.SetTerrainSegmentSize( 1.f / segs );
	mgdv->ShaderLib.SetSpecularProperties(vec3(0.5f), 1.f);

	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	UVVertex::SetLayout();

	glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0U, (segs + 1U)*2U, segs); // segs +1*2 wegen linien bzw. *2 wegen Punkten - Anzahl der Punkte übergeben

	UVVertex::ResetLayout();
}
