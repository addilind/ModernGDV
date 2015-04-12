#include "Teil3.h"
#include <stack>

using ModernGDV::ColorVertex;

Teil3::Teil3( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv )
	: mgdv(mgdv), shaderTransform(0U), vertexBuffer(0U)
{
	shaderTransform = glGetUniformLocation( mgdv->GetShaderProgram(), "transformation" );

	std::vector<ColorVertex> vertexBufferData;
	float size = 0.2f;
	vertexBufferData.push_back( ColorVertex( -1.0f * size, -1.0f * size, -1.0f * size, 0, 0, 0 ) ); //Schwarz	0
	vertexBufferData.push_back( ColorVertex( -1.0f * size, -1.0f * size, +1.0f * size, 1, 0, 0 ) ); //Rot
	vertexBufferData.push_back( ColorVertex( -1.0f * size, +1.0f * size, -1.0f * size, 0, 0, 1 ) ); //Blau		2
	vertexBufferData.push_back( ColorVertex( -1.0f * size, +1.0f * size, +1.0f * size, 1, 0, 1 ) ); //Magenta
	vertexBufferData.push_back( ColorVertex( +1.0f * size, -1.0f * size, -1.0f * size, 0, 1, 0 ) ); //Grün		4
	vertexBufferData.push_back( ColorVertex( +1.0f * size, -1.0f * size, +1.0f * size, 1, 1, 0 ) ); //Gelb
	vertexBufferData.push_back( ColorVertex( +1.0f * size, +1.0f * size, -1.0f * size, 0, 1, 1 ) ); //Cyan		6
	vertexBufferData.push_back( ColorVertex( +1.0f * size, +1.0f * size, +1.0f * size, 1, 1, 1 ) ); //Weiß

	createVertexBuffer( vertexBufferData );

	mgdv->SetApp( this );

	glDepthFunc( GL_LESS );
	glClearDepth( 1.0f );
	glClearColor( 0.9f, 0.6f, 0.1f, 1.0f );

}

Teil3::~Teil3()
{
}

void Teil3::Render ()
{
	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 5.0f);
	viewMatrix = glm::lookAt( glm::vec3(0, 0, 3 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );
	
	if (glfwGetKey( mgdv->GetWindow(), GLFW_KEY_2 ))
		viewMatrix = glm::lookAt( glm::vec3( 3 * glm::sin( glfwGetTime() / 2. ), 1, 3 * glm::cos( glfwGetTime() / 2. ) ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );

	float pi = glm::pi<float>();
	
	std::stack<glm::mat4> transstack;
	glm::mat4 trans = glm::mat4();
	trans = glm::rotate(trans, static_cast<float>(glfwGetTime()) / 2.f, glm::vec3(0, 0, 1));
		
	transstack.push(trans); //Gruppe beginnen

	trans = glm::translate(trans, glm::vec3(0.5f, 0, 0));
	trans = glm::scale(trans, glm::vec3(2.5f, 1.f, 1.f));
	transform(trans);//transformation zur Grafikkarte schicken
	drawCube();

	trans = transstack.top(); //Neuen Ast in Gruppe
	trans = glm::translate(trans, glm::vec3(1.6f, 0, 0));
	trans = glm::scale(trans, glm::vec3(3.0f, 0.5f, 0.5f));

	transform(trans);//transformation zur Grafikkarte schicken
	drawCube();
	
	transstack.pop(); //Gruppe beenden
	
}

void Teil3::drawCube()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	ColorVertex::SetLayout();

	unsigned char side1[8] = { 7, 5, 1, 3, 2, 6, 4, 5 };
	unsigned char side2[8] = { 0, 5, 4, 6, 2, 3, 1, 5 };
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_BYTE, side1);
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_BYTE, side2);

	ColorVertex::ResetLayout();
}

void Teil3::transform(const glm::mat4& tran)
{
	glm::mat4 transform = projectionMatrix * viewMatrix * tran;
	glUniformMatrix4fv(shaderTransform, 1, GL_FALSE, &transform[0][0]);
}

void Teil3::createVertexBuffer( const std::vector<ModernGDV::ColorVertex>& vertexBufferData )
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( ColorVertex ), &vertexBufferData[0], GL_STATIC_DRAW );
}