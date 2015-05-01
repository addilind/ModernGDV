#include "Texture.h"
#include <fstream>
#include "DDSDefs.h"
#include <vector>

ModernGDV::Textures::Texture::Texture(const std::string& filename) : glID(0U)
{
	std::ifstream file( filename, std::ifstream::binary );
	if (!file)
		throw std::runtime_error( "Cannot open texture file!" );

	char filecode[4]; //Dateiheader überprüfen
	file.read( filecode, 4 );
	if (strncmp( filecode, "DDS ", 4 ) != 0)
		throw std::runtime_error( "Invalid texture file, must be a DDS file using DXT1/3/5 compression!" );

	DDS_HEADER header;
	file.read( reinterpret_cast<char*>(&header), 124 );


	if (header.MipMapCount < 1U)
		header.MipMapCount = 1U;

	/* Buffergröße errechnen: Falls die Textur vorberechnete MIPMAPs mitbringt, doppelt so viel Platz reservieren */
	unsigned int bufsize = header.MipMapCount > 1 ? header.PitchOrLinearSize * 2 : header.PitchOrLinearSize;
	std::vector<char> imageData( bufsize );
	file.read( &imageData[0], bufsize );
	auto read = file.gcount();

	file.close();

	unsigned int components = (header.ddspf.dwFourCC == DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		throw std::runtime_error( "Texture declares unknown compression format!" );
	}

	// OpenGL-Textur erstellen
	GLuint textureID;
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	// Einzelne Bildversionen laden
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D( GL_TEXTURE_2D, level, format, width, height, 0, size, &imageData[0] + offset );

		offset += size;
		width /= 2;
		height /= 2;

		if (width < 1) width = 1;
		if (height < 1) height = 1;
	}

	return textureID;
}

ModernGDV::Textures::Texture::~Texture()
{

}