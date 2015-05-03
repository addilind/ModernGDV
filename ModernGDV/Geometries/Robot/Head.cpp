#include "Head.h"

#include "../Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Head::Head(ModernGDV::Driver* mgdv)
	: vertexBuffer( 0U ), mgdv( mgdv ), texture( nullptr )
{
	std::vector<Vertex> vertices;
	//Kopf
	vec3 cuboidBottomFrontLeft(-0.12f, -0.0f, +0.1f);
	vec3 cuboidBottomFrontRight(+0.12f, -0.0f, +0.1f);
	vec3 cuboidBottomBackLeft(-0.12f, -0.0f, -0.1f);
	vec3 cuboidBottomBackRight(+0.12f, -0.0f, -0.1f);

	vec3 cuboidTopFrontLeft(-0.12f, +0.25f, +0.1f);
	vec3 cuboidTopFrontRight(+0.12f, +0.25f, +0.1f);
	vec3 cuboidTopBackLeft(-0.12f, +0.25f, -0.1f);
	vec3 cuboidTopBackRight(+0.12f, +0.25f, -0.1f);

	Quad::Create(vertices, cuboidBottomFrontLeft, vec2(0.f, 0.f), cuboidBottomFrontRight, vec2(1.f, 0.f),
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

	//Kinn
	vec3 kcuboidBottomFrontLeft(-0.09f, -0.095f, +0.1f);
	vec3 kcuboidBottomFrontRight(+0.09f, -0.095f, +0.1f);
	vec3 kcuboidBottomBackLeft(-0.09f, -0.095f, +0.025f);
	vec3 kcuboidBottomBackRight(+0.09f, -0.095f, +0.025f);

	vec3 kcuboidTopFrontLeft(-0.09f, -0.0f, +0.1f);
	vec3 kcuboidTopFrontRight(+0.09f, -0.0f, +0.1f);
	vec3 kcuboidTopBackLeft(-0.09f, -0.0f, +0.025f);
	vec3 kcuboidTopBackRight(+0.09f, -0.0f, +0.025f);

	Quad::Create(vertices, kcuboidBottomFrontLeft, vec2(0.f, 0.f), kcuboidBottomFrontRight, vec2(1.f, 0.f),
		kcuboidBottomBackRight, vec2(1.f, 1.f), kcuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfläche Quader

	Quad::Create(vertices, kcuboidTopFrontLeft, vec2(0.f, 0.f), kcuboidTopFrontRight, vec2(1.f, 0.f),
		kcuboidBottomFrontRight, vec2(1.f, 1.f), kcuboidBottomFrontLeft, vec2(0.f, 1.f));				//Seitenflächen Quader
	Quad::Create(vertices, kcuboidTopFrontRight, vec2(0.f, 0.f), kcuboidTopBackRight, vec2(1.f, 0.f),
		kcuboidBottomBackRight, vec2(1.f, 1.f), kcuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, kcuboidTopBackRight, vec2(0.f, 0.f), kcuboidTopBackLeft, vec2(1.f, 0.f),
		kcuboidBottomBackLeft, vec2(1.f, 1.f), kcuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, kcuboidTopBackLeft, vec2(0.f, 0.f), kcuboidTopFrontLeft, vec2(1.f, 0.f),
		kcuboidBottomFrontLeft, vec2(1.f, 1.f), kcuboidBottomBackLeft, vec2(0.f, 1.f));

	Quad::Create(vertices, kcuboidTopFrontLeft, vec2(0.f, 1.f), kcuboidTopBackLeft, vec2(0.f, 0.f),
		kcuboidTopBackRight, vec2(1.f, 0.f), kcuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("test");

	
}

Geometries::Robot::Head::~Head()
{

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

	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}

