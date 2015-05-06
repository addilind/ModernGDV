#include "Terrain.h"
#include "Primitives/Quad.h"

using glm::vec2;
using glm::vec3;
using Geometries::Primitives::Quad;
using ModernGDV::Vertex;

Geometries::Terrain::Terrain( ModernGDV::Driver* mgdv, unsigned int segments )
	:mgdv(mgdv), shader(0U), segs(segments)
{
	shader = mgdv->ShaderLib.GetShaderID( "terrain" );

	//vec3 backLeft( -1.f, 0.f, -1.f );
	//vec3 backRight( -1.f + 2.f / segments, 0.f, -1.f );
	//vec3 frontRight( -1.f + 2.f / segments, 0.f, -1.f + 2.f / segments );
	//vec3 frontLeft( -1.f, 0.f, -1.f + 2.f / segments );
	//Quad::Create( vertices, backLeft, vec2( 0.f, 0.f ), backRight, vec2( 1.f/segments, 0.f ),
	//	frontRight, vec2( 1.f / segments, 1.f / segments ), frontLeft, vec2( 0.f, 1.f / segments ) );

	std::vector<Vertex> vertices;

	float space = 2.f / segments;
	float uvspace = 1.f / segments;

	for (unsigned int i = 0U; i <= segments; ++i)
	{
		vertices.push_back( Vertex( -1.f, 0.f, -1.f + (i * space), 0.f, 1.f, 0.f, 0.f, i*uvspace ) );
		vertices.push_back( Vertex( -1.f + space, 0.f, -1.f + (i * space), 0.f, 1.f, 0.f, uvspace, i*uvspace ) );
	}

	vertexBuffer = mgdv->CreateVertexBuffer( vertices );
}

Geometries::Terrain::~Terrain()
{
}

void Geometries::Terrain::Render()
{
	mgdv->ShaderLib.UseShader( shader );

	mgdv->ShaderLib.SetDiffuseTex( mgdv->GetTexture( "skybox" ) );
	mgdv->ShaderLib.SetHeightTex( mgdv->GetTexture( "test_hmap" ) );
	mgdv->ShaderLib.SetTerrainSegmentSize( 1.f / segs );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	ModernGDV::Vertex::SetLayout();

	glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0U, (segs + 1U)*2U, segs);

	ModernGDV::Vertex::ResetLayout();
}
