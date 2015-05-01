#ifndef MGDV_TEXTURES_TEXTURE_H
#define MGDV_TEXTURES_TEXTURE_H
#include <stdint.h>
#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

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
#endif