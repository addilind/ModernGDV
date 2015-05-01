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
		public:
			Texture( const std::string& filename );
			~Texture();

			GLuint GetID() const;
			void Unload();
		};
	}
}