#include "Neck.h"

#include "../Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Neck::Neck(ModernGDV::Driver* mgdv)
	: instanceCounter( new size_t( 1U ) ), vertexBuffer( 0U ), mgdv( mgdv ), texture( nullptr )
{
	std::vector<Vertex> vertices;

	vec3 cuboidBottomFrontLeft(-0.0375f, -0.0f, +0.f);
	vec3 cuboidBottomFrontRight(+0.0375f, -0.0f, +0.f);
	vec3 cuboidBottomBackLeft(-0.0375f, -0.0f, -0.075f);
	vec3 cuboidBottomBackRight(+0.0375f, -0.0f, -0.075f);

	vec3 cuboidTopFrontLeft(-0.0375f, +0.15f, +0.f);
	vec3 cuboidTopFrontRight(+0.0375f, +0.15f, +0.f);
	vec3 cuboidTopBackLeft(-0.0375f, +0.15f, -0.075f);
	vec3 cuboidTopBackRight(+0.0375f, +0.15f, -0.075f);

	Quad::Create(vertices, cuboidBottomFrontLeft, vec2(0.f, 0.f), cuboidBottomFrontRight, vec2(1.f, 0.f),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfl�che Quader

	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.f, 0.f), cuboidTopFrontRight, vec2(1.f, 0.f),
		cuboidBottomFrontRight, vec2(1.f, 1.f), cuboidBottomFrontLeft, vec2(0.f, 1.f));				//Seitenfl�chen Quader
	Quad::Create(vertices, cuboidTopFrontRight, vec2(0.f, 0.f), cuboidTopBackRight, vec2(1.f, 0.f),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, cuboidTopBackRight, vec2(0.f, 0.f), cuboidTopBackLeft, vec2(1.f, 0.f),
		cuboidBottomBackLeft, vec2(1.f, 1.f), cuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, cuboidTopBackLeft, vec2(0.f, 0.f), cuboidTopFrontLeft, vec2(1.f, 0.f),
		cuboidBottomFrontLeft, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));

	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.f, 1.f), cuboidTopBackLeft, vec2(0.f, 0.f),
		cuboidTopBackRight, vec2(1.f, 0.f), cuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader

	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("Joint");
}

Geometries::Robot::Neck::Neck( const Neck& source )
	: instanceCounter( source.instanceCounter ), vertexBuffer( source.vertexBuffer ), mgdv( source.mgdv ), texture( source.texture )
{
	++*instanceCounter;
}

Geometries::Robot::Neck::~Neck()
{
	--*instanceCounter;
	if (*instanceCounter > 0U)
		return;

	ModernGDV::Log( "GEOM", "Destructing Neck" );
	glDeleteBuffers( 1, &vertexBuffer );
	delete instanceCounter;
}

void Geometries::Robot::Neck::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex(texture);
	unsigned char index = 0U;

	index = Quad::Draw(index); //Bodenfl�che Quader

	index = Quad::Draw(index); //Seitenfl�chen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}

