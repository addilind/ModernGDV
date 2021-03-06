#include "Shank.h"

#include "../Primitives/Quad.h"
#include "Dimensions.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Shank::Shank(ModernGDV::Driver* mgdv)
	: instanceCounter( new size_t( 1U ) ), vertexBuffer( 0U ), mgdv( mgdv ), texture( nullptr )
{
	std::vector<Vertex> vertices;

	//Unterschenkel linke Seite
	vec3 lCuboidBottomFrontLeft	( -0.5f * Dim::SNK_WIDTH,	-1.f * Dim::SNK_HEIGHT, +0.5f * Dim::SNK_DEPTH);
	vec3 lCuboidBottomFrontRight( -0.5f * Dim::SNK_IWIDTH,	-1.f * Dim::SNK_HEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 lCuboidBottomBackLeft	( -0.5f * Dim::SNK_WIDTH,	-1.f * Dim::SNK_HEIGHT, -0.5f * Dim::SNK_DEPTH );
	vec3 lCuboidBottomBackRight	( -0.5f * Dim::SNK_IWIDTH,	-1.f * Dim::SNK_HEIGHT, -0.5f * Dim::SNK_DEPTH );
	vec3 lCuboidTopFrontLeft	( -0.5f * Dim::SNK_WIDTH,		  Dim::SNK_SHEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 lCuboidTopFrontRight	( -0.5f * Dim::SNK_IWIDTH,		  Dim::SNK_SHEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 lCuboidTopBackLeft		( -0.5f * Dim::SNK_WIDTH,		  Dim::SNK_SHEIGHT, -0.5f * Dim::SNK_DEPTH );
	vec3 lCuboidTopBackRight	( -0.5f * Dim::SNK_IWIDTH,		  Dim::SNK_SHEIGHT, -0.5f * Dim::SNK_DEPTH );

	//Unterschenkel rechte Seite
	vec3 rCuboidBottomFrontLeft	( +0.5f * Dim::SNK_IWIDTH,	-1.f * Dim::SNK_HEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidBottomFrontRight( +0.5f * Dim::SNK_WIDTH,	-1.f * Dim::SNK_HEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidBottomBackLeft	( +0.5f * Dim::SNK_IWIDTH,	-1.f * Dim::SNK_HEIGHT, -0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidBottomBackRight	( +0.5f * Dim::SNK_WIDTH,	-1.f * Dim::SNK_HEIGHT, -0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidTopFrontLeft	( +0.5f * Dim::SNK_IWIDTH,		  Dim::SNK_SHEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidTopFrontRight	( +0.5f * Dim::SNK_WIDTH,		  Dim::SNK_SHEIGHT, +0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidTopBackLeft		( +0.5f * Dim::SNK_IWIDTH,		  Dim::SNK_SHEIGHT, -0.5f * Dim::SNK_DEPTH );
	vec3 rCuboidTopBackRight	( +0.5f * Dim::SNK_WIDTH,		  Dim::SNK_SHEIGHT, -0.5f * Dim::SNK_DEPTH );

	//Bodenfläche Quader
	Quad::Create(vertices, lCuboidBottomFrontLeft, vec2(0.f, 0.f), lCuboidBottomFrontRight, vec2(7.5f/16.f, 0.f),
		lCuboidBottomBackRight, vec2(7.5f/16.f, 1.f), lCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, lCuboidTopFrontLeft, vec2(0.f, 0.f), lCuboidTopFrontRight, vec2(7.5f/50.f, 0.f),
		lCuboidBottomFrontRight, vec2(7.5f/50.f, 1.f), lCuboidBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, lCuboidTopFrontRight, vec2(0.f, 0.f), lCuboidTopBackRight, vec2(16.f/50.f, 0.f),
		lCuboidBottomBackRight, vec2(16.f/50.f, 1.f), lCuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, lCuboidTopBackRight, vec2(0.f, 0.f), lCuboidTopBackLeft, vec2(7.5f/50.f, 0.f),
		lCuboidBottomBackLeft, vec2(7.5f/50.f, 1.f), lCuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, lCuboidTopBackLeft, vec2(0.f, 0.f), lCuboidTopFrontLeft, vec2(16.f/50.f, 0.f),
		lCuboidBottomFrontLeft, vec2(16.f/50.f, 1.f), lCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, lCuboidTopFrontLeft, vec2(0.f, 1.f), lCuboidTopBackLeft, vec2(0.f, 0.f),
		lCuboidTopBackRight, vec2(7.5f/16.f, 0.f), lCuboidTopFrontRight, vec2(7.5f/16.f, 1.f));


	//Bodenfläche Quader
	Quad::Create(vertices, rCuboidBottomFrontLeft, vec2(0.f, 0.f), rCuboidBottomFrontRight, vec2(7.5f / 16.f, 0.f),
		rCuboidBottomBackRight, vec2(7.5f / 16.f, 1.f), rCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, rCuboidTopFrontLeft, vec2(0.f, 0.f), rCuboidTopFrontRight, vec2(7.5f / 50.f, 0.f),
		rCuboidBottomFrontRight, vec2(7.5f / 50.f, 1.f), rCuboidBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, rCuboidTopFrontRight, vec2(0.f, 0.f), rCuboidTopBackRight, vec2(16.f / 50.f, 0.f),
		rCuboidBottomBackRight, vec2(16.f / 50.f, 1.f), rCuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, rCuboidTopBackRight, vec2(0.f, 0.f), rCuboidTopBackLeft, vec2(7.5f / 50.f, 0.f),
		rCuboidBottomBackLeft, vec2(7.5f / 50.f, 1.f), rCuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, rCuboidTopBackLeft, vec2(0.f, 0.f), rCuboidTopFrontLeft, vec2(16.f / 50.f, 0.f),
		rCuboidBottomFrontLeft, vec2(16.f / 50.f, 1.f), rCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, rCuboidTopFrontLeft, vec2(0.f, 1.f), rCuboidTopBackLeft, vec2(0.f, 0.f),
		rCuboidTopBackRight, vec2(7.5f / 16.f, 0.f), rCuboidTopFrontRight, vec2(7.5f / 16.f, 1.f));

	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture( "Dummy" );
}

Geometries::Robot::Shank::Shank( const Shank& source )
	: instanceCounter( source.instanceCounter ), vertexBuffer( source.vertexBuffer ), mgdv( source.mgdv ), texture( source.texture )
{
	++*instanceCounter;
}

Geometries::Robot::Shank::~Shank()
{
	--*instanceCounter;
	if (*instanceCounter > 0U)
		return;

	ModernGDV::Log( "GEOM", "Destructing Shank" );
	glDeleteBuffers( 1, &vertexBuffer );
	delete instanceCounter;
}

void Geometries::Robot::Shank::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex( texture );
	unsigned char index = 0U;
	//Unterschenkel linke Seite
	index = Quad::Draw(index); //Bodenfläche Quader
	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index); //Oberseite Quader

	//Unterschenkel rechte Seite
	index = Quad::Draw(index); //Bodenfläche Quader
	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}

