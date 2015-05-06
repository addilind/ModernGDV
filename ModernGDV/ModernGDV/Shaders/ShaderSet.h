#pragma once

#include "../OGLInc.h"
#include "ShaderLibrary.h"

namespace ModernGDV
{
	namespace Shaders
	{
		class ShaderSet
		{
		private:
			size_t* instanceCounter;

			std::string name;
			ShaderLibrary* library;

			GLuint vertexShader;
			GLuint fragmentShader;
			GLuint shaderProgram;
			GLuint vertexArray;

			GLuint shaderUniformModel;
			GLuint shaderUniformNormal;
			GLuint shaderUniformView;
			GLuint shaderUniformProj;
			GLuint shaderUniformLightPos;
			GLuint shaderUniformLightColor;
			GLuint shaderUniformLightPower;
			GLuint shaderUniformAmbientLight;
			GLuint shaderUniformSpecularColor;
			GLuint shaderUniformSpecularExponent;
			GLuint shaderUniformDiffuseTextureSampler;
			GLuint shaderUniformSunDirection;
			GLuint shaderUniformSunColor;

			GLuint shaderUniformHeightTextureSampler; //Terrain spezifisch
			GLuint shaderUniformSegmentSize;    //Terrain spezifisch
		public:
			ShaderSet( ShaderLibrary* library, const std::string& name );
			ShaderSet( const ShaderSet& source );
			~ShaderSet();

			void Bind();
			void Unbind();

			void UploadModel();
			void UploadView();
			void UploadProj();
			void UploadTextures();
			void UploadLight();
			void UploadSun();
			void UploadSpecularProperties();
			void UploadTerrainProperties();

			std::string GetName() const;
		private:
			std::vector<char> readShaderFile( const char* filename );
			void createShaders();
			void createShaderProgram();
			void createVertexArray();
			void loadActiveUniforms();
		};
	}
}