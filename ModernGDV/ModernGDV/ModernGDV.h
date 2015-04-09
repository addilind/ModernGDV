#ifndef MODERNGDV_H
#define MODERNGDV_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

		App* app;
	public:
		ModernGDV(App* app);
		virtual ~ModernGDV();

		void Run();

	private:
		void createWindow();
		char* readShaderFile( const char* filename );
		void createShaders( );
		void createShaderProgram( );
	};
}

#endif