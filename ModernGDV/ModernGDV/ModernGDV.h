#ifndef MODERNGDV_H
#define MODERNGDV_H

#include <epoxy/gl.h>
#include <epoxy/wgl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

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

		App* app;
	public:
		ModernGDV();
		virtual ~ModernGDV();

		void Run();
		void SetApp( App* application );

	private:
		void createWindow();
		std::vector<char> readShaderFile( const char* filename );
		void createShaders( );
		void createShaderProgram( );
		void createVertexArray( );
	};
}

#endif