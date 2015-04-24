#include "Thigh.h"

#include "Primitives/Quad.h"

using ModernGDV::Vertex;
using glm::vec3;
using glm::vec2;


Thigh::Thigh(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	vec3 CubeBottomFrontLeft(-0.075f, -0.50f, +0.075f);
	vec3 CubeBottomFrontRight(+0.075f, -0.50f, +0.075f);
	vec3 CubeBottomBackLeft(-0.075f, -0.50f, -0.075f);
	vec3 CubeBottomBackRight(+0.075f, -0.50f, -0.075f);

	vec3 CubeTopFrontLeft(-0.075f, +0.05f, +0.075f);
	vec3 CubeTopFrontRight(+0.075f, +0.05f, +0.075f);
	vec3 CubeTopBackLeft(-0.075f, +0.05f, -0.075f);
	vec3 CubeTopBackRight(+0.075f, +0.05f, -0.075f);

	//Bodenfläche Quader
	Quad::Create(vertices, CubeBottomFrontLeft, vec2(0.f, 0.f), CubeBottomFrontRight, vec2(1.f, 0.f),
		CubeBottomBackRight, vec2(1.f, 1.f), CubeBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, CubeTopFrontLeft, vec2(0.f, 0.f), CubeTopFrontRight, vec2(1.f, 0.f),
		CubeBottomFrontRight, vec2(1.f, 1.f), CubeBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, CubeTopFrontRight, vec2(0.f, 0.f), CubeTopBackRight, vec2(1.f, 0.f),
		CubeBottomBackRight, vec2(1.f, 1.f), CubeBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, CubeTopBackRight, vec2(0.f, 0.f), CubeTopBackLeft, vec2(1.f, 0.f),
		CubeBottomBackLeft, vec2(1.f, 1.f), CubeBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, CubeTopBackLeft, vec2(0.f, 0.f), CubeTopFrontLeft, vec2(1.f, 0.f),
		CubeBottomFrontLeft, vec2(1.f, 1.f), CubeBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, CubeTopFrontLeft, vec2(0.f, 1.f), CubeTopBackLeft, vec2(0.f, 0.f),
		CubeTopBackRight, vec2(1.f, 0.f), CubeTopFrontRight, vec2(1.f, 1.f));


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("test");

	
}

Thigh::~Thigh()
{

}

void Thigh::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->UseTexture(texture);
	unsigned char index = 0U;

	index = Quad::Draw(index); //Bodenfläche Quader

	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}

