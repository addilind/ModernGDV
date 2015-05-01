#pragma once

namespace ModernGDV {
#pragma pack(push, 1) //Weist den Compiler an, den Vertex genau so, wie beschrieben, im Speicher zu halten, damit wir ihn 1:1 auf die Grafikkarte kopieren können
	struct Vertex { //Muss zu den Inputs im Vertex-Shader passen
	public:
		float X; float Y; float Z; //PositionsKoordinaten
		float NX; float NY; float NZ;//Normalenvektor
		float U; float V; //Texturkoordinaten
		Vertex()
			: X( 0.0f ), Y( 0.0f ), Z( 0.0f ), NX( 0.0f ), NY( 0.0f ), NZ( 0.0f ) {} //Standardkonstruktor
		Vertex( const float& x, const float& y, const float& z, const float& nx, const float& ny, const float& nz, const float& u, const float& v )
			: X( x ), Y( y ), Z( z ), NX( nx ), NY( ny ), NZ( nz ), U( u ), V( v )  {} //Position + Farbe
		static void SetLayout()
		{
			glEnableVertexAttribArray( 0 ); //Der VertexShader hat 3 Inputs, die aktiviert 
			glEnableVertexAttribArray( 1 );
			glEnableVertexAttribArray( 2 );
			glVertexAttribPointer(			//und beschrieben werden müssen
				0,                  // Attribut 0 ist in unserem Shader die Position
				3,                  // Positionen im MyVertex bestehen aus 3 Koordinaten
				GL_FLOAT,           // und sind als Floats gespeichert
				GL_FALSE,           // die float-werte sind nicht normalisiert
				sizeof( Vertex ), // zwischen zwei vertices liegen sizeof( Vertex ) = 8 * sizeof( Float ) = 8 * 4 = 32 byte
				nullptr            // Positionsinfos liegen an erster Stelle im Vertex
				);
			glVertexAttribPointer(
				1,                  // Attribut 1 ist in unserem Shader der Normalenvektor
				3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), // auch hier 3 nicht normalisierte floats 
				(void*)(3 * sizeof( float )) //vor den Farbinfos müssen die Positionsdaten übersprungen werden, die 3 * sizeof( float ) = 12 byte groß sind
				);
			glVertexAttribPointer(
				2,                  // Attribut 2 ist in unserem Shader die Texturkoordinaten
				2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), // hier 2 nicht normalisierte floats 
				(void*)(6 * sizeof( float )) //vor den Farbinfos müssen die Positions- und Normalendaten übersprungen werden, die 6 * sizeof( float ) byte groß sind
				);
		}

		static void ResetLayout()
		{
			glDisableVertexAttribArray( 0 );
			glDisableVertexAttribArray( 1 );
			glDisableVertexAttribArray( 2 );
		}
	};

#pragma pack(pop) //Beendet pack
}