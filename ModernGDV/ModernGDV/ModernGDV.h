#pragma once

#include <stack>
#include <map>
#include "OGLInc.h"
#include "CCallbackWrapper.h"
#include "MGDVVertex.h"
#include "MGDVApp.h"
#include "Textures/Texture.h"
#include <vector>

namespace ModernGDV {
	class Driver {
	private:
		bool glfwInitialized; //Flag, ob GLFW deinitialisiert werden muss
		GLFWwindow *window; //Anzeigefenster

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
		GLuint shaderUniformSpecularPower;

		glm::mat4 transform;
		std::stack<glm::mat4> transformStack;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		float aspectRatio;
		float fov;
		float farDist;

		std::map<std::string, Textures::Texture> textureCache;
		App* app;
	public:
		Driver();
		virtual ~Driver();

		void Run();
		void SetApp( App* application );

		void FramebufferSizeChanged( GLFWwindow* window, int width, int height );

		GLuint GetShaderProgram();
		GLFWwindow* GetWindow();

		void SetProjectionOptions( const float& fov, const float& farPlane );
		void SetViewMatrix( glm::mat4& viewMat );
		const glm::mat4* Transform(  );
		void SetTransform( glm::mat4& transform );
		void PushTransform();
		void ReloadTransform();
		void PopTransform( int count = 1 );
		void ResetTransform();

		void SetLight( const glm::vec3& position, const glm::vec3& color, const float& power, const float& ambient );
		void SetSpecularProperties( const glm::vec3& specularColor, const float& specularPower = 5.0f);
		GLuint GetTexture( const std::string& filename );
		void UseTexture( GLuint id );
		GLuint CreateVertexBuffer( const std::vector<ModernGDV::Vertex>& vertices );

	private:
		void createWindow();
		std::vector<char> readShaderFile( const char* filename );
		void createShaders( );
		void createShaderProgram( );
		void createVertexArray( );
		void uploadTransform( );
		void uploadView();
		void updateProj();
		void uploadProj();
		void deinit();
	};
}
