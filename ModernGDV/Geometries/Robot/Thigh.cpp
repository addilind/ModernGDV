#include "Thigh.h"

#include "../Primitives/Quad.h"
#include "Dimensions.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Thigh::Thigh(ModernGDV::Driver* mgdv)
	: instanceCounter( new size_t( 1U ) ), vertexBuffer( 0U ), mgdv( mgdv ), texture( nullptr )
{
	std::vector<Vertex> vertices;

	vec3 cuboidBottomFrontLeft	( -0.5f * Dim::THG_WIDTH, -1.f * Dim::THG_HEIGHT, +0.5f * Dim::THG_DEPTH );
	vec3 cuboidBottomFrontRight	( +0.5f * Dim::THG_WIDTH, -1.f * Dim::THG_HEIGHT, +0.5f * Dim::THG_DEPTH );
	vec3 cuboidBottomBackLeft	( -0.5f * Dim::THG_WIDTH, -1.f * Dim::THG_HEIGHT, -0.5f * Dim::THG_DEPTH );
	vec3 cuboidBottomBackRight	( +0.5f * Dim::THG_WIDTH, -1.f * Dim::THG_HEIGHT, -0.5f * Dim::THG_DEPTH );
	vec3 cuboidTopFrontLeft		( -0.5f * Dim::THG_WIDTH,		Dim::THG_SHEIGHT, +0.5f * Dim::THG_DEPTH );
	vec3 cuboidTopFrontRight	( +0.5f * Dim::THG_WIDTH,		Dim::THG_SHEIGHT, +0.5f * Dim::THG_DEPTH );
	vec3 cuboidTopBackLeft		( -0.5f * Dim::THG_WIDTH,		Dim::THG_SHEIGHT, -0.5f * Dim::THG_DEPTH );
	vec3 cuboidTopBackRight		( +0.5f * Dim::THG_WIDTH,		Dim::THG_SHEIGHT, -0.5f * Dim::THG_DEPTH );

	Quad::Create(vertices, cuboidBottomFrontLeft, vec2(0.5f, 0.5f), cuboidBottomFrontRight, vec2(1.f, 0.5f),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.5f, 1.f));				//Bodenfläche Quader
	Quad::Create( vertices, cuboidTopFrontLeft, vec2( 15.f / 55.f, 0.f ), cuboidTopFrontRight, vec2( 30.f / 55.f, 0.f ),
		cuboidBottomFrontRight, vec2( 30.f / 55.f, 1.f ), cuboidBottomFrontLeft, vec2( 15.f / 55.f, 1.f ) );				//Seitenflächen Quader
	Quad::Create(vertices, cuboidTopFrontRight, vec2(0.f, 0.f), cuboidTopBackRight, vec2(15.f/55.f, 0.f),
		cuboidBottomBackRight, vec2(15.f/55.f, 1.f), cuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create( vertices, cuboidTopBackRight, vec2( 15.f / 55.f, 0.f ), cuboidTopBackLeft, vec2( 30.f / 55.f, 0.f ),
		cuboidBottomBackLeft, vec2( 30.f / 55.f, 1.f ), cuboidBottomBackRight, vec2( 15.f / 55.f, 1.f ) );
	Quad::Create(vertices, cuboidTopBackLeft, vec2(0.f, 0.f), cuboidTopFrontLeft, vec2(15.f/55.f, 0.f),
		cuboidBottomFrontLeft, vec2(15.f/55.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));
	Quad::Create( vertices, cuboidTopFrontLeft, vec2( 0.5f, 1.f ), cuboidTopBackLeft, vec2( 0.5f, 0.5f ),
		cuboidTopBackRight, vec2( 1.f, 0.5f ), cuboidTopFrontRight, vec2( 1.f, 1.f ) );					//Oberseite Quader


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("Warn");
}

Geometries::Robot::Thigh::Thigh( const Thigh& source )
	: instanceCounter( source.instanceCounter ), vertexBuffer( source.vertexBuffer ), mgdv( source.mgdv ), texture( source.texture )
{
	++*instanceCounter;
}

Geometries::Robot::Thigh::~Thigh()
{
	--*instanceCounter;
	if (*instanceCounter > 0U)
		return;

	ModernGDV::Log( "GEOM", "Destructing Thigh" );
	glDeleteBuffers( 1, &vertexBuffer );
	delete instanceCounter;
}

void Geometries::Robot::Thigh::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex( texture );
	unsigned char index = 0U;

	index = Quad::Draw(index); //Bodenfläche Quader

	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}

