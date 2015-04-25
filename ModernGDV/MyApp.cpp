#include "MyApp.h"
#include "Geometries/Primitives/Quad.h"

using ModernGDV::ColorVertex;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv )
	: mgdv(mgdv), robot(mgdv), sky(mgdv)
{
	mgdv->SetProjectionMatrix(glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f ));

	mgdv->SetApp( this );

	glDepthFunc( GL_LESS );
	glClearDepth( 1.0f );
	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CW ); //Wir zeichnen immer im Uhrzeigersinn
	glCullFace( GL_BACK ); //Nur Vorderseiten zeichnen

	glClearColor( 1.0f, 0.5f, 1.0f, 1.0f );

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
	glEnable( GL_CULL_FACE );

	mgdv->SetViewMatrix( glm::lookAt( glm::vec3( -2.f*glm::sin( glfwGetTime() / 5.f ), 1.3f, 2.f*glm::cos( glfwGetTime() / 5.f ) ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) ) );
	mgdv->SetLightPos( glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ), 0.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) ) );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glDisable( GL_DEPTH_TEST ); //Z-Buffer deaktivieren, um Sky-Cube zu zeichnen

	mgdv->SetTransform( glm::translate( glm::mat4(), glm::vec3( -2.f*glm::sin( glfwGetTime() / 5.f ), 1.3f, 2.f*glm::cos( glfwGetTime() / 5.f ) ) ) );
	sky.Render();

	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren


	mgdv->ResetTransform();
	robot.Render();

	glDisable( GL_CULL_FACE ); //Lampe ist nicht immer korrekt
	glBindBuffer( GL_ARRAY_BUFFER, lampvb );
	ModernGDV::Vertex::SetLayout();
	mgdv->UseTexture( lamptex );
	mgdv->SetTransform( glm::translate( glm::mat4(), glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ), 0.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) ) ) );
	mgdv->SetLightPos( glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ) - 1.f, 0.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) + 1.f ) );
	Quad::Draw( 0U );
	Quad::Draw( 4U );
	ModernGDV::Vertex::ResetLayout();
}