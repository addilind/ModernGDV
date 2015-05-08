#include "Ski.h"

#include "../Primitives/Quad.h"
#include "../Primitives/Triangle.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using Geometries::Primitives::Tri;
using glm::vec3;
using glm::vec2;


Geometries::Robot::Ski::Ski(ModernGDV::Driver* mgdv)
: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	//Ski
	vec3 cuboidBottomFrontLeft(-0.075f, -0.03f, +1.10f);
	vec3 cuboidBottomFrontRight(+0.075f, -0.03f, +1.10f);
	vec3 cuboidBottomBackLeft(-0.075f, -0.03f, -1.10f);
	vec3 cuboidBottomBackRight(+0.075f, -0.03f, -1.10f);

	vec3 cuboidTopFrontLeft( -0.075f, +0.0f, +1.10f );
	vec3 cuboidTopFrontRight( +0.075f, +0.0f, +1.10f );
	vec3 cuboidTopBackLeft( -0.075f, +0.0f, -1.10f );
	vec3 cuboidTopBackRight( +0.075f, +0.0f, -1.10f );

	Quad::Create(vertices, cuboidBottomFrontLeft, vec2(0.f, 0.f), cuboidBottomFrontRight, vec2(1.f, 0.f),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));				//Bodenfläche Quader

	Quad::Create(vertices, cuboidTopFrontRight, vec2(0.f, 0.f), cuboidTopBackRight, vec2(1.f, 0.f),
		cuboidBottomBackRight, vec2(1.f, 1.f), cuboidBottomFrontRight, vec2(0.f, 1.f));				//Rechts
	Quad::Create(vertices, cuboidTopBackLeft, vec2(0.f, 0.f), cuboidTopFrontLeft, vec2(1.f, 0.f),
		cuboidBottomFrontLeft, vec2(1.f, 1.f), cuboidBottomBackLeft, vec2(0.f, 1.f));				//Links

	Quad::Create(vertices, cuboidTopFrontLeft, vec2(0.f, 1.f), cuboidTopBackLeft, vec2(0.f, 0.f),
		cuboidTopBackRight, vec2(1.f, 0.f), cuboidTopFrontRight, vec2(1.f, 1.f));					//Oberseite Quader

	//Ski Spitze vorne
	vec3 frontTipLeft(-0.035f, +0.02f, +1.25f);
	vec3 frontTipRight(+0.035f, +0.02f, +1.25f);

	Quad::Create( vertices, cuboidTopFrontLeft, vec2( 0.f, 0.f ), cuboidTopFrontRight, vec2( 1.f, 0.f ),  //Oberseite
		frontTipRight, vec2( 1.f, 1.f ), frontTipLeft, vec2( 0.f, 1.f ) );
	Tri::Create( vertices, frontTipRight, vec2( 0.f, 0.5f ), cuboidTopFrontRight, vec2( 1.f, 0.f ), cuboidBottomFrontRight, vec2( 1.f, 1.f ) ); //Rechte Seite
	Quad::Create( vertices, cuboidBottomFrontRight, vec2( 1.f, 0.f ), cuboidBottomFrontLeft, vec2(0.f, 0.f),
		frontTipLeft, vec2( 0.f, 1.f ), frontTipRight, vec2( 1.f, 1.f ) );
	Tri::Create( vertices, frontTipLeft, vec2( 0.f, 0.5f ), cuboidBottomFrontLeft, vec2( 1.f, 1.f ), cuboidTopFrontLeft, vec2( 1.f, 0.f ) ); //Linke Seite


	//Ski Spitze hinten
	vec3 backTipLeft(-0.035f, +0.02f, -1.25f);
	vec3 backTipRight( +0.035f, +0.02f, -1.25f );

	Quad::Create( vertices, cuboidTopBackRight, vec2( 0.f, 0.f ), cuboidTopBackLeft, vec2( 1.f, 0.f ),  //Oberseite
		backTipLeft, vec2( 1.f, 1.f ), backTipRight, vec2( 0.f, 1.f ) );
	Tri::Create( vertices, backTipLeft, vec2( 0.f, 0.5f ), cuboidTopBackLeft, vec2( 1.f, 0.f ), cuboidBottomBackLeft, vec2( 1.f, 1.f ) ); //Linke Seite
	Quad::Create( vertices, cuboidBottomBackLeft, vec2( 1.f, 0.f ), cuboidBottomBackRight, vec2( 0.f, 0.f ),
		backTipRight, vec2( 0.f, 1.f ), backTipLeft, vec2( 1.f, 1.f ) );
	Tri::Create( vertices, backTipRight, vec2( 0.f, 0.5f ), cuboidBottomBackRight, vec2( 1.f, 1.f ), cuboidTopBackRight, vec2( 1.f, 0.f ) ); //Rechte Seite

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

	index = Quad::Draw( index );//Oberseite Quader
	//Ski Spitze vorne
	index = Quad::Draw( index ); //Oberseite Quader
	index = Tri::Draw( index ); //Rechte Seite
	index = Quad::Draw( index ); //Unterseite
	index = Tri::Draw( index );//Linke Seite
	//Ski Spitze vorne
	index = Quad::Draw( index ); //Oberseite
	index = Tri::Draw( index ); //Linke Seite
	index = Quad::Draw( index ); //Unterseite
	index = Tri::Draw( index );//Rechte Seite


	Vertex::ResetLayout();
}

