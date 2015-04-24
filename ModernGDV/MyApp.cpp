#include "MyApp.h"

using ModernGDV::ColorVertex;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv )
	: mgdv(mgdv), shaderTransform(0U), vertexBuffer(0U), robot(mgdv)
{
	shaderTransform = glGetUniformLocation( mgdv->GetShaderProgram(), "transformation" );

	mgdv->SetProjectionMatrix(glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f ));

	mgdv->SetApp( this );

	glDepthFunc( GL_LESS );
	glClearDepth( 1.0f );

	mgdv->SetLightPos( glm::vec3( 0, 0, 1 ) );
}

MyApp::~MyApp()
{
}

void MyApp::Render ()
{
	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	mgdv->SetViewMatrix(glm::lookAt(glm::vec3(1.f*glm::sin(glfwGetTime()/4.f), 0.3f, 1.f*glm::cos(glfwGetTime()/4.f)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

	mgdv->ResetTransform();

	robot.Render();


}