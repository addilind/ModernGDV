#include "MyApp.h"

MyApp::MyApp( std::vector<std::string> commandline )
	: vertexArray(0U), vertexBuffer(0U), vertexBufferData(nullptr)
{

	vertexBufferData = new GLfloat[] {
		-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
	};

	createVertexArray();
	createVertexBuffer();
}

MyApp::~MyApp()
{

}

void MyApp::Render () {
	glClear( GL_COLOR_BUFFER_BIT );

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

GLuint MyApp::createVertexArray()
{
	GLuint* VertexArrayID  = new GLuint[1];
	glGenVertexArrays( 1, VertexArrayID );
	glBindVertexArray( VertexArrayID[0] );
	//vertexArray = GLuint(VertexArrayID);
	//return VertexArrayID;
	return 0;
}

void MyApp::createVertexBuffer()
{
	GLuint id;
	glGenBuffers( 1, &id );
	vertexBuffer = id;
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertexBufferData ), vertexBufferData, GL_STATIC_DRAW );
}