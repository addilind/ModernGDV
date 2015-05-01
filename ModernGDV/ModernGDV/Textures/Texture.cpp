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
	auto byteRead = file.gcount();
	imageData.resize( byteRead ); //Überflüssig reservierten Speicher freigeben + Wert zur BufferOverflow-Überprüfung setzen

	file.close();

	GLuint format;
	switch (header.ddspf.FourCC)
	{
	case DDS_PIXELFORMAT::DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case DDS_PIXELFORMAT::DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case DDS_PIXELFORMAT::DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		throw std::runtime_error( "Texture declares unknown compression format!" );
	}

	// OpenGL-Textur erstellen
	glGenTextures( 1, &glID );
	glBindTexture( GL_TEXTURE_2D, glID );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, header.MipMapCount - 1 );

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;
	unsigned int width = header.Width;
	unsigned int height = header.Height;

	// Einzelne Bildversionen laden
	for (unsigned int level = 0; level < header.MipMapCount; ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		if (offset + size > imageData.size())
			throw std::runtime_error( "Texture contains too few data!" );
		glCompressedTexImage2D( GL_TEXTURE_2D, level, format, width, height, 0, size, &imageData[offset] );

		offset += size;
		width /= 2;
		height /= 2;

		if (width < 1) width = 1;
		if (height < 1) height = 1;
	}
}

ModernGDV::Textures::Texture::~Texture()
{
}

GLuint ModernGDV::Textures::Texture::GetID() const
{
	return glID;
}

void ModernGDV::Textures::Texture::Unload()
{
	glDeleteTextures( 1, &glID );
	glID = 0;
}