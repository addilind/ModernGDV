#ifndef MODERNGDV_H
#define MODERNGDV_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <stack>

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
		GLuint shaderTransform;

		glm::mat4 transform;
		std::stack<glm::mat4> transformStack;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

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
		//void SetTransform(glm::mat4);
		void AddTransform( glm::mat4& );
		void PushTransform();
		void ReloadTransform();
		void PopTransform( int count = 1 );
		void ResetTransform();

	private:
		void createWindow();
		std::vector<char> readShaderFile( const char* filename );
		void createShaders( );
		void createShaderProgram( );
		void createVertexArray( );
	};
}

#endif