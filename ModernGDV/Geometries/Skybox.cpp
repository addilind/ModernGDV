#include "Skybox.h"

#include "Primitives/Quad.h"

using ModernGDV::Vertex;
using Geometries::Primitives::Quad;
using glm::vec3;
using glm::vec2;


Geometries::Skybox::Skybox( ModernGDV::Driver* mgdv )
	: vertexBuffer( 0U ), mgdv( mgdv ), texture( nullptr )
{
	std::vector<Vertex> vertices;

	vec3 cubeBottomFrontLeft	( -1.f, -1.f, +1.f );
	vec3 cubeBottomFrontRight	( +1.f, -1.f, +1.f );
	vec3 cubeBottomBackLeft		( -1.f, -1.f, -1.f );
	vec3 cubeBottomBackRight	( +1.f, -1.f, -1.f );

	vec3 cubeTopFrontLeft		( -1.f, +1.f, +1.f );
	vec3 cubeTopFrontRight		( +1.f, +1.f, +1.f );
	vec3 cubeTopBackLeft		( -1.f, +1.f, -1.f );
	vec3 cubeTopBackRight		( +1.f, +1.f, -1.f );

	//Im Folgenden "Rückwärts", da der Würfel von innen betrachtet werden soll
	const float halfx = 1.5f / 4096.f;
	const float halfy = 1.5f / 2048.f;
	Quad::Create( vertices, cubeBottomFrontLeft, vec2( 0.25f + halfx, 1.f - halfy ), cubeBottomBackLeft, vec2( 0.25f + halfx, 0.5f + halfy ),
		cubeBottomBackRight, vec2( 0.5f - halfx, 0.5f + halfy ), cubeBottomFrontRight, vec2( 0.5f - halfx, 1.f - halfy ) );				//Bodenfläche Würfel

	Quad::Create( vertices, cubeTopBackLeft, vec2( 0.f + halfx, 0.f + halfy ), cubeTopBackRight, vec2( 0.25f - halfx, 0.f + halfy ),		//Seitenflächen Würfel
		cubeBottomBackRight, vec2( 0.25f - halfx, 0.5f - halfy ), cubeBottomBackLeft, vec2( 0.f + halfx, 0.5f - halfy ) );					//Hinten
	Quad::Create( vertices, cubeTopBackRight, vec2( 0.25f + halfx, 0.f + halfy ), cubeTopFrontRight, vec2( 0.5f - halfx, 0.f + halfy ),
		cubeBottomFrontRight, vec2( 0.5f - halfx, 0.5f - halfy ), cubeBottomBackRight, vec2( 0.25f + halfx, 0.5f - halfy ) );
	Quad::Create( vertices, cubeTopFrontRight, vec2( 0.5f + halfx, 0.f + halfy ), cubeTopFrontLeft, vec2( 0.75f - halfx, 0.f + halfy ),		//Vorne
		cubeBottomFrontLeft, vec2( 0.75f - halfx, 0.5f - halfy ), cubeBottomFrontRight, vec2( 0.5f + halfx, 0.5f - halfy ) );
	Quad::Create( vertices, cubeTopFrontLeft, vec2( 0.75f + halfx, 0.f + halfy ), cubeTopBackLeft, vec2( 1.f - halfx, 0.f + halfy ),
		cubeBottomBackLeft, vec2( 1.f - halfx, 0.5f - halfy ), cubeBottomFrontLeft, vec2( 0.75f + halfx, 0.5f - halfy ) );

	Quad::Create( vertices, cubeTopBackLeft, vec2( 0.f + halfx, 1.f - halfy ), cubeTopFrontLeft, vec2( 0.f + halfx, 0.5f +  halfy ),
		cubeTopFrontRight, vec2( 0.25f - halfx, 0.5f + halfy ), cubeTopBackRight, vec2( 0.25f - halfx, 1.f - halfy ) );					//Oberseite Würfel


	vertexBuffer = mgdv->CreateVertexBuffer( vertices );

	shaderID = mgdv->ShaderLib.GetShaderID( "default" );

	texture = mgdv->GetTexture( "skybox" );
}

Geometries::Skybox::~Skybox()
{

}

void Geometries::Skybox::Render()
{
	mgdv->ShaderLib.UseShader( shaderID );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex( texture );

	unsigned char index = 0U;
	index = Quad::Draw( index ); //Bodenfläche Würfel

	index = Quad::Draw( index ); //Seitenflächen Würfel
	index = Quad::Draw( index );
	index = Quad::Draw( index );
	index = Quad::Draw( index );

	index = Quad::Draw( index ); //Oberseite Würfel

	Vertex::ResetLayout();
}

