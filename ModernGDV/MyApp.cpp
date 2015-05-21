#include "MyApp.h"
#include "Geometries/Primitives/Quad.h"

using Geometries::Primitives::Quad;
static const size_t ROBOTCOUNT = 12U;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::Driver* mgdv )
	: mgdv(mgdv), robots(ROBOTCOUNT, Geometries::Robot::Robot(mgdv)), camera(mgdv), terrain(mgdv, 320U), lowsegterrain(mgdv, 256),
	terrain_slope("snow", "hmap", 200.f, mgdv), //von -200 bis +200 ist immer Terrain sichtbar(4Segmente a 100), selbst wenn das letzte Segment gerade springt
	terrain_bgmountain("Mountain", "MountainHMap", 550.f, mgdv),
	terrain_glacier( "Snow", "MountainHMap", 550.f, mgdv )
{
	mgdv->SetProjectionOptions(45.0f, 600.f);

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
	

	double time = glfwGetTime();

	for (size_t i = 0U; i < ROBOTCOUNT; ++i){
		robots[i].SetTilt( glm::sin( time )*0.4f ); //Seitenneigung
		robots[i].SetOrientation( glm::cos( time + 0.5f )*-0.9f ); //Drehung y-Achse
		robots[i].SetPosition( glm::vec3( glm::sin( time ) * -5.0f, 2.37f - glm::abs( glm::sin( time ) )*0.25f + 1.3f * i, -4.f * i ) ); //Rechts Links

		robots[i].SetLeftArm( -0.6f, 0.5f - 0.5f*glm::sin( time ), -0.5f );
		robots[i].SetRightArm( -0.6f, 0.5f + 0.5f*glm::sin( time ), -0.5f );

		time += 1.5;
	}
}

void MyApp::Render(  )
{
	camera.Render();
	mgdv->ShaderLib.SetLight(glm::vec3(1.f*glm::sin(glfwGetTime() / 3.f), 5.3f, 1.f*glm::cos(glfwGetTime() / 3.f)), glm::vec3(0.0f, 0.f, 1.f), 1.f, 0.3f);

	drawSlope();
	drawSceneryTerrain();

	for (size_t i = 0U; i < ROBOTCOUNT; ++i)
		robots[i].Render();

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

void MyApp::drawSlope()
{
	static const size_t pieces = 5;
	glm::mat4 transform = 	glm::rotate( glm::mat4(), 0.1f * glm::pi<float>(), glm::vec3( 1, 0, 0 ) );
	for (size_t i = 0; i < pieces; ++i)
	{
		glm::mat4 pieceTransform =
			glm::scale(
				glm::translate(
					transform,
					glm::vec3( 0, 0.f, pieces * 50.f - glm::mod( static_cast<float>(glfwGetTime())*4.f + i*100.f, pieces * 100.f ) ) ),
				glm::vec3( 50.f, 5.f, 50.f ) );
		mgdv->ShaderLib.SetModel( pieceTransform );
		terrain.Render(terrain_slope);
	}
}

void MyApp::drawSceneryTerrain()
{
	mgdv->ShaderLib.SetModel( glm::scale(
		glm::translate(
		glm::mat4(),
		glm::vec3( 400, -250.f, 400 ) ),
		glm::vec3( 300.f, 300.f, 300.f ) ) );

	lowsegterrain.Render( terrain_bgmountain );

	mgdv->ShaderLib.SetModel( glm::scale(
		glm::rotate(
		glm::translate(
		glm::mat4(),
		glm::vec3( -350, -230.f, 400 ) ),
		-1.5f, glm::vec3( 0, 1, 0 ) ),
		glm::vec3( 200.f, 320.f, 200.f ) ) );

	lowsegterrain.Render( terrain_bgmountain );

	mgdv->ShaderLib.SetModel( glm::scale(
		glm::rotate(
		glm::translate(
		glm::mat4(),
		glm::vec3( 0, +20.f, -400 ) ),
		1.7f, glm::vec3( 0, 1, 0 ) ),
		glm::vec3( 200.f, 130.f, 200.f ) ) );

	lowsegterrain.Render( terrain_glacier );
}