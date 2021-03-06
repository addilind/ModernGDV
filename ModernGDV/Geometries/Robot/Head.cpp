#include "Head.h"

#include "../Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Head::Head(ModernGDV::Driver* mgdv)
	: instanceCounter( new size_t( 1U ) ), vertexBuffer( 0U ), mgdv( mgdv ), texture( nullptr )
{
	std::vector<Vertex> vertices;
	//Kopf
	vec3 cuboidBottomFrontLeft(-0.12f, -0.0f, +0.12f);
	vec3 cuboidBottomFrontRight(+0.12f, -0.0f, +0.12f);
	vec3 cuboidBottomBackLeft(-0.12f, -0.0f, -0.12f);
	vec3 cuboidBottomBackRight(+0.12f, -0.0f, -0.12f);

	vec3 cuboidTopFrontLeft(-0.12f, +0.25f, +0.12f);
	vec3 cuboidTopFrontRight(+0.12f, +0.25f, +0.12f);
	vec3 cuboidTopBackLeft(-0.12f, +0.25f, -0.12f);
	vec3 cuboidTopBackRight(+0.12f, +0.25f, -0.12f);

	//Texturwerte aus Skizze entnommen
	Quad::Create(vertices, cuboidBottomFrontLeft, vec2(0.f, 1.f), cuboidBottomFrontRight, vec2(0.25f, 1.f),
		cuboidBottomBackRight, vec2(0.25f, 0.75f), cuboidBottomBackLeft, vec2(0.f, 0.75f));				//Bodenfläche Quader
	
	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.f, 0.f), cuboidTopFrontRight, vec2(0.5f, 0.f),
		cuboidBottomFrontRight, vec2(0.5f, 0.5f), cuboidBottomFrontLeft, vec2(0.f, 0.5f));				//Vorderseite
	Quad::Create(vertices, cuboidTopFrontRight, vec2(0.75f, 0.f), cuboidTopBackRight, vec2(1.f, 0.f),
		cuboidBottomBackRight, vec2(1.f, 0.25f), cuboidBottomFrontRight, vec2(0.75f, 0.25f));
	Quad::Create(vertices, cuboidTopBackRight, vec2(0.75f, 0.25f), cuboidTopBackLeft, vec2(1.f, 0.25f),
		cuboidBottomBackLeft, vec2(1.f, 0.5f), cuboidBottomBackRight, vec2(0.75f, 0.5f));
	Quad::Create(vertices, cuboidTopBackLeft, vec2(0.5f, 0.f), cuboidTopFrontLeft, vec2(0.75f, 0.f),
		cuboidBottomFrontLeft, vec2(0.75f, 0.25f), cuboidBottomBackLeft, vec2(0.5f, 0.25f));
	
	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.5f, 0.5f), cuboidTopBackLeft, vec2(0.5f, 0.25f),
		cuboidTopBackRight, vec2(0.75f, 0.25f), cuboidTopFrontRight, vec2(0.75f, 0.5f));					//Oberseite Quader

	//Kinn  Texturwerte aus Skizze entnommen
	vec3 kcuboidBottomFrontLeft(-0.09f, -0.095f, +0.11f);
	vec3 kcuboidBottomFrontRight(+0.09f, -0.095f, +0.11f);
	vec3 kcuboidBottomBackLeft(-0.09f, -0.095f, +0.025f);
	vec3 kcuboidBottomBackRight(+0.09f, -0.095f, +0.025f);

	vec3 kcuboidTopFrontLeft(-0.09f, -0.0f, +0.11f);
	vec3 kcuboidTopFrontRight(+0.09f, -0.0f, +0.11f);
	vec3 kcuboidTopBackLeft(-0.09f, -0.0f, +0.025f);
	vec3 kcuboidTopBackRight(+0.09f, -0.0f, +0.025f);

	Quad::Create(vertices, kcuboidBottomFrontLeft, vec2(0.25f, 0.875f), kcuboidBottomFrontRight, vec2(0.5f, 0.875f),
		kcuboidBottomBackRight, vec2(0.5f, 0.75f), kcuboidBottomBackLeft, vec2(0.25f, 0.75f));				//Bodenfläche Quader

	Quad::Create(vertices, kcuboidTopFrontLeft, vec2(0.f, 0.5f), kcuboidTopFrontRight, vec2(0.5f, 0.5f),
		kcuboidBottomFrontRight, vec2(0.5f, 0.75f), kcuboidBottomFrontLeft, vec2(0.f, 0.75f));				//Seitenflächen Quader
	Quad::Create(vertices, kcuboidTopFrontRight, vec2(0.75f, 0.5f), kcuboidTopBackRight, vec2(1.f, 0.5f),
		kcuboidBottomBackRight, vec2(1.f, 0.75f), kcuboidBottomFrontRight, vec2(0.75f, 0.75f));
	Quad::Create(vertices, kcuboidTopBackRight, vec2(0.25f, 0.875f), kcuboidTopBackLeft, vec2(0.5f, 0.875f),
		kcuboidBottomBackLeft, vec2(0.5f, 1.f), kcuboidBottomBackRight, vec2(0.25f, 1.f));
	Quad::Create(vertices, kcuboidTopBackLeft, vec2(0.5f, 0.5f), kcuboidTopFrontLeft, vec2(0.75f, 0.5f),
		kcuboidBottomFrontLeft, vec2(0.75f, 0.75f), kcuboidBottomBackLeft, vec2(0.5f, 0.75f));

	/*Quad::Create(vertices, kcuboidTopFrontLeft, vec2(0.f, 1.f), kcuboidTopBackLeft, vec2(0.f, 0.f),
		kcuboidTopBackRight, vec2(1.f, 0.f), kcuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader Gibt es nicht, da bündig mit Schädel*/


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("head");
}

Geometries::Robot::Head::Head( const Head& source )
	: instanceCounter( source.instanceCounter ), vertexBuffer( source.vertexBuffer ), mgdv( source.mgdv ), texture( source.texture )
{
	++*instanceCounter;
}

Geometries::Robot::Head::~Head()
{
	--*instanceCounter;
	if (*instanceCounter > 0U)
		return;

	ModernGDV::Log( "GEOM", "Destructing Head" );
	glDeleteBuffers( 1, &vertexBuffer );
	delete instanceCounter;
}

void Geometries::Robot::Head::Render()
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

	index = Quad::Draw(index); //Bodenfläche Quader

	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);


	Vertex::ResetLayout();
}

