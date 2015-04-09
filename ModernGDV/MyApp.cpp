#include "MyApp.h"

MyApp::MyApp( std::vector<std::string> commandline )
	: vertexArray(0U), vertexBuffer(0U), vertexBufferData(nullptr)
{
	vertexBufferData = new GLfloat[9] { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	createVertexArray();
	createVertexBuffer();
}

MyApp::~MyApp()
{
	delete[] vertexBufferData;
}

void MyApp::Render () {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glDisableVertexAttribArray( 0 );
}

void MyApp::createVertexArray()
{
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );
}

void MyApp::createVertexBuffer()
{
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( GLfloat ), vertexBufferData, GL_STATIC_DRAW );
}