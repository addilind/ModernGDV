#ifndef MGDVVERTEX_H
#define MGDVVERTEX_H

namespace ModernGDV {
#pragma pack(push, 1) //Sagt Visual Studio, den Vertex genau so, wie beschrieben im Speicher zu halten, damit wir ihn 1:1 auf die Grafikkarte kopieren können

	struct ColorVertex { //Muss zu den Inputs im Vertex-Shader passen
	public:
		float X; float Y; float Z;
		float R; float G; float B;
		ColorVertex()
			: X( 0.0f ), Y( 0.0f ), Z( 0.0f ), R( 0.0f ), G( 0.0f ), B( 0.0f ) {} //Standardkonstruktor
		ColorVertex( const float& x, const float& y, const float& z )
			: X( x ), Y( y ), Z( z ), R( 1.0f ), G( 1.0f ), B( 1.0f ) {} //Nur Position, Farbe weiß
		ColorVertex( const float& x, const float& y, const float& z, const float& r, const float& g, const float& b )
			: X( x ), Y( y ), Z( z ), R( r ), G( g ), B( b ) {} //Position + Farbe
		static void SetLayout()
		{
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
				(void*)(3 * sizeof( float )) //vor den Farbinfos müssen die Positionsdaten übersprungen werden, die 3 * sizeof( float ) = 12 byte groß sind
				);
		}

		static void ResetLayout()
		{
			glDisableVertexAttribArray( 0 );
			glDisableVertexAttribArray( 1 );
		}
	};

#pragma pack(pop) //Beendet pack
}
#endif