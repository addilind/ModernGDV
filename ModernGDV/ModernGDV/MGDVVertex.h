#ifndef MGDVVERTEX_H
#define MGDVVERTEX_H

namespace ModernGDV {
	#pragma pack(push, 1) //Sagt Visual Studio, den Vertex genau so, wie beschrieben im Speicher zu halten, damit wir ihn 1:1 auf die Grafikkarte kopieren k�nnen
	
	class MyVertex { //Muss zu den Inputs im Vertex-Shader passen
	public:
		float X; float Y; float Z;
		float R; float G; float B;
		MyVertex()
			: X( 0.0f ), Y( 0.0f ), Z( 0.0f ), R( 0.0f ), G( 0.0f ), B( 0.0f ) {} //Standardkonstruktor
		MyVertex( const float& x, const float& y, const float& z )
			: X( x ), Y( y ), Z( z ), R( 1.0f ), G( 1.0f ), B( 1.0f ) {} //Nur Position, Farbe wei�
		MyVertex( const float& x, const float& y, const float& z, const float& r, const float& g, const float& b )
			: X( x ), Y( y ), Z( z ), R( r ), G( g ), B( b ) {} //Position + Farbe
	};
	
	#pragma pack(pop) //Beendet pack
}
#endif