#ifndef MODERNGDV_H
#define MODERNGDV_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <stack>
#include <map>

#include "MGDVVertex.h"
#include "MGDVApp.h"

namespace ModernGDV {
	class ModernGDV {
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

		glm::mat4 transform;
		std::stack<glm::mat4> transformStack;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		glm::vec3 lightPos;
		std::map<std::string, GLuint> textureCache;
		App* app;
	public:
		ModernGDV();
		virtual ~ModernGDV();

		void Run();
		void SetApp( App* application );

		GLuint GetShaderProgram();
		GLFWwindow* GetWindow();

		void SetProjectionMatrix( glm::mat4& projectionMat );
		void SetViewMatrix( glm::mat4& viewMat );
		const glm::mat4* Transform(  );
		void SetTransform( glm::mat4& transform );
		void PushTransform();
		void ReloadTransform();
		void PopTransform( int count = 1 );
		void ResetTransform();

		void SetLightPos( const glm::vec3& position );
		GLuint GetTexture( const std::string& filename );
		void UseTexture( GLuint id );

	private:
		void createWindow();
		std::vector<char> readShaderFile( const char* filename );
		void createShaders( );
		void createShaderProgram( );
		void createVertexArray( );
		void uploadTransform( );
		void uploadView();
		void uploadProj();
		GLuint loadTexture( const std::string& filename );
		void deinit();
	};
}

#endif