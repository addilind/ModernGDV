#include "Torso.h"

#include "../Primitives/Triangle.h"
#include "../Primitives/Quad.h"
#include "Dimensions.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using Geometries::Primitives::Tri;
using glm::vec3;
using glm::vec2;

Geometries::Robot::Torso::Torso( ModernGDV::Driver* mgdv )
	: mgdv(mgdv), vertexBuffer(0U), texture(nullptr)
{
	std::vector<Vertex> vertices;

	vec3 pyramidTop				( +0.00f, Dim::TOR_LOWEST, +0.00f );
	vec3 pyramidBaseFrontLeft	( -0.5f * Dim::TOR_PYR_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT, +0.5f * Dim::TOR_PYR_DEPTH );
	vec3 pyramidBaseFrontRight	( +0.5f * Dim::TOR_PYR_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT, +0.5f * Dim::TOR_PYR_DEPTH );
	vec3 pyramidBaseBackLeft	( -0.5f * Dim::TOR_PYR_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT, -0.5f * Dim::TOR_PYR_DEPTH );
	vec3 pyramidBaseBackRight	( +0.5f * Dim::TOR_PYR_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT, -0.5f * Dim::TOR_PYR_DEPTH );

	vec3 smCuboidTopFrontLeft	( -0.5f * Dim::TOR_SCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, +0.5f * Dim::TOR_SCB_DEPTH );
	vec3 smCuboidTopFrontRight	( +0.5f * Dim::TOR_SCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, +0.5f * Dim::TOR_SCB_DEPTH );
	vec3 smCuboidTopBackLeft	( -0.5f * Dim::TOR_SCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, -0.5f * Dim::TOR_SCB_DEPTH );
	vec3 smCuboidTopBackRight	( +0.5f * Dim::TOR_SCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, -0.5f * Dim::TOR_SCB_DEPTH );

	vec3 truncatedPyramidBottomFrontLeft	( -0.5f * Dim::TOR_TPR_BWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, +0.5f * Dim::TOR_TPR_BDEPTH );
	vec3 truncatedPyramidBottomFrontRight	( +0.5f * Dim::TOR_TPR_BWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, +0.5f * Dim::TOR_TPR_BDEPTH );
	vec3 truncatedPyramidBottomBackLeft		( -0.5f * Dim::TOR_TPR_BWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, -0.5f * Dim::TOR_TPR_BDEPTH );
	vec3 truncatedPyramidBottomBackRight	( +0.5f * Dim::TOR_TPR_BWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT, -0.5f * Dim::TOR_TPR_BDEPTH );

	vec3 truncatedPyramidTopFrontLeft	( -0.5f * Dim::TOR_TPR_TWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, +0.5f * Dim::TOR_TPR_TDEPTH );
	vec3 truncatedPyramidTopFrontRight	( +0.5f * Dim::TOR_TPR_TWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, +0.5f * Dim::TOR_TPR_TDEPTH );
	vec3 truncatedPyramidTopBackLeft	( -0.5f * Dim::TOR_TPR_TWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, -0.5f * Dim::TOR_TPR_TDEPTH );
	vec3 truncatedPyramidTopBackRight	( +0.5f * Dim::TOR_TPR_TWIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, -0.5f * Dim::TOR_TPR_TDEPTH );
	
	
	vec3 cuboidBottomFrontLeft	( -0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, +0.5f * Dim::TOR_BCB_DEPTH );
	vec3 cuboidBottomFrontRight	( +0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, +0.5f * Dim::TOR_BCB_DEPTH );
	vec3 cuboidBottomBackLeft	( -0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, -0.5f * Dim::TOR_BCB_DEPTH );
	vec3 cuboidBottomBackRight	( +0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT, -0.5f * Dim::TOR_BCB_DEPTH );

	vec3 cuboidTopFrontLeft	( -0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT + Dim::TOR_BCB_HEIGHT, +0.5f * Dim::TOR_BCB_DEPTH );
	vec3 cuboidTopFrontRight( +0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT + Dim::TOR_BCB_HEIGHT, +0.5f * Dim::TOR_BCB_DEPTH );
	vec3 cuboidTopBackLeft	( -0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT + Dim::TOR_BCB_HEIGHT, -0.5f * Dim::TOR_BCB_DEPTH );
	vec3 cuboidTopBackRight	( +0.5f * Dim::TOR_BCB_WIDTH, Dim::TOR_LOWEST + Dim::TOR_PYR_HEIGHT + Dim::TOR_SCB_HEIGHT + Dim::TOR_TPR_HEIGHT + Dim::TOR_BCB_HEIGHT, -0.5f * Dim::TOR_BCB_DEPTH );
	
	static const float n26 = 1.f / 26.f;

	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 0.f ), pyramidBaseFrontLeft, vec2( 0.f, 1.f ), pyramidBaseFrontRight, vec2( 1.f, 1.f ) ); //Seitenflächen Pyramide
	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 1.f ), pyramidBaseFrontRight, vec2( 0.f, 0.f ), pyramidBaseBackRight, vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 1.f ), pyramidBaseBackRight, vec2( 0.f, 0.f ), pyramidBaseBackLeft, vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, vec2( 0.5f, 1.f ), pyramidBaseBackLeft, vec2( 0.f, 0.f ), pyramidBaseFrontLeft, vec2( 1.f, 0.f ) );
	/*********************************************************************************************************************/
	Quad::Create( vertices, smCuboidTopFrontLeft, vec2( 0.f, 0.f ), smCuboidTopFrontRight, vec2( 1.f, 0.f ), pyramidBaseFrontRight, vec2( 1.f, 0.75f ), pyramidBaseFrontLeft, vec2( 0.f, 0.75f ) ); //Seitenflächen kleiner Quader
	Quad::Create(vertices, smCuboidTopFrontRight, vec2(0.f, 0.f), smCuboidTopBackRight, vec2(1.f, 0.f), pyramidBaseBackRight, vec2(1.f, 0.75f), pyramidBaseFrontRight, vec2(0.f, 0.75f));
	Quad::Create(vertices, smCuboidTopBackRight, vec2(0.f, 0.f), smCuboidTopBackLeft, vec2(1.f, 0.f), pyramidBaseBackLeft, vec2(1.f, 0.75f), pyramidBaseBackRight, vec2(0.f, 0.75f));
	Quad::Create(vertices, smCuboidTopBackLeft, vec2(0.f, 0.f), smCuboidTopFrontLeft, vec2(1.f, 0.f), pyramidBaseFrontLeft, vec2(1.f, 0.75f), pyramidBaseBackLeft, vec2(0.f, 0.75f));
	/*********************************************************************************************************************/
	Quad::Create( vertices, truncatedPyramidBottomFrontLeft, vec2( 0.f, 0.f ), truncatedPyramidBottomFrontRight, vec2( 1.f, 0.f ),
		truncatedPyramidBottomBackRight, vec2( 1.f, 24.f/40.f ), truncatedPyramidBottomBackLeft, vec2( 0.f, 24.f/40.f ) );		//Bodenfläche Pyramidenstumpf
	Quad::Create( vertices, truncatedPyramidTopFrontLeft, vec2( 0.f, 0.f ), truncatedPyramidTopFrontRight, vec2( 1.f, 0.f ),
		truncatedPyramidBottomFrontRight, vec2( 0.9f, 0.4f ), truncatedPyramidBottomFrontLeft, vec2( 0.1f, 0.4f ) );	//Seitenflächen Pyramidenstumpf
	Quad::Create( vertices, truncatedPyramidTopFrontRight, vec2( 0.f, 0.f ), truncatedPyramidTopBackRight, vec2( 1.f, 0.f ),
		truncatedPyramidBottomBackRight, vec2( 25.f* n26, 20.f * n26 ), truncatedPyramidBottomFrontRight, vec2( n26, 20.f*n26 ) );
	Quad::Create( vertices, truncatedPyramidTopBackRight, vec2( 0.f, 0.f ), truncatedPyramidTopBackLeft, vec2( 1.f, 0.f ),
		truncatedPyramidBottomBackLeft, vec2( 0.9f, 0.4f ), truncatedPyramidBottomBackRight, vec2( 0.1f, 0.4f ) );
	Quad::Create( vertices, truncatedPyramidTopBackLeft, vec2( 0.f, 0.f ), truncatedPyramidTopFrontLeft, vec2( 1.f, 0.f ),
		truncatedPyramidBottomFrontLeft, vec2( 25.f*n26, 20.f*n26 ), truncatedPyramidBottomBackLeft, vec2( n26, 20.f*n26 ) );
	/*********************************************************************************************************************/
	Quad::Create( vertices, cuboidBottomFrontLeft, vec2( 0.f, 0.f ), cuboidBottomFrontRight, vec2( 1.f, 0.f ),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfläche Quader
	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.f, 0.f), cuboidTopFrontRight, vec2(1.f, 0.f),
		cuboidBottomFrontRight, vec2(1.f, 1.f), cuboidBottomFrontLeft, vec2(0.f, 1.f));				//Seitenflächen Quader
	Quad::Create(vertices, cuboidTopFrontRight, vec2(0.f, 0.f), cuboidTopBackRight, vec2(1.f, 0.f),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, cuboidTopBackRight, vec2(0.f, 0.f), cuboidTopBackLeft, vec2(1.f, 0.f),
		cuboidBottomBackLeft, vec2(1.f, 1.f), cuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, cuboidTopBackLeft, vec2(0.f, 0.f), cuboidTopFrontLeft, vec2(1.f, 0.f),
		cuboidBottomFrontLeft, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.f, 1.f), cuboidTopBackLeft, vec2(0.f, 0.f),
		cuboidTopBackRight, vec2(1.f, 0.f), cuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture( "blubb" );
}

Geometries::Robot::Torso::~Torso()
{

}

void Geometries::Robot::Torso::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();

	mgdv->ShaderLib.SetDiffuseTex( texture );
	unsigned char index = 0U;
	index = Tri::Draw(index);
	index = Tri::Draw(index);
	index = Tri::Draw(index);
	index = Tri::Draw(index);

	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index);

	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index); //Bodenfläche Quader
	
	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	
	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}
