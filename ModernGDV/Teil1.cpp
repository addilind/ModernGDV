#include "Teil1.h"

using ModernGDV::ColorVertex;

Teil1::Teil1( std::vector<std::string> commandline, ModernGDV::ModernGDV* mgdv )
	: mgdv(mgdv), shaderTransform(0U), vertexBuffer(0U)
{

	std::vector<ColorVertex> vertexBufferData;
	vertexBufferData.push_back( ColorVertex( -0.5f, -0.5f, -0.5f, 1, 0, 0 ) ); // 3xKoordinaten, 3xRGB-Farbcode
	vertexBufferData.push_back( ColorVertex( +0.5f, -0.5f, -0.5f, 0, 0, 1 ) );
	vertexBufferData.push_back( ColorVertex( -0.5f, +0.5f, -0.5f, 0, 0, 1 ) );
	vertexBufferData.push_back( ColorVertex( +0.5f, +0.5f, -0.5f, 0, 0, 1 ) );

	vertexBufferData.push_back( ColorVertex( -0.5f, -0.5f, -1.0f, 0, 1, 0 ) );
	vertexBufferData.push_back( ColorVertex( +0.5f, -0.5f, -1.0f, 0, 1, 0 ) );
	vertexBufferData.push_back( ColorVertex( -0.5f, +0.5f, -1.0f, 0, 1, 0 ) );
	vertexBufferData.push_back( ColorVertex( +0.5f, +0.5f, -1.0f, 0, 1, 0 ) );

	createVertexBuffer( vertexBufferData );

	mgdv->SetApp( this );

	glDepthFunc( GL_GREATER );
	glClearDepth( 0.0f );
	glClearColor( 0.9f, 0.6f, 0.1f, 1.0f );
}

Teil1::~Teil1()
{
}

void Teil1::Render ()
{
	glEnable( GL_DEPTH_TEST ); //Z-Buffer aktivieren
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	
	ColorVertex::SetLayout();

	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
	glDrawArrays( GL_TRIANGLE_STRIP, 4, 4 ); //Zweites Rechteck

	ColorVertex::ResetLayout();
}

void Teil1::createVertexBuffer( const std::vector<ModernGDV::ColorVertex>& vertexBufferData )
{	//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertexBufferData.size() * sizeof( ColorVertex ), &vertexBufferData[0], GL_STATIC_DRAW );
}