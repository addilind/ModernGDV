#include "Ski.h"

#include "../Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Ski::Ski(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	//Ski
	vec3 cuboidBottomFrontLeft(-0.075f, -0.01f, +0.70f);
	vec3 cuboidBottomFrontRight(+0.075f, -0.01f, +0.70f);
	vec3 cuboidBottomBackLeft(-0.075f, -0.01f, -0.70f);
	vec3 cuboidBottomBackRight(+0.075f, -0.01f, -0.70f);

	vec3 cuboidTopFrontLeft(-0.075f, +0.0f, +0.70f);
	vec3 cuboidTopFrontRight(+0.075f, +0.0f, +0.70f);
	vec3 cuboidTopBackLeft(-0.075f, +0.0f, -0.70f);
	vec3 cuboidTopBackRight(+0.075f, +0.0f, -0.70f);

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

	//Ski Spitze vorne
	vec3 fcuboidBottomFrontLeft(-0.035f, -0.005f, +0.80f);
	vec3 fcuboidBottomFrontRight(+0.035f, -0.005f, +0.80f);
	vec3 fcuboidBottomBackLeft(-0.075f, -0.01f, +0.70f);
	vec3 fcuboidBottomBackRight(+0.075f, -0.01f, +0.70f);

	vec3 fcuboidTopFrontLeft(-0.035f, -0.005f, +0.80f);
	vec3 fcuboidTopFrontRight(+0.035f, -0.005f, +0.80f);
	vec3 fcuboidTopBackLeft(-0.075f, +0.0f, +0.70f);
	vec3 fcuboidTopBackRight(+0.075f, +0.0f, +0.70f);

	Quad::Create(vertices, fcuboidBottomFrontLeft, vec2(0.f, 0.f), fcuboidBottomFrontRight, vec2(1.f, 0.f),
		fcuboidBottomBackRight, vec2(1.f, 1.f), fcuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfläche Quader

	Quad::Create(vertices, fcuboidTopFrontLeft, vec2(0.f, 0.f), fcuboidTopFrontRight, vec2(1.f, 0.f),
		fcuboidBottomFrontRight, vec2(1.f, 1.f), fcuboidBottomFrontLeft, vec2(0.f, 1.f));				//Seitenflächen Quader
	Quad::Create(vertices, fcuboidTopFrontRight, vec2(0.f, 0.f), fcuboidTopBackRight, vec2(1.f, 0.f),
		fcuboidBottomBackRight, vec2(1.f, 1.f), fcuboidBottomFrontRight, vec2(0.f, 1.f));
	Quad::Create(vertices, fcuboidTopBackRight, vec2(0.f, 0.f), fcuboidTopBackLeft, vec2(1.f, 0.f),
		fcuboidBottomBackLeft, vec2(1.f, 1.f), fcuboidBottomBackRight, vec2(0.f, 1.f));
	Quad::Create(vertices, fcuboidTopBackLeft, vec2(0.f, 0.f), fcuboidTopFrontLeft, vec2(1.f, 0.f),
		fcuboidBottomFrontLeft, vec2(1.f, 1.f), fcuboidBottomBackLeft, vec2(0.f, 1.f));

	Quad::Create(vertices, fcuboidTopFrontLeft, vec2(0.f, 1.f), fcuboidTopBackLeft, vec2(0.f, 0.f),
		fcuboidTopBackRight, vec2(1.f, 0.f), fcuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader

	//Ski Spitze hinten
	vec3 bcuboidBottomFrontLeft(-0.075f, -0.01f, -0.70f);
	vec3 bcuboidBottomFrontRight(+0.075f, -0.01f, -0.70f);
	vec3 bcuboidBottomBackLeft(-0.035f, -0.005f, - 0.80f);
	vec3 bcuboidBottomBackRight(+0.035f, -0.005f, -0.80f);

	vec3 bcuboidTopFrontLeft(-0.075f, +0.0f, -0.70f);
	vec3 bcuboidTopFrontRight(+0.075f, +0.0f, -0.70f);
	vec3 bcuboidTopBackLeft(-0.035f, -0.005f, -0.80f);
	vec3 bcuboidTopBackRight(+0.035f, -0.005f, -0.80f);

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


	vertexBuffer = mgdv->CreateVertexBuffer(vertices);

	texture = mgdv->GetTexture("test");


}

Geometries::Robot::Ski::~Ski()
{

}

void Geometries::Robot::Ski::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex(texture);
	unsigned char index = 0U;
	//Ski
	index = Quad::Draw(index); //Bodenfläche Quader

	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	//Ski Spitze vorne
	index = Quad::Draw(index); //Oberseite Quader

	index = Quad::Draw(index); //Bodenfläche Quader

	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	//Ski Spitze hinten
	index = Quad::Draw(index); //Oberseite Quader

	index = Quad::Draw(index); //Bodenfläche Quader

	index = Quad::Draw(index); //Seitenflächen Quader
	index = Quad::Draw(index);
	index = Quad::Draw(index);
	index = Quad::Draw(index);

	index = Quad::Draw(index); //Oberseite Quader

	Vertex::ResetLayout();
}

