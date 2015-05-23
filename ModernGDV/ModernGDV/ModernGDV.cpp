#include "ModernGDV.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

ModernGDV::Driver::Driver()
	: ShaderLib(), glfwInitialized( false ), window( nullptr ),
	aspectRatio(4.f/3.f), fov(45.f), farDist(100.f),
	textureCache(), app( nullptr ),
	debugWireframe(false)
{
	glfwSetErrorCallback( Callbacks::glfwErrorCallback );

	if (!glfwInit()) //GLFW Initialisieren
		throw std::runtime_error( "Cannot initialize GLFW" );

	glfwInitialized = true;
	Log( "DRVR", "GLFW initialized");

	try
	{
		createWindow();
		Log( "DRVR", "Window created");

		ShaderLib.UseShader( ShaderLib.GetShaderID( "default" ) );

		glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );
	}
	catch (...)
	{
		deinit(); //Destructor would not be called on exception in constructor (since there never really was an instance to destruct) -> manually clean up
		throw;
	}

	Log( "DRVR", "ModernGDV Initialization finished");
}

ModernGDV::Driver::~Driver()
{
	deinit();
}

void ModernGDV::Driver::Run()
{
	if (app == nullptr)
		throw std::logic_error( "Must call SetApp before running" );

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose( window )) { //Dauerschleife, solange das Fenster offen ist
		ShaderLib.ReapplyShader();

		double now = glfwGetTime();
		app->Update( static_cast<float>( now - lastTime ) );
		lastTime = now;

		app->Render();

		glfwSwapBuffers( window ); //Gezeichnetes auf den Monitor bringen
		glfwPollEvents(); //Tastendrücke, Mausbewegungen, Meldungen vom Betriebssystem etc. verarbeiten
	}
}

void ModernGDV::Driver::SetApp( App* application )
{
	app = application;
}

void ModernGDV::Driver::FramebufferSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport( 0, 0, width, height );
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	updateProj();
}

void ModernGDV::Driver::KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) //erst CallbackWrapper dann hier
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_F2:
			debugWireframe = !debugWireframe;
			if (debugWireframe)
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			else
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		case GLFW_KEY_F5:
			ShaderLib.ReloadShaders();
			break;
		}
	}
}

GLFWwindow* ModernGDV::Driver::GetWindow()
{
	return window;
}

void ModernGDV::Driver::SetProjectionOptions(const float& fov, const float& farPlane)
{
	this->fov = fov;
	farDist = farPlane;
	updateProj();
}

ModernGDV::Textures::Texture* ModernGDV::Driver::GetTexture( const std::string& filename )
{
	//Suche nach Datei in Texturcache
	auto cacheEntry = textureCache.find( filename ); //Textur wird einmalig geladen, dann aus dem Cache
	if (cacheEntry != textureCache.end())
		return &cacheEntry->second; //Gib gefundene ID zurück

	//Speichere die Textur im cache und gib ihre ID zurück
	return &textureCache.insert( std::pair<std::string, Textures::Texture>(
		filename, Textures::Texture( "../Data/" + filename + ".dds" )  ) ).first->second; 
}

GLuint ModernGDV::Driver::CreateVertexBuffer( const std::vector<ModernGDV::Vertex>& vertices )
{//Vertices aus dem CPU-Hauptspeicher in den Grafik-RAM kopieren
	GLuint vertexBuffer;
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices[0], GL_STATIC_DRAW );
	return vertexBuffer;
}

void ModernGDV::Driver::createWindow()
{
	glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x Antialiasing
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 ); //OpenGL-Version 3.2 verwenden
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#ifdef _DEBUG
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
#endif
	window = glfwCreateWindow( 1024, 768, "GDV: Bastian Kreuzer (734877), Adrian Mueller (734922)", nullptr, nullptr ); //Fenster erstellen
	if (window == nullptr)
		throw std::runtime_error( "Cannot create window - is your graphics card driver current?" );
	
	glfwSetWindowUserPointer( window, this );
	glfwSetFramebufferSizeCallback( window, Callbacks::glfwFramebufferSizeCallback );
	glfwSetKeyCallback( window, Callbacks::glfwKeyCallback );

	glfwMakeContextCurrent( window ); //Fenster für alle zukünftigen OpenGL-Aufrufe als Ziel setzen
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
		throw std::runtime_error( "ERROR: Unable to load required OpenGL-Functions" );

	Log( "DRVR", "Context info:" );
	Log( "DRVR", "\tVer: ", std::string( reinterpret_cast<const char*>(glGetString( GL_VERSION )) ) );
	Log( "DRVR", "\tVen: ", std::string( reinterpret_cast<const char*>(glGetString( GL_VENDOR )) ) );
	Log( "DRVR", "\tRen: ", std::string( reinterpret_cast<const char*>(glGetString( GL_RENDERER )) ) );
	Log( "DRVR", "\tSLV: ", std::string( reinterpret_cast<const char*>(glGetString( GL_SHADING_LANGUAGE_VERSION )) ) );

#ifdef _DEBUG
	glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB );
#endif
	glDebugMessageCallbackARB( &Callbacks::oglDebugMessage, this );
}

void ModernGDV::Driver::updateProj()
{
	glm::mat4 proj = glm::perspective( fov, aspectRatio, 0.1f, farDist );
	ShaderLib.SetProj( proj );
}

void ModernGDV::Driver::deinit()
{
	ShaderLib.UnloadShaders();
	textureCache.clear();

	if (window) {
		glfwDestroyWindow( window ); //Fenster entladen, falls vorhanden
		glfwPollEvents();
	}
	if (glfwInitialized)
		glfwTerminate(); //GLFW beenden, falls initialisiert
}

void ModernGDV::Log( const std::string& source, const std::string& message )
{
	Log( source, message, "" );
}
void ModernGDV::Log( const std::string& source, const std::string& messageA, const std::string& messageB)
{
	/*std::async( [source, message]()->void{*/ std::clog << glfwGetTime() << " [" << source << "]: " << messageA << messageB << std::endl; // } );
}

