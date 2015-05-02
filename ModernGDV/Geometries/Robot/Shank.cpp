#include "Shank.h"

#include "../Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Shank::Shank(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	//Unterschenkel linke Seite
	vec3 lCuboidBottomFrontLeft(-0.15f, -0.45f, +0.08f);
	vec3 lCuboidBottomFrontRight(-0.075f, -0.45f, +0.08f);
	vec3 lCuboidBottomBackLeft(-0.15f, -0.45f, -0.08f);
	vec3 lCuboidBottomBackRight(-0.075f, -0.45f, -0.08f);

	vec3 lCuboidTopFrontLeft(-0.15f, +0.05f, +0.08f);
	vec3 lCuboidTopFrontRight(-0.075f, +0.05f, +0.08f);
	vec3 lCuboidTopBackLeft(-0.15f, +0.05f, -0.08f);
	vec3 lCuboidTopBackRight(-0.075f, +0.05f, -0.08f);

	//Bodenfläche Quader
	Quad::Create(vertices, lCuboidBottomFrontLeft, vec2(0.f, 0.f), lCuboidBottomFrontRight, vec2(1.f, 0.f),
		lCuboidBottomBackRight, vec2(1.f, 1.f), lCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, lCuboidTopFrontLeft, vec2(0.f, 0.f), lCuboidTopFrontRight, vec2(1.f, 0.f),
		lCuboidBottomFrontRight, vec2(1.f, 1.f), lCuboidBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, lCuboidTopFrontRight, vec2(0.f, 0.f), lCuboidTopBackRight, vec2(1.f, 0.f),
		lCuboidBottomBackRight, vec2(1.f, 1.f), lCuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, lCuboidTopBackRight, vec2(0.f, 0.f), lCuboidTopBackLeft, vec2(1.f, 0.f),
		lCuboidBottomBackLeft, vec2(1.f, 1.f), lCuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, lCuboidTopBackLeft, vec2(0.f, 0.f), lCuboidTopFrontLeft, vec2(1.f, 0.f),
		lCuboidBottomFrontLeft, vec2(1.f, 1.f), lCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, lCuboidTopFrontLeft, vec2(0.f, 1.f), lCuboidTopBackLeft, vec2(0.f, 0.f),
		lCuboidTopBackRight, vec2(1.f, 0.f), lCuboidTopFrontRight, vec2(1.f, 1.f));

	//Unterschenkel rechte Seite
	vec3 rCuboidBottomFrontLeft(+0.075f, -0.45f, +0.08f);
	vec3 rCuboidBottomFrontRight(+0.15f, -0.45f, +0.08f);
	vec3 rCuboidBottomBackLeft(+0.075f, -0.45f, -0.08f);
	vec3 rCuboidBottomBackRight(+0.15f, -0.45f, -0.08f);

	vec3 rCuboidTopFrontLeft(+0.075f, +0.05f, +0.08f);
	vec3 rCuboidTopFrontRight(+0.15f, +0.05f, +0.08f);
	vec3 rCuboidTopBackLeft(+0.075f, +0.05f, -0.08f);
	vec3 rCuboidTopBackRight(+0.15f, +0.05f, -0.08f);

	//Bodenfläche Quader
	Quad::Create(vertices, rCuboidBottomFrontLeft, vec2(0.f, 0.f), rCuboidBottomFrontRight, vec2(1.f, 0.f),
		rCuboidBottomBackRight, vec2(1.f, 1.f), rCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Seitenflächen Quader
	Quad::Create(vertices, rCuboidTopFrontLeft, vec2(0.f, 0.f), rCuboidTopFrontRight, vec2(1.f, 0.f),
		rCuboidBottomFrontRight, vec2(1.f, 1.f), rCuboidBottomFrontLeft, vec2(0.f, 1.f));
	Quad::Create(vertices, rCuboidTopFrontRight, vec2(0.f, 0.f), rCuboidTopBackRight, vec2(1.f, 0.f),
		rCuboidBottomBackRight, vec2(1.f, 1.f), rCuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, rCuboidTopBackRight, vec2(0.f, 0.f), rCuboidTopBackLeft, vec2(1.f, 0.f),
		rCuboidBottomBackLeft, vec2(1.f, 1.f), rCuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, rCuboidTopBackLeft, vec2(0.f, 0.f), rCuboidTopFrontLeft, vec2(1.f, 0.f),
		rCuboidBottomFrontLeft, vec2(1.f, 1.f), rCuboidBottomBackLeft, vec2(0.f, 1.f));
	//Oberseite Quader
	Quad::Create(vertices, rCuboidTopFrontLeft, vec2(0.f, 1.f), rCuboidTopBackLeft, vec2(0.f, 0.f),
		rCuboidTopBackRight, vec2(1.f, 0.f), rCuboidTopFrontRight, vec2(1.f, 1.f));

	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("test");
}

Geometries::Robot::Shank::~Shank()
{

}

void Geometries::Robot::Shank::Render()
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

