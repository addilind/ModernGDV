#include "Torso.h"

#include "Primitives/Triangle.h"
#include "Primitives/Quad.h"

using ModernGDV::Vertex;
using glm::vec3;
using glm::vec2;

Torso::Torso( ModernGDV::Driver* mgdv )
	: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	vec3 pyramidTop				( +0.00f, +0.00f, +0.00f );
	vec3 pyramidBaseFrontLeft	( -0.10f, +0.10f, +0.08f );
	vec3 pyramidBaseFrontRight	( +0.10f, +0.10f, +0.08f );
	vec3 pyramidBaseBackLeft	( -0.10f, +0.10f, -0.08f );
	vec3 pyramidBaseBackRight	( +0.10f, +0.10f, -0.08f );

	vec3 smCuboidTopFrontLeft	( -0.10f, +0.25f, +0.10f );
	vec3 smCuboidTopFrontRight	( +0.10f, +0.25f, +0.10f );
	vec3 smCuboidTopBackLeft	( -0.10f, +0.25f, -0.10f );
	vec3 smCuboidTopBackRight	( +0.10f, +0.25f, -0.10f );

	vec3 truncatedPyramidBottomFrontLeft	( -0.20f, +0.25f, +0.12f );
	vec3 truncatedPyramidBottomFrontRight	( +0.20f, +0.25f, +0.12f );
	vec3 truncatedPyramidBottomBackLeft		( -0.20f, +0.25f, -0.12f );
	vec3 truncatedPyramidBottomBackRight	( +0.20f, +0.25f, -0.12f );

	vec3 truncatedPyramidTopFrontLeft	( -0.25f, +0.45f, +0.13f );
	vec3 truncatedPyramidTopFrontRight	( +0.25f, +0.45f, +0.13f );
	vec3 truncatedPyramidTopBackLeft	( -0.25f, +0.45f, -0.13f );
	vec3 truncatedPyramidTopBackRight	( +0.25f, +0.45f, -0.13f );


	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 0.f ), pyramidBaseFrontLeft, vec2( 0.f, 1.f ), pyramidBaseFrontRight, vec2( 1.f, 1.f ) );
	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 1.f ), pyramidBaseFrontRight, vec2( 0.f, 0.f ), pyramidBaseBackRight, vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 1.f ), pyramidBaseBackRight, vec2( 0.f, 0.f ), pyramidBaseBackLeft, vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 1.f ), pyramidBaseBackLeft, vec2( 0.f, 0.f ), pyramidBaseFrontLeft, vec2( 1.f, 0.f ) );

	Quad::Create( vertices, smCuboidTopFrontLeft, vec2( 0.f, 0.f ), smCuboidTopFrontRight, vec2( 1.f, 0.f ), pyramidBaseFrontRight, vec2( 1.f, 1.f ), pyramidBaseFrontLeft, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, smCuboidTopFrontRight, vec2( 0.f, 0.f ), smCuboidTopBackRight, vec2( 1.f, 0.f ), pyramidBaseBackRight, vec2( 1.f, 1.f ), pyramidBaseFrontRight, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, smCuboidTopBackRight, vec2( 0.f, 0.f ), smCuboidTopBackLeft, vec2( 1.f, 0.f ), pyramidBaseBackLeft, vec2( 1.f, 1.f ), pyramidBaseBackRight, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, smCuboidTopBackLeft, vec2( 0.f, 0.f ), smCuboidTopFrontLeft, vec2( 1.f, 0.f ), pyramidBaseFrontLeft, vec2( 1.f, 1.f ), pyramidBaseBackLeft, vec2( 0.f, 1.f ) );

	Quad::Create( vertices, truncatedPyramidBottomFrontLeft, vec2( 0.f, 0.f ), truncatedPyramidBottomFrontRight, vec2( 1.f, 0.f ),
		truncatedPyramidBottomBackRight, vec2( 1.f, 1.f ), truncatedPyramidBottomBackLeft, vec2( 0.f, 1.f ) ); //Bodenfläche Pyramidenstumpf

	Quad::Create( vertices, truncatedPyramidTopFrontLeft, vec2( 0.f, 0.f ), truncatedPyramidTopFrontRight, vec2( 1.f, 0.f ),
		truncatedPyramidBottomFrontRight, vec2( 1.f, 1.f ), truncatedPyramidBottomFrontLeft, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, truncatedPyramidTopFrontRight, vec2( 0.f, 0.f ), truncatedPyramidTopBackRight, vec2( 1.f, 0.f ),
		truncatedPyramidBottomBackRight, vec2( 1.f, 1.f ), truncatedPyramidBottomFrontRight, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, truncatedPyramidTopBackRight, vec2( 0.f, 0.f ), truncatedPyramidTopBackLeft, vec2( 1.f, 0.f ),
		truncatedPyramidBottomBackLeft, vec2( 1.f, 1.f ), truncatedPyramidBottomBackRight, vec2( 0.f, 1.f ) );
	Quad::Create( vertices, truncatedPyramidTopBackLeft, vec2( 0.f, 0.f ), truncatedPyramidTopFrontLeft, vec2( 1.f, 0.f ),
		truncatedPyramidBottomFrontLeft, vec2( 1.f, 1.f ), truncatedPyramidBottomBackLeft, vec2( 0.f, 1.f ) );

	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture( "test" );
}

Torso::~Torso()
{

}

void Torso::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();

	mgdv->UseTexture( texture );
	Tri::Draw( 0U );
	Tri::Draw( 3U );
	Tri::Draw( 6U );
	Tri::Draw( 9U );

	Quad::Draw( 12U );
	Quad::Draw( 16U );
	Quad::Draw( 20U );
	Quad::Draw( 24U );

	Quad::Draw( 28U );

	Quad::Draw( 32U );
	Quad::Draw( 36U );
	Quad::Draw( 40U );
	Quad::Draw( 44U );


	Vertex::ResetLayout();
}
