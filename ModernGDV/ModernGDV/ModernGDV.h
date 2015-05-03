#pragma once

#include <stack>
#include <map>
#include "OGLInc.h"
#include "CCallbackWrapper.h"
#include "MGDVVertex.h"
#include "MGDVApp.h"
#include "Textures/Texture.h"
#include <vector>
#include "Shaders/ShaderLibrary.h"

namespace ModernGDV {
	class Driver {
	public:
		Shaders::ShaderLibrary ShaderLib;
	private:
		bool glfwInitialized; //Flag, ob GLFW deinitialisiert werden muss
		GLFWwindow *window; //Anzeigefenster


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

		GLFWwindow* GetWindow();

		void SetProjectionOptions( const float& fov, const float& farPlane );
		
		Textures::Texture* Driver::GetTexture( const std::string& filename );

		GLuint CreateVertexBuffer( const std::vector<ModernGDV::Vertex>& vertices );

	private:
		void createWindow();
		void updateProj();
		void deinit();
	};
}
