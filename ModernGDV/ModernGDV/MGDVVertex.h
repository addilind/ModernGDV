#pragma once

namespace ModernGDV {
#pragma pack(push, 1) //Weist den Compiler an, den Vertex genau so, wie beschrieben, im Speicher zu halten, damit wir ihn 1:1 auf die Grafikkarte kopieren k�nnen
	struct Vertex { //Muss zu den Inputs im Vertex-Shader passen
	public:
		float X; float Y; float Z; //PositionsKoordinaten
		float NX; float NY; float NZ;//Normalenvektor
		float U; float V; //Texturkoordinaten
		Vertex()
			: X( 0.0f ), Y( 0.0f ), Z( 0.0f ), NX( 0.0f ), NY( 0.0f ), NZ( 0.0f ), U(0.0f), V(0.0f) {} //Standardkonstruktor
		Vertex( const float& x, const float& y, const float& z, const float& nx, const float& ny, const float& nz, const float& u, const float& v )
			: X( x ), Y( y ), Z( z ), NX( nx ), NY( ny ), NZ( nz ), U( u ), V( v )  {} //Position, Normale, UV-Koordinaten
		static void SetLayout()
		{
			glEnableVertexAttribArray( 0 ); //Der VertexShader hat 3 Inputs, die aktiviert 
			glEnableVertexAttribArray( 1 );
			glEnableVertexAttribArray( 2 );
			glVertexAttribPointer(			//und beschrieben werden m�ssen
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
				(void*)(3 * sizeof( float )) //vor den Farbinfos m�ssen die Positionsdaten �bersprungen werden, die 3 * sizeof( float ) = 12 byte gro� sind
				);
			glVertexAttribPointer(
				2,                  // Attribut 2 ist in unserem Shader die Texturkoordinaten
				2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), // hier 2 nicht normalisierte floats 
				(void*)(6 * sizeof( float )) //vor den Farbinfos m�ssen die Positions- und Normalendaten �bersprungen werden, die 6 * sizeof( float ) byte gro� sind
				);
		}

		static void ResetLayout()
		{
			glDisableVertexAttribArray( 0 );
			glDisableVertexAttribArray( 1 );
			glDisableVertexAttribArray( 2 );
		}
	};
	struct UVVertex { //Muss zu den Inputs im Vertex-Shader passen
	public:
		float X; float Y; float Z; //PositionsKoordinaten
		float U; float V; //Texturkoordinaten
		UVVertex()
			: X( 0.0f ), Y( 0.0f ), Z( 0.0f ), U( 0.0f ), V( 0.0f ) {} //Standardkonstruktor
		UVVertex( const float& x, const float& y, const float& z, const float& u, const float& v )
			: X( x ), Y( y ), Z( z ), U( u ), V( v )  {} //Position + UV-Koordinaten
		static void SetLayout()
		{
			glEnableVertexAttribArray( 0 ); //Der VertexShader hat 2 Inputs, die aktiviert 
			glEnableVertexAttribArray( 1 );
			glVertexAttribPointer(			//und beschrieben werden m�ssen
				0,                  // Attribut 0 ist in unserem Shader die Position
				3,                  // Positionen im MyVertex bestehen aus 3 Koordinaten
				GL_FLOAT,           // und sind als Floats gespeichert
				GL_FALSE,           // die float-werte sind nicht normalisiert
				sizeof( UVVertex ), // zwischen zwei vertices liegen sizeof( UVVertex ) = 5 * sizeof( Float ) = 5 * 4 = 20 byte
				nullptr            // Positionsinfos liegen an erster Stelle im Vertex
				);
			glVertexAttribPointer(
				1,                  // Attribut 1 ist in unserem Shader die Texturkoordinaten
				2, GL_FLOAT, GL_FALSE, sizeof( UVVertex ), // hier 2 nicht normalisierte floats 
				(void*)(3 * sizeof( float )) //vor den Farbinfos m�ssen die Positionsdaten �bersprungen werden, die 3 * sizeof( float ) byte gro� sind
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