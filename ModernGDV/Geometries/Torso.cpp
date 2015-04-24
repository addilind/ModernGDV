#include "Torso.h"

#include "Primitives/Triangle.h"
#include "Primitives/Quad.h"

using ModernGDV::Vertex;

Torso::Torso( ModernGDV::ModernGDV* mgdv )
	: mgdv(mgdv), vertexBuffer(0U), texture(0U)
{
	std::vector<Vertex> vertices;

	glm::vec3 pyramidTop			( +0.00f, +0.00f, +0.00f );
	glm::vec3 pyramidBaseFrontLeft	( -0.10f, +0.10f, +0.15f );
	glm::vec3 pyramidBaseFrontRight	( +0.10f, +0.10f, +0.15f );
	glm::vec3 pyramidBaseBackLeft	( -0.10f, +0.10f, -0.15f );
	glm::vec3 pyramidBaseBackRight	( +0.10f, +0.10f, -0.15f );


	Tri::Create( vertices, pyramidTop, glm::vec2( 0.5f, 1.f ), pyramidBaseFrontLeft, glm::vec2( 0.f, 0.f ), pyramidBaseFrontRight, glm::vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, glm::vec2( 0.5f, 1.f ), pyramidBaseFrontRight, glm::vec2( 0.f, 0.f ), pyramidBaseBackRight, glm::vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, glm::vec2( 0.5f, 1.f ), pyramidBaseBackRight, glm::vec2( 0.f, 0.f ), pyramidBaseBackLeft, glm::vec2( 1.f, 0.f ) );
	Tri::Create( vertices, pyramidTop, glm::vec2( 0.5f, 1.f ), pyramidBaseBackLeft, glm::vec2( 0.f, 0.f ), pyramidBaseFrontLeft, glm::vec2( 1.f, 0.f ) );


	createVertexBuffer(vertices);

	texture = mgdv->GetTexture( "test" );
}

Torso::~Torso()
{

}

void Torso::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	Vertex::SetLayout();

	mgdv->UseTexture( texture );
	Tri::Draw( 0U );
	Tri::Draw( 3U );
	Tri::Draw( 6U );
	Tri::Draw( 9U );

	Vertex::ResetLayout();
}

void Torso::createVertexBuffer(const std::vector<ModernGDV::Vertex>& vertexBufferData)
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof(Vertex), &vertexBufferData[0], GL_STATIC_DRAW);
}