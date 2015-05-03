#pragma once

#include <string>

#include "../OGLInc.h"

namespace ModernGDV
{
	namespace Textures
	{
		class Texture
		{
		private:
			GLuint glID;
			unsigned int width;
			unsigned int height;
			float texelwidth;
			float texelheight;
		public:
			Texture( const std::string& filename );
			~Texture();

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			float GetTexelWidth() const;
			float GetTexelHeight() const;
			GLuint GetID() const;
			void Unload();
		};
	}
}