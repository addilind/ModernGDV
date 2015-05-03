#include "ThighJoint.h"

#include "../Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::ThighJoint::ThighJoint(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	//Vorderquader
	vec3 cuboidBottomFrontLeft(-0.0375f, -0.05f, +0.125f);
	vec3 cuboidBottomFrontRight(+0.15f, -0.05f, +0.125f);
	vec3 cuboidBottomBackLeft(-0.0375f, -0.05f, +0.075f);
	vec3 cuboidBottomBackRight(+0.15f, -0.05f, +0.075f);

	vec3 cuboidTopFrontLeft(-0.0375f, +0.05f, +0.125f);
	vec3 cuboidTopFrontRight(+0.15f, +0.05f, +0.125f);
	vec3 cuboidTopBackLeft(-0.0375f, +0.05f, +0.075f);
	vec3 cuboidTopBackRight(+0.15f, +0.05f, +0.075f);

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

	//Hinterquader
	vec3 bcuboidBottomFrontLeft(-0.0375f, -0.05f, -0.075f);
	vec3 bcuboidBottomFrontRight(+0.15f, -0.05f, -0.075f);
	vec3 bcuboidBottomBackLeft(-0.0375f, -0.05f, -0.125f);
	vec3 bcuboidBottomBackRight(+0.15f, -0.05f, -0.125f);

	vec3 bcuboidTopFrontLeft(-0.0375f, +0.05f, -0.075f);
	vec3 bcuboidTopFrontRight(+0.15f, +0.05f, -0.075f);
	vec3 bcuboidTopBackLeft(-0.0375f, +0.05f, -0.125f);
	vec3 bcuboidTopBackRight(+0.15f, +0.05f, -0.125f);

	Quad::Create(vertices, bcuboidBottomFrontLeft, vec2(0.f, 0.f), bcuboidBottomFrontRight, vec2(1.f, 0.f),
		bcuboidBottomBackRight, vec2(1.f, 1.f), bcuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfläche Quader

	Quad::Create(vertices, bcuboidTopFrontLeft, vec2(0.f, 0.f), bcuboidTopFrontRight, vec2(1.f, 0.f),
		bcuboidBottomFrontRight, vec2(1.f, 1.f), bcuboidBottomFrontLeft, vec2(0.f, 1.f));				//Seitenflächen Quader
	Quad::Create(vertices, bcuboidTopFrontRight, vec2(0.f, 0.f), bcuboidTopBackRight, vec2(1.f, 0.f),
		bcuboidBottomBackRight, vec2(1.f, 1.f), bcuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, bcuboidTopBackRight, vec2(0.f, 0.f), bcuboidTopBackLeft, vec2(1.f, 0.f),
		bcuboidBottomBackLeft, vec2(1.f, 1.f), bcuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, bcuboidTopBackLeft, vec2(0.f, 0.f), bcuboidTopFrontLeft, vec2(1.f, 0.f),
		bcuboidBottomFrontLeft, vec2(1.f, 1.f), bcuboidBottomBackLeft, vec2(0.f, 1.f));

	Quad::Create(vertices, bcuboidTopFrontLeft, vec2(0.f, 1.f), bcuboidTopBackLeft, vec2(0.f, 0.f),
		bcuboidTopBackRight, vec2(1.f, 0.f), bcuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader

	//Mittelquader
	vec3 mcuboidBottomFrontLeft(+0.1f, -0.05f, +0.075f);
	vec3 mcuboidBottomFrontRight(+0.15f, -0.05f, +0.075f);
	vec3 mcuboidBottomBackLeft(+0.1f, -0.05f, -0.075f);
	vec3 mcuboidBottomBackRight(+0.15f, -0.05f, -0.075f);

	vec3 mcuboidTopFrontLeft(+0.1f, +0.05f, +0.075f);
	vec3 mcuboidTopFrontRight(+0.15f, +0.05f, +0.075f);
	vec3 mcuboidTopBackLeft(+0.1f, +0.05f, -0.075f);
	vec3 mcuboidTopBackRight(+0.15f, +0.05f, -0.075f);

	Quad::Create(vertices, mcuboidBottomFrontLeft, vec2(0.f, 0.f), mcuboidBottomFrontRight, vec2(1.f, 0.f),
		mcuboidBottomBackRight, vec2(1.f, 1.f), mcuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfläche Quader

	Quad::Create(vertices, mcuboidTopFrontLeft, vec2(0.f, 0.f),mcuboidTopFrontRight, vec2(1.f, 0.f),
		mcuboidBottomFrontRight, vec2(1.f, 1.f), mcuboidBottomFrontLeft, vec2(0.f, 1.f));				//Seitenflächen Quader
	Quad::Create(vertices, mcuboidTopFrontRight, vec2(0.f, 0.f), mcuboidTopBackRight, vec2(1.f, 0.f),
		mcuboidBottomBackRight, vec2(1.f, 1.f), mcuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, mcuboidTopBackRight, vec2(0.f, 0.f), mcuboidTopBackLeft, vec2(1.f, 0.f),
		mcuboidBottomBackLeft, vec2(1.f, 1.f), mcuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, mcuboidTopBackLeft, vec2(0.f, 0.f), mcuboidTopFrontLeft, vec2(1.f, 0.f),
		mcuboidBottomFrontLeft, vec2(1.f, 1.f), mcuboidBottomBackLeft, vec2(0.f, 1.f));

	Quad::Create(vertices, mcuboidTopFrontLeft, vec2(0.f, 1.f), mcuboidTopBackLeft, vec2(0.f, 0.f),
		mcuboidTopBackRight, vec2(1.f, 0.f), mcuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("test");


}

Geometries::Robot::ThighJoint::~ThighJoint()
{

}

void Geometries::Robot::ThighJoint::Render()
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

