#include "MyApp.h"

using ModernGDV::ColorVertex;

MyApp::MyApp( std::vector<std::string> commandline )
	: vertexBuffer(0U)
{
	std::vector<ColorVertex> vertexBufferData;
	vertexBufferData.push_back( ColorVertex( -0.5f, -0.5f, -0.5f, 1, 1, 0 ) ); // 3xKoordinaten, 3xRGB-Farbcode
	vertexBufferData.push_back( ColorVertex( +0.5f, -0.5f, -0.5f, 1, 0, 0 ) );
	vertexBufferData.push_back( ColorVertex( -0.5f, +0.5f, -0.5f, 1, 0, 0 ) );
	vertexBufferData.push_back( ColorVertex( +0.5f, +0.5f, -0.5f, 1, 0, 0 ) );

	createVertexBuffer( vertexBufferData );
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
		sizeof( ColorVertex ), // zwischen zwei vertices liegen sizeof( MyVertex ) = 6 * sizeof( Float ) = 6 * 4 = 24 byte
		(void*)0            // Positionsinfos liegen an erster Stelle im Vertex
		);
	glVertexAttribPointer(
		1,                  // Attribut 1 ist in unserem Shader die Farbe
		3, GL_FLOAT, GL_FALSE, sizeof( ColorVertex ), // auch hier 3 nicht normalisierte floats mit dem Abstand von 24 byte
		(void*)(3 * sizeof(float)) //vor den Farbinfos müssen die Positionsdaten übersprungen werden, die 3 * sizeof( float ) = 12 byte groß sind
		);

	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4  );

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
}

void MyApp::createVertexBuffer( const std::vector<ModernGDV::ColorVertex>& vertexBufferData )
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( ColorVertex ), &vertexBufferData[0], GL_STATIC_DRAW );
}