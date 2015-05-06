#pragma once

#include "../OGLInc.h"
#include <vector>
#include <map>

namespace ModernGDV{namespace Textures{
	class Texture;
}}

namespace ModernGDV
{
	namespace Shaders
	{
		class ShaderSet;

		class ShaderLibrary
		{
		private:
			size_t activeShader;
			std::vector<ShaderSet> shaders;
			std::map<const std::string, size_t> shaderNames;

			glm::mat4 model;
			glm::mat3 normal;
			glm::mat4 projection;
			glm::mat4 view;

			glm::vec3 lightPos;
			glm::vec3 lightColor;
			float lightPower;
			float ambient;
			glm::vec3 specularColor;
			float specularExponent;

			glm::vec3 sunDirection;
			glm::vec3 sunColor;

			GLuint diffuseTexure;
			GLuint heightTexure;
			float terrainSegSize;

		public:
			friend ShaderSet;

			ShaderLibrary();
			~ShaderLibrary();

			void UseShader( size_t shaderID );
			void ReapplyShader(  );
			size_t GetShaderID( const std::string& name );

			void SetModel( const glm::mat4& model );
			void SetView( const glm::mat4& view );
			void SetProj( const glm::mat4& proj );
			void SetDiffuseTex( const Textures::Texture* texture );
			void SetHeightTex( const Textures::Texture* texture );
			void SetLight( const glm::vec3& position, const glm::vec3& color, const float& power, const float& ambient );
			void SetSun( const glm::vec3& dir, const glm::vec3& color );
			void SetSpecularProperties( const glm::vec3& specularColor, const float& specularExp = 5.0f );
			void SetTerrainSegmentSize( const float& segmentSize );

		private:
		};
	}
}