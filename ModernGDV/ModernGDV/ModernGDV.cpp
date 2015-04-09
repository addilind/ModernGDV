#include "ModernGDV.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

ModernGDV::ModernGDV::ModernGDV( )
	: glfwInitialized(false), window(nullptr), vertexShader(0U), fragmentShader(0U), shaderProgram(0U), app(nullptr)
{
	if (!glfwInit()) //GLFW Initialisieren
		throw std::runtime_error( "Cannot initialize GLFW" );

	glfwInitialized = true;
	std::cout << "GLFW initialized" << std::endl;

	createWindow();
	std::cout << "Window created" << std::endl;

	createShaders();
	createShaderProgram();
}

ModernGDV::ModernGDV::~ModernGDV()
{
	if (shaderProgram > 0U)
		glDeleteProgram( shaderProgram );
	if (fragmentShader > 0U)
		glDeleteShader( fragmentShader );
	if (vertexShader > 0U)
		glDeleteShader( vertexShader );
	if (window)
		glfwDestroyWindow( window ); //Fenster entladen, falls vorhanden
	if (glfwInitialized)
		glfwTerminate(); //GLFW beenden, falls initialisiert
}

void ModernGDV::ModernGDV::Run()
{
	if (app == nullptr)
		throw std::logic_error( "Must call SetApp before running" );

	while (!glfwWindowShouldClose( window )) { //Dauerschleife, solange das Fenster offen ist
		glUseProgram( shaderProgram );
		app->Render();

		glfwSwapBuffers( window ); //Gezeichnetes auf den Monitor bringen
		glfwPollEvents(); //Tastendr�cke, Mausbewegungen, Meldungen vom Betriebssystem etc. verarbeiten
	}
}

void ModernGDV::ModernGDV::SetApp( App* application )
{
	if (application == nullptr)
		throw std::logic_error( "Passed invalid app pointer" );
	app = application;
}

void ModernGDV::ModernGDV::createWindow()
{
	glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x Antialiasing
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 ); //OpenGL-Version 4.0 verwenden
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	window = glfwCreateWindow( 1024, 768, "ModernGDV App", nullptr, nullptr ); //Fenster erstellen

	if (!window)
		throw std::runtime_error( "Cannot create window" );

	glfwMakeContextCurrent( window ); //Fenster f�r alle zuk�nftigen OpenGL-Aufrufe als Ziel setzen
}

char* ModernGDV::ModernGDV::readShaderFile( const char* filename )
{
	std::ifstream shaderFile( filename );
	if (!shaderFile)
		throw std::runtime_error( "Cannot read Shader file" );

	//Dateil�nge bestimmen
	shaderFile.seekg( 0, shaderFile.end );
	int shaderLength = static_cast<int>(shaderFile.tellg());
	shaderFile.seekg( 0, shaderFile.beg );

	char* shaderGLSL = new char[shaderLength + 1];
	memset( shaderGLSL, 0, shaderLength + 1 );
	shaderFile.read( shaderGLSL, shaderLength );

	shaderFile.close();

	return shaderGLSL;
}

void ModernGDV::ModernGDV::createShaders( )
{
	//GLSL-Dateien einlesen
	char* vertexShaderGLSL = readShaderFile( "VertexShader.glsl" );
	char* fragmentShaderGLSL = readShaderFile( "FragmentShader.glsl" );

	//Shader laden
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderGLSL, NULL );
	glCompileShader( vertexShader );

	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderGLSL, NULL );
	glCompileShader( fragmentShader );

	GLint result = GL_FALSE;

	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> vertexShaderErrorMessage( infoLogLength );
		glGetShaderInfoLog( vertexShader, infoLogLength, NULL, &vertexShaderErrorMessage[0] );
		throw std::runtime_error( &vertexShaderErrorMessage[0] );
	}

	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength );
		std::vector<char> fragmentShaderErrorMessage( infoLogLength );
		glGetShaderInfoLog( fragmentShader, infoLogLength, NULL, &fragmentShaderErrorMessage[0] );
		throw std::runtime_error( &fragmentShaderErrorMessage[0] );
	}


	delete[] vertexShaderGLSL;
	delete[] fragmentShaderGLSL;
}

void ModernGDV::ModernGDV::createShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, fragmentShader );
	glAttachShader( shaderProgram, vertexShader );
	glLinkProgram( shaderProgram );

	GLint result = GL_FALSE;

	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &result );
	if (result != GL_TRUE) {
		int infoLogLength = -1;
		glGetProgramiv( shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength );
		if (infoLogLength < 1)
			throw std::runtime_error( "Unable to link program, no error message" );
		std::vector<char> shaderProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog( shaderProgram, infoLogLength, NULL, &shaderProgramErrorMessage[0] );
		throw std::runtime_error( &shaderProgramErrorMessage[0] );
	}
}