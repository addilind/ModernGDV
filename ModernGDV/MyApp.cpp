#include "MyApp.h"

using ModernGDV::ColorVertex;

MyApp::MyApp( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv )
	: mgdv(mgdv), shaderTransform(0U), vertexBuffer(0U)
{
	shaderTransform = glGetUniformLocation( mgdv->GetShaderProgram(), "transformation" );

	std::vector<ColorVertex> vertexBufferData;
	vertexBufferData.push_back( ColorVertex( -0.5f, -0.5f, 0.0f, 1, 1, 0 ) ); // 3xKoordinaten, 3xRGB-Farbcode
	vertexBufferData.push_back( ColorVertex( +0.5f, -0.5f, 0.0f, 1, 0, 0 ) );
	vertexBufferData.push_back( ColorVertex( -0.5f, +0.5f, 0.0f, 1, 0, 0 ) );
	vertexBufferData.push_back( ColorVertex( +0.5f, +0.5f, 0.0f, 0, 1, 1 ) );

	createVertexBuffer( vertexBufferData );

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

	//glm::mat4 transform = glm::mat4();

	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	
	ColorVertex::SetLayout();

	transform(glm::translate(glm::mat4(), glm::vec3(1, 0, 0)));
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	transform(glm::mat4());
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4  );

	ColorVertex::ResetLayout();
}

void MyApp::transform(const glm::mat4& tran)
{
	glm::mat4 transform = projectionMatrix * viewMatrix * tran;
	glUniformMatrix4fv(shaderTransform, 1, GL_FALSE, &transform[0][0]);
}

void MyApp::createVertexBuffer( const std::vector<ModernGDV::ColorVertex>& vertexBufferData )
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( ColorVertex ), &vertexBufferData[0], GL_STATIC_DRAW );
}