#include "MyApp.h"
#include "Geometries/Primitives/Quad.h"

using ModernGDV::ColorVertex;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv )
	: mgdv(mgdv), robot(mgdv)
{
	mgdv->SetProjectionMatrix(glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f ));

	mgdv->SetApp( this );

	glDepthFunc( GL_LESS );
	glClearDepth( 1.0f );

	std::vector<ModernGDV::Vertex> lampvert;
	Quad::Create( lampvert, glm::vec3( -.1f, .1f, 0 ), glm::vec2( 0, 0 ), glm::vec3( .1f, .1f, 0 ), glm::vec2( 1, 0 ), glm::vec3( .1f, -.1f, 0 ), glm::vec2( 1, 1 ), glm::vec3( -.1f, -.1f, 0 ), glm::vec2( 0, 1 ) );
	Quad::Create( lampvert, glm::vec3( 0, 0.1f, -.1f ), glm::vec2( 0, 0 ), glm::vec3( 0, .1f, .1f ), glm::vec2( 1, 0 ), glm::vec3( 0, -.1f, .1f ), glm::vec2( 1, 1 ), glm::vec3( 0, -.1f, -.1f ), glm::vec2( 0, 1 ) );
	lampvb = mgdv->CreateVertexBuffer( lampvert );
	lamptex = mgdv->GetTexture( "lamp" );
}

MyApp::~MyApp()
{
}

void MyApp::Render ()
{
	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	mgdv->SetViewMatrix( glm::lookAt( glm::vec3( 2.f*glm::sin( glfwGetTime() / 30.f ), -0.3f, 2.f*glm::cos( glfwGetTime() / 30.f )), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) ) );
	mgdv->SetLightPos( glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ), 0.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) ) );

	mgdv->ResetTransform();

	robot.Render();

	glBindBuffer( GL_ARRAY_BUFFER, lampvb );
	ModernGDV::Vertex::SetLayout();
	mgdv->UseTexture( lamptex );
	mgdv->SetTransform( glm::translate( glm::mat4(), glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ), 0.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) ) ) );
	mgdv->SetLightPos( glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ) - 1.f, 0.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) + 1.f ) );
	Quad::Draw( 0U );
	Quad::Draw( 4U );
	ModernGDV::Vertex::ResetLayout();
}