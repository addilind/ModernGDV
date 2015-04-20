#include "MyApp.h"

using ModernGDV::ColorVertex;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv )
: mgdv(mgdv), shaderTransform(0U), vertexBuffer(0U), testtorso()
{
	shaderTransform = glGetUniformLocation( mgdv->GetShaderProgram(), "transformation" );

	projectionMatrix = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f );
	viewMatrix = glm::lookAt( glm::vec3( 0, 1, 3 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );

	mgdv->SetApp( this );

	glDepthFunc( GL_LESS );
	glClearDepth( 1.0f );
}

MyApp::~MyApp()
{
}

void MyApp::Render ()
{
	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	viewMatrix = glm::lookAt(glm::vec3(3.f*glm::sin(glfwGetTime()), 1, 3.f*glm::cos(glfwGetTime())), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	transform(glm::mat4());

	//testtorso.Render();
	//testthigh.Render();
	testshank.Render();
}

void MyApp::transform(const glm::mat4& tran)
{
	glm::mat4 transform = projectionMatrix * viewMatrix * tran;
	glUniformMatrix4fv(shaderTransform, 1, GL_FALSE, &transform[0][0]);
}