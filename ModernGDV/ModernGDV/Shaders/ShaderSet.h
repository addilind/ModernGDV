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
			GLuint shaderUniformDiffuseTextureSampler;
			GLuint shaderUniformLightColor;
			GLuint shaderUniformLightPower;
			GLuint shaderUniformAmbientLight;
			GLuint shaderUniformSpecularColor;
			GLuint shaderUniformSpecularExponent;
		public:
			ShaderSet( ShaderLibrary* library, const std::string& name );
			~ShaderSet();

			void Bind();
			void Unbind();

			void UploadModel();
			void UploadView();
			void UploadProj();
			void UploadTextures();
			void UploadLight();
			void UploadSpecularProperties();

		private:
			std::vector<char> readShaderFile( const char* filename );
			void createShaders();
			void createShaderProgram();
			void createVertexArray();
			void loadActiveUniforms();
		};
	}
}