#include "MyApp.h"

using ModernGDV::MyVertex;

MyApp::MyApp( std::vector<std::string> commandline )
	: vertexArray(0U), vertexBuffer(0U), vertexBufferData()
{
	vertexBufferData.push_back( MyVertex( -0.5f, -0.5f, -0.5f, 1, 1, 0 ) ); // 3xKoordinaten, 3xRGB-Farbcode
	vertexBufferData.push_back( MyVertex( +0.5f, -0.5f, -0.5f, 1, 0, 0 ) );
	vertexBufferData.push_back( MyVertex( -0.5f, +0.5f, -0.5f, 1, 0, 0 ) );
	vertexBufferData.push_back( MyVertex( +0.5f, +0.5f, -0.5f, 1, 0, 0 ) );

	createVertexArray();
	createVertexBuffer();
}

MyApp::~MyApp()
{
}

void MyApp::Render () {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glEnableVertexAttribArray( 0 ); //Der VertexShader hat 2 Inputs, die aktiviert 
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer(			//und beschrieben werden müssen
		0,                  // Attribut 0 ist in unserem Shader die Position
		3,                  // Positionen im MyVertex bestehen aus 3 Koordinaten
		GL_FLOAT,           // und sind als Floats gespeichert
		GL_FALSE,           // die float-werte sind nicht normalisiert
		sizeof( MyVertex ), // zwischen zwei vertices liegen sizeof( MyVertex ) = 6 * sizeof( Float ) = 6 * 4 = 24 byte
		(void*)0            // Positionsinfos liegen an erster Stelle im Vertex
		);
	glVertexAttribPointer(
		1,                  // Attribut 1 ist in unserem Shader die Farbe
		3, GL_FLOAT, GL_FALSE, sizeof( MyVertex ), // auch hier 3 nicht normalisierte floats mit dem Abstand von 24 byte
		(void*)(3 * sizeof(float)) //vor den Farbinfos müssen die Positionsdaten übersprungen werden, die 3 * sizeof( float ) = 12 byte groß sind
		);

	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4  );

	glDisableVertexAttribArray( 0 );
}

void MyApp::createVertexArray()
{	//Speichert im Hintergrund die Eigenschaften der VertexBuffer
	glGenVertexArrays( 1, &vertexArray );
	glBindVertexArray( vertexArray );
}

void MyApp::createVertexBuffer()
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( MyVertex ), &vertexBufferData[0], GL_STATIC_DRAW );
}