#include "MyApp.h"
#include "Geometries/Primitives/Quad.h"

using Geometries::Primitives::Quad;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv )
	: mgdv(mgdv), robot(mgdv), robot2(mgdv), camera(mgdv), terrain(mgdv, 320U)
{
	mgdv->SetProjectionOptions(45.0f, 500.f);

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

void MyApp::Update(float deltaT)
{
	camera.Update( deltaT );
	robot.SetTilt( glm::sin( glfwGetTime() )*0.4f ); //Seitenneigung
	robot.SetOrientation( glm::cos( glfwGetTime() + 0.5f )*-0.9f ); //Drehung y-Achse
	robot.SetPosition( glm::vec3( glm::sin( glfwGetTime() ) * -5.0f, 2.4f - glm::abs( glm::sin( glfwGetTime() ) )*0.25, 0 ) ); //Rechts Links

	robot.SetLeftArm( 1.2f, -0.f, -0.9f );
	robot.SetRightArm(1.2f, -0.f, +0.9f);

	double timediff = 1.5;

	robot2.SetTilt( glm::sin( glfwGetTime() + timediff )*0.4f );
	robot2.SetOrientation( glm::cos( glfwGetTime() + timediff + 0.5f )*-0.9f );
	robot2.SetPosition( glm::vec3( glm::sin( glfwGetTime() + timediff ) * -5.0f,
		3.80f - glm::abs( glm::sin( glfwGetTime() + timediff ) )*0.25,
		-4.f ) );

	robot2.SetLeftArm( 1.2f, -0.f, -0.9f );
	robot2.SetRightArm(1.2f, -0.f, +0.9f);
}

void MyApp::Render(  )
{
	camera.Render();
	mgdv->ShaderLib.SetLight(glm::vec3(1.f*glm::sin(glfwGetTime() / 3.f), 5.3f, 1.f*glm::cos(glfwGetTime() / 3.f)), glm::vec3(0.0f, 0.f, 1.f), 1.f, 0.3f);

	mgdv->ShaderLib.SetModel(
		glm::scale(
			glm::translate(
				glm::rotate(
					glm::mat4(),
					-0.1f * -glm::pi<float>(),
					glm::vec3(1, 0, 0) ),
			glm::vec3( 0, 0.f, 150.f - glm::mod(static_cast<float>(glfwGetTime())*4.f, 285.f ) ) ),
		glm::vec3(50.f, 5.f, 50.f)
		));

	terrain.Render();

	mgdv->ShaderLib.SetModel(
		glm::scale(
		glm::translate(
		glm::rotate(
		glm::mat4(),
		-0.1f * -glm::pi<float>(),
		glm::vec3( 1, 0, 0 ) ),
		glm::vec3( 0, 0.f, 150.f - glm::mod( static_cast<float>(glfwGetTime())*4.f + 95.f, 285.f ) ) ),
		glm::vec3( 50.f, 5.f, 50.f )
		) );

	terrain.Render();

	mgdv->ShaderLib.SetModel(
		glm::scale(
		glm::translate(
		glm::rotate(
		glm::mat4(),
		-0.1f * -glm::pi<float>(),
		glm::vec3( 1, 0, 0 ) ),
		glm::vec3( 0, 0.f, 150.f - glm::mod( static_cast<float>(glfwGetTime())*4.f + 190.f, 285.f ) ) ),
		glm::vec3( 50.f, 5.f, 50.f )
		) );

	terrain.Render();
	
	robot.Render();
	robot2.Render();

	glDisable( GL_CULL_FACE ); //Lampe ist nicht immer korrekt
	glBindBuffer( GL_ARRAY_BUFFER, lampvb );
	ModernGDV::Vertex::SetLayout();
	mgdv->ShaderLib.SetDiffuseTex( lamptex );
	mgdv->ShaderLib.SetModel( glm::translate( glm::mat4(), glm::vec3( 1.f*glm::sin( glfwGetTime() / 3.f ), 5.3f, 1.f*glm::cos( glfwGetTime() / 3.f ) ) ) );
	mgdv->ShaderLib.SetLight( glm::vec3( 0 ), glm::vec3( 1, 1, 1 ), 0.f, 1.f );//Dont light
	mgdv->ShaderLib.SetSpecularProperties( glm::vec3( 0 ), 1.f );
	Quad::Draw( 0U );
	Quad::Draw( 4U );
	ModernGDV::Vertex::ResetLayout();
}