#include "Shank.h"

#include "Primitives/Quad.h"

using ModernGDV::Vertex;
using glm::vec3;
using glm::vec2;


Shank::Shank(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	//Unterschenkel linke Seite
	vec3 lCubeBottomFrontLeft(-0.15f, -0.45f, +0.08f);
	vec3 lCubeBottomFrontRight(-0.075f, -0.45f, +0.08f);
	vec3 lCubeBottomBackLeft(-0.15f, -0.45f, -0.08f);
	vec3 lCubeBottomBackRight(-0.075f, -0.45f, -0.08f);

	vec3 lCubeTopFrontLeft(-0.15f, +0.05f, +0.075f);
	vec3 lCubeTopFrontRight(-0.075f, +0.05f, +0.075f);
	vec3 lCubeTopBackLeft(-0.15f, +0.05f, -0.075f);
	vec3 lCubeTopBackRight(-0.075f, +0.05f, -0.075f);

	//Bodenfläche Quader
	Quad::Create(vertices, lCubeBottomFrontLeft, vec2(0.f, 0.f), lCubeBottomFrontRight, vec2(1.f, 0.f),
		lCubeBottomBackRight, vec2(1.f, 1.f), lCubeBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, lCubeTopFrontLeft, vec2(0.f, 0.f), lCubeTopFrontRight, vec2(1.f, 0.f),
		lCubeBottomFrontRight, vec2(1.f, 1.f), lCubeBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, lCubeTopFrontRight, vec2(0.f, 0.f), lCubeTopBackRight, vec2(1.f, 0.f),
		lCubeBottomBackRight, vec2(1.f, 1.f), lCubeBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, lCubeTopBackRight, vec2(0.f, 0.f), lCubeTopBackLeft, vec2(1.f, 0.f),
		lCubeBottomBackLeft, vec2(1.f, 1.f), lCubeBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, lCubeTopBackLeft, vec2(0.f, 0.f), lCubeTopFrontLeft, vec2(1.f, 0.f),
		lCubeBottomFrontLeft, vec2(1.f, 1.f), lCubeBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, lCubeTopFrontLeft, vec2(0.f, 1.f), lCubeTopBackLeft, vec2(0.f, 0.f),
		lCubeTopBackRight, vec2(1.f, 0.f), lCubeTopFrontRight, vec2(1.f, 1.f));

	//Unterschenkel rechte Seite
	vec3 rCubeBottomFrontLeft(+0.075f, -0.45f, +0.08f);
	vec3 rCubeBottomFrontRight(+0.15f, -0.45f, +0.08f);
	vec3 rCubeBottomBackLeft(+0.075f, -0.45f, -0.08f);
	vec3 rCubeBottomBackRight(+0.15f, -0.45f, -0.08f);

	vec3 rCubeTopFrontLeft(+0.075f, +0.05f, +0.075f);
	vec3 rCubeTopFrontRight(+0.15f, +0.05f, +0.075f);
	vec3 rCubeTopBackLeft(+0.075f, +0.05f, -0.075f);
	vec3 rCubeTopBackRight(+0.15f, +0.05f, -0.075f);

	//Bodenfläche Quader
	Quad::Create(vertices, rCubeBottomFrontLeft, vec2(0.f, 0.f), rCubeBottomFrontRight, vec2(1.f, 0.f),
		rCubeBottomBackRight, vec2(1.f, 1.f), rCubeBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, rCubeTopFrontLeft, vec2(0.f, 0.f), rCubeTopFrontRight, vec2(1.f, 0.f),
		rCubeBottomFrontRight, vec2(1.f, 1.f), rCubeBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, rCubeTopFrontRight, vec2(0.f, 0.f), rCubeTopBackRight, vec2(1.f, 0.f),
		rCubeBottomBackRight, vec2(1.f, 1.f), rCubeBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, rCubeTopBackRight, vec2(0.f, 0.f), rCubeTopBackLeft, vec2(1.f, 0.f),
		rCubeBottomBackLeft, vec2(1.f, 1.f), rCubeBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, rCubeTopBackLeft, vec2(0.f, 0.f), rCubeTopFrontLeft, vec2(1.f, 0.f),
		rCubeBottomFrontLeft, vec2(1.f, 1.f), rCubeBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, rCubeTopFrontLeft, vec2(0.f, 1.f), rCubeTopBackLeft, vec2(0.f, 0.f),
		rCubeTopBackRight, vec2(1.f, 0.f), rCubeTopFrontRight, vec2(1.f, 1.f));

	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("test");
}

Shank::~Shank()
{

}

void Shank::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->UseTexture(texture);
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

